/*
   INDI 开发者手册
   教程 #2

   "简单望远镜驱动程序"

   我们开发了一个简单的望远镜模拟器。

   请参考 README，其中包含有关如何构建此驱动程序并将其与兼容 INDI 的客户端一起使用的说明。

*/

/** \file simplescope.cpp
    \brief 构建一个基本的 INDI 望远镜设备，用于模拟 GOTO 命令。
    \author Jasem Mutlaq

    \example simplescope.cpp
    一个简单的 GOTO 望远镜，模拟平移操作。
*/

#include "simplescope.h"

#include "indicom.h"

#include <cmath>
#include <memory>

static std::unique_ptr<SimpleScope> simpleScope(new SimpleScope());

SimpleScope::SimpleScope()
{
    // 我们添加了一个额外的调试级别，以便可以记录详细的望远镜状态
    DBG_SCOPE = INDI::Logger::getInstance().addDebugLevel("Scope Verbose", "SCOPE");
}

/**************************************************************************************
** 在这里初始化属性。我们只需要初始化调试控件
***************************************************************************************/
bool SimpleScope::initProperties()
{
    // 始终先调用父类的 initProperties()
    INDI::Telescope::initProperties();

    // 添加调试控件，以便最终用户可以打开和关闭调试/日志记录
    addDebugControl();

    // 启用模拟模式，这样 INDI::Telescope 中的串口连接不会尝试与物理串口进行连接
    setSimulation(true);

    // 设置望远镜功能。0 表示支持的平移速率数量。对于这个简单的驱动程序，我们没有支持任何速率。
    SetTelescopeCapability(TELESCOPE_CAN_GOTO | TELESCOPE_CAN_ABORT, 0);

    return true;
}

/**************************************************************************************
** INDI 要求我们通过握手检查设备通信
***************************************************************************************/
bool SimpleScope::Handshake()
{
    // 当与真实的安装座通信时，我们在这里检查命令是否被接收并被安装座确认。
    // 对于 SimpleScope，我们直接返回 true。
    return true;
}

/**************************************************************************************
** INDI 要求我们提供默认设备名称
***************************************************************************************/
const char *SimpleScope::getDefaultName()
{
    return "Simple Scope";
}

/**************************************************************************************
** 客户端要求我们移动到新位置
***************************************************************************************/
bool SimpleScope::Goto(double ra, double dec)
{
    targetRA  = ra;
    targetDEC = dec;
    char RAStr[64] = {0}, DecStr[64] = {0};

    // 将 RA/DEC 转换为字符串
    fs_sexa(RAStr, targetRA, 2, 3600);
    fs_sexa(DecStr, targetDEC, 2, 3600);

    // 将状态标记为正在移动
    TrackState = SCOPE_SLEWING;

    // 通知客户端我们正在移动到新位置
    LOGF_INFO("移动到 RA: %s - DEC: %s", RAStr, DecStr);

    // 成功！
    return true;
}

/**************************************************************************************
** 客户端要求我们中止移动
***************************************************************************************/
bool SimpleScope::Abort()
{
    return true;
}

/**************************************************************************************
** 客户端要求我们报告望远镜状态
***************************************************************************************/
bool SimpleScope::ReadScopeStatus()
{
    static struct timeval ltv
    {
        0, 0
    };
    struct timeval tv
    {
        0, 0
    };
    double dt = 0, da_ra = 0, da_dec = 0, dx = 0, dy = 0;
    int nlocked;

    /* 更新自上次轮询以来的时间，不假设正好是 POLLMS */
    gettimeofday(&tv, nullptr);

    if (ltv.tv_sec == 0 && ltv.tv_usec == 0)
        ltv = tv;

    dt  = tv.tv_sec - ltv.tv_sec + (tv.tv_usec - ltv.tv_usec) / 1e6;
    ltv = tv;

    // 计算自上次以来移动的距离
    da_ra  = SLEW_RATE * dt;
    da_dec = SLEW_RATE * dt;

    /* 根据当前状态处理。我们检查 EQUATORIAL_EOD_COORDS_REQUEST 的状态并采取相应行动 */
    switch (TrackState)
    {
        case SCOPE_SLEWING:
            // 等待直到我们在 RA 和 DEC 轴上都“锁定”到位
            nlocked = 0;

            // 计算 RA 的差值
            dx = targetRA - currentRA;

            // 如果差值非常小，即小于自上次以来的移动量，则我们到达目标 RA。
            if (fabs(dx) * 15. <= da_ra)
            {
                currentRA = targetRA;
                nlocked++;
            }
            // 否则增加 RA
            else if (dx > 0)
                currentRA += da_ra / 15.;
            // 否则减少 RA
            else
                currentRA -= da_ra / 15.;

            // 计算 DEC 的差值
            dy = targetDEC - currentDEC;

            // 如果差值非常小，即小于自上次以来的移动量，则我们到达目标 DEC。
            if (fabs(dy) <= da_dec)
            {
                currentDEC = targetDEC;
                nlocked++;
            }
            // 否则增加 DEC
            else if (dy > 0)
                currentDEC += da_dec;
            // 否则减少 DEC
            else
                currentDEC -= da_dec;

            // 检查我们是否在 RA 和 DEC 上都到达了目标位置
            if (nlocked == 2)
            {
                // 将状态设置为 TRACKING
                TrackState = SCOPE_TRACKING;

                LOG_INFO("望远镜移动完成。正在跟踪...");
            }
            break;

        default:
            break;
    }

    char RAStr[64] = {0}, DecStr[64] = {0};

    // 将 RA/DEC 转换为字符串
    fs_sexa(RAStr, currentRA, 2, 3600);
    fs_sexa(DecStr, currentDEC, 2, 3600);

    DEBUGF(DBG_SCOPE, "当前 RA: %s 当前 DEC: %s", RAStr, DecStr);

    NewRaDec(currentRA, currentDEC);
    return true;
}
