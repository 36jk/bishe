#include "config.h"
#include "indi_mycustomdriver.h"
#include "inditelescope.h"

#include "indicom.h"
#include <cmath>
#include <memory>

// 声明一个指向 MyCustomDriver 的智能指针实例。
// 该指针用于管理 MyCustomDriver 对象的生命周期。
static std::unique_ptr<MyCustomDriver> mydriver(new MyCustomDriver());

// 构造函数：初始化调试日志的作用域。
MyCustomDriver::MyCustomDriver(){
    // DBG_SCOPE 是一个调试日志级别，用于记录与望远镜相关的详细信息。
    DBG_SCOPE = INDI::Logger::getInstance().addDebugLevel("Scope Verbose", "SCOPE");
}

// 初始化设备属性。
// 继承自 INDI::Telescope 的 initProperties 方法，并添加自定义调试控制。
bool MyCustomDriver::initProperties()
{
    // 调用父类的 initProperties 方法，初始化基本属性。
    INDI::Telescope::initProperties();
    // 添加调试控制选项。
    addDebugControl();
    // 设置为模拟模式。
    setSimulation(true);
    // 设置望远镜的功能：支持 GOTO 和中止操作。
    SetTelescopeCapability(TELESCOPE_CAN_GOTO | TELESCOPE_CAN_ABORT , 0);
    return true;
}

bool MyCustomDriver::Connect()
{
    LOG_INFO("连接成功!");
    // 连接方法：在实际设备中，这里会执行连接操作。
    // 在模拟模式下，直接返回 true。
    return true;
}


bool MyCustomDriver::Disconnect()
{
    LOG_INFO("断开连接成功!");
    // 断开连接方法：在实际设备中，这里会执行断开操作。
    // 在模拟模式下，直接返回 true。
    return true;
}

// 握手方法：用于与实际设备通信时确认连接是否正常。
// 在模拟模式下，直接返回 true。
bool MyCustomDriver::Handshake()
{
    // 如果是实际设备，这里会检查命令是否被设备接收并确认。
    return true;
}

// 获取设备的默认名称。
// 该名称会被 INDI 客户端显示。
const char *MyCustomDriver::getDefaultName()
{
    return "MyCustomTelescope"; // 返回设备名称为 "MyCustomTelescope"。
}

// Goto 方法：控制望远镜移动到指定的赤经 (RA) 和赤纬 (DEC) 坐标。
bool MyCustomDriver::Goto(double ra, double dec)
{
    // 设置目标赤经和赤纬。
    targetRA  = ra;
    targetDEC = dec;

    char RAStr[64] = {0}, DecStr[64] = {0};

    // 将目标赤经和赤纬转换为字符串格式，便于日志记录。
    fs_sexa(RAStr, targetRA, 2, 3600);
    fs_sexa(DecStr, targetDEC, 2, 3600);

    // 将望远镜状态设置为正在移动（SLEWING）。
    TrackState = SCOPE_SLEWING;

    // 记录日志，通知客户端望远镜正在移动到新位置。
    LOGF_INFO("Slewing to RA: %s - DEC: %s", RAStr, DecStr);

    return true; // 返回成功。
}

// Abort 方法：中止当前操作。
// 在模拟模式下，直接返回 true。
bool MyCustomDriver::Abort()
{
    return true;
}

// ReadScopeStatus 方法：读取望远镜的当前状态并更新其位置。
bool MyCustomDriver::ReadScopeStatus()
{
    static struct timeval ltv
    {
        0, 0
    }; // 上次轮询的时间。
    struct timeval tv
    {
        0, 0
    }; // 当前时间。
    double dt = 0, da_ra = 0, da_dec = 0, dx = 0, dy = 0;
    int nlocked;

    // 更新自上次轮询以来的时间间隔。
    gettimeofday(&tv, nullptr);

    if (ltv.tv_sec == 0 && ltv.tv_usec == 0)
        ltv = tv;

    dt  = tv.tv_sec - ltv.tv_sec + (tv.tv_usec - ltv.tv_usec) / 1e6;
    ltv = tv;

    // 根据时间间隔计算望远镜的移动量。
    da_ra  = SLEW_RATE * dt;
    da_dec = SLEW_RATE * dt;

    // 根据当前状态处理望远镜的行为。
    switch (TrackState)
    {
        case SCOPE_SLEWING:
            // 检查是否已到达目标位置。
            nlocked = 0;

            // 计算赤经的差值。
            dx = targetRA - currentRA;

            // 如果差值足够小，表示已到达目标赤经。
            if (fabs(dx) * 15. <= da_ra)
            {
                currentRA = targetRA;
                nlocked++;
            }
            else if (dx > 0)
                currentRA += da_ra / 15.; // 向目标赤经增加。
            else
                currentRA -= da_ra / 15.; // 向目标赤经减少。

            // 计算赤纬的差值。
            dy = targetDEC - currentDEC;

            // 如果差值足够小，表示已到达目标赤纬。
            if (fabs(dy) <= da_dec)
            {
                currentDEC = targetDEC;
                nlocked++;
            }
            else if (dy > 0)
                currentDEC += da_dec; // 向目标赤纬增加。
            else
                currentDEC -= da_dec; // 向目标赤纬减少。

            // 如果赤经和赤纬都已到达目标位置，切换到跟踪状态。
            if (nlocked == 2)
            {
                TrackState = SCOPE_TRACKING;
                LOG_INFO("Telescope slew is complete. Tracking...");
            }
            break;

        default:
            break;
    }

    char RAStr[64] = {0}, DecStr[64] = {0};

    // 将当前赤经和赤纬转换为字符串格式，便于调试。
    fs_sexa(RAStr, currentRA, 2, 3600);
    fs_sexa(DecStr, currentDEC, 2, 3600);

    DEBUGF(DBG_SCOPE, "Current RA: %s Current DEC: %s", RAStr, DecStr);

    // 更新客户端的赤经和赤纬。
    NewRaDec(currentRA, currentDEC);
    return true;
}
