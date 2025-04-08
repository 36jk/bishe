#pragma once

#include "indiguiderinterface.h"
#include "inditelescope.h"
#include "alignment/AlignmentSubsystemForDrivers.h"

class ScopeSim : public INDI::Telescope, public INDI::AlignmentSubsystem::AlignmentSubsystemForDrivers
{
    public:
        ScopeSim();

    protected:
        bool Abort() override; // 中止望远镜操作
        bool canSync(); // 检查是否可以同步
        bool Connect() override; // 连接到设备
        bool Disconnect() override; // 断开设备连接
        const char *getDefaultName() override; // 获取默认设备名称
        bool Goto(double ra, double dec) override; // 移动到指定的赤经和赤纬
        bool initProperties() override; // 初始化设备属性
        bool ISNewBLOB(const char *dev, const char *name, int sizes[], int blobsizes[], char *blobs[],
                       char *formats[], char *names[], int n) override; // 处理新的 BLOB 属性
        bool ISNewNumber(const char *dev, const char *name, double values[], char *names[], int n) override; // 处理新的数字属性
        bool ISNewSwitch(const char *dev, const char *name, ISState *states, char *names[], int n) override; // 处理新的开关属性
        bool ISNewText(const char *dev, const char *name, char *texts[], char *names[], int n) override; // 处理新的文本属性
        bool MoveNS(INDI_DIR_NS dir, TelescopeMotionCommand command) override; // 控制望远镜南北方向的移动
        bool MoveWE(INDI_DIR_WE dir, TelescopeMotionCommand command) override; // 控制望远镜东西方向的移动
        bool ReadScopeStatus() override; // 读取望远镜状态
        bool Sync(double ra, double dec) override; // 同步望远镜到指定的赤经和赤纬
        void TimerHit() override; // 定时器触发事件
        bool updateLocation(double latitude, double longitude, double elevation) override; // 更新望远镜位置

    private:
        static constexpr long MICROSTEPS_PER_REVOLUTION { 1000000 }; // 每圈的微步数
        static constexpr double MICROSTEPS_PER_DEGREE { MICROSTEPS_PER_REVOLUTION / 360.0 }; // 每度的微步数
        static constexpr double DEFAULT_SLEW_RATE { MICROSTEPS_PER_DEGREE * 2.0 }; // 默认的移动速率
        static constexpr long MAX_DEC { (long)(90.0 * MICROSTEPS_PER_DEGREE) }; // 最大赤纬
        static constexpr long MIN_DEC { (long)(-90.0 * MICROSTEPS_PER_DEGREE) }; // 最小赤纬

        enum AxisStatus
        {
            STOPPED, // 停止
            SLEWING, // 移动中
            SLEWING_TO // 移动到目标
        };
        enum AxisDirection
        {
            FORWARD, // 前进
            REVERSE // 后退
        };

        AxisStatus AxisStatusDEC { STOPPED }; // DEC 轴状态
        AxisDirection AxisDirectionDEC { FORWARD }; // DEC 轴方向
        double AxisSlewRateDEC { DEFAULT_SLEW_RATE }; // DEC 轴移动速率
        long CurrentEncoderMicrostepsDEC { 0 }; // 当前 DEC 轴编码器微步数
        long GotoTargetMicrostepsDEC { 0 }; // DEC 轴目标微步数

        AxisStatus AxisStatusRA { STOPPED }; // RA 轴状态
        AxisDirection AxisDirectionRA { FORWARD }; // RA 轴方向
        double AxisSlewRateRA { DEFAULT_SLEW_RATE }; // RA 轴移动速率
        long CurrentEncoderMicrostepsRA { 0 }; // 当前 RA 轴编码器微步数
        long GotoTargetMicrostepsRA { 0 }; // RA 轴目标微步数

        // 跟踪
        INDI::IEquatorialCoordinates CurrentTrackingTarget { 0, 0 }; // 当前跟踪目标的赤经和赤纬

        // 定时器触发中的跟踪
        int TraceThisTickCount { 0 }; // 当前计时器触发计数
        bool TraceThisTick { false }; // 是否跟踪当前触发

        unsigned int DBG_SIMULATOR { 0 }; // 调试级别
};
