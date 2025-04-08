/*
   INDI 开发者手册
   教程 #7

   "简单的望远镜模拟器"

   我们构建了一个最基本（且无用）的设备驱动程序来说明 INDI 的使用。

   请参考 README，其中包含有关如何构建此驱动程序并将其与 INDI 兼容客户端一起使用的说明。
*/

#include "telescope_simulator_client.h"

#include "indicom.h"

#include <memory>

using namespace INDI::AlignmentSubsystem;

// 我们声明了一个指向 ScopeSim 的智能指针。
std::unique_ptr<ScopeSim> telescope_sim(new ScopeSim());

ScopeSim::ScopeSim() :
    DBG_SIMULATOR(INDI::Logger::getInstance().addDebugLevel("Simulator Verbose", "SIMULATOR"))
{
}

bool ScopeSim::Abort()
{
    if (MovementNSSP.getState() == IPS_BUSY)
    {
        MovementNSSP.reset();
        MovementNSSP.setState(IPS_IDLE);
        MovementNSSP.apply();
    }

    if (MovementWESP.getState() == IPS_BUSY)
    {
        MovementWESP.setState(IPS_IDLE);
        MovementWESP.reset();
        MovementWESP.apply();
    }

    if (EqNP.getState() == IPS_BUSY)
    {
        EqNP.setState(IPS_IDLE);
        EqNP.apply();
    }

    TrackState = SCOPE_IDLE;

    AxisStatusRA = AxisStatusDEC = STOPPED; // 这个神奇的无惯性望远镜可以立即停止！

    AbortSP.setState(IPS_OK);
    AbortSP.reset();
    AbortSP.apply();
    LOG_INFO("Telescope aborted.");

    return true;
}

bool ScopeSim::canSync()
{
    return true;
}

bool ScopeSim::Connect()
{
    SetTimer(getCurrentPollingPeriod());
    return true;
}

bool ScopeSim::Disconnect()
{
    return true;
}

const char *ScopeSim::getDefaultName()
{
    return (const char *)"Simple Telescope Simulator";
}

bool ScopeSim::Goto(double ra, double dec)
{
    DEBUGF(DBG_SIMULATOR, "Goto - Celestial reference frame target right ascension %lf(%lf) declination %lf",
           ra * 360.0 / 24.0, ra, dec);

    if (CoordSP.isSwitchOn("TRACK"))
    {
        char RAStr[32], DecStr[32];
        fs_sexa(RAStr, ra, 2, 3600);
        fs_sexa(DecStr, dec, 2, 3600);
        CurrentTrackingTarget.rightascension  = ra;
        CurrentTrackingTarget.declination = dec;
        DEBUG(DBG_SIMULATOR, "Goto - tracking requested");
    }

    // 调用对齐子系统将天体参考系坐标转换为望远镜参考系坐标
    TelescopeDirectionVector TDV;
    INDI::IHorizontalCoordinates AltAz { 0, 0 };

    if (TransformCelestialToTelescope(ra, dec, 0.0, TDV))
    {
        // 对齐子系统已成功转换坐标
        AltitudeAzimuthFromTelescopeDirectionVector(TDV, AltAz);
    }
    else
    {
        // 对齐子系统无法转换坐标。
        // 使用存储的天文台位置尝试一些简单的旋转（如果有）

        INDI::IEquatorialCoordinates EquatorialCoordinates { ra, dec };
        INDI::EquatorialToHorizontal(&EquatorialCoordinates, &m_Location, ln_get_julian_from_sys(), &AltAz);
        TDV = TelescopeDirectionVectorFromAltitudeAzimuth(AltAz);
        switch (GetApproximateMountAlignment())
        {
            case ZENITH:
                break;

            case NORTH_CELESTIAL_POLE:
                // 绕 y 轴顺时针（负）旋转 90 减去（正）天文台纬度。矢量本身逆时针旋转
                TDV.RotateAroundY(m_Location.latitude - 90.0);
                break;

            case SOUTH_CELESTIAL_POLE:
                // 绕 y 轴逆时针（正）旋转 90 加上（负）天文台纬度。矢量本身顺时针旋转
                TDV.RotateAroundY(m_Location.latitude + 90.0);
                break;
        }
        AltitudeAzimuthFromTelescopeDirectionVector(TDV, AltAz);
    }

    // 我的高度编码器范围为 -90 到 +90（边界检查）
    if ((AltAz.altitude > 90.0) || (AltAz.altitude < -90.0))
    {
        DEBUG(DBG_SIMULATOR, "Goto - Altitude out of range");
        // 这不应该发生
        return false;
    }

    // 我的极轴编码器范围为 0 到 +360（边界检查）
    if ((AltAz.azimuth > 360.0) || (AltAz.azimuth < -360.0))
    {
        DEBUG(DBG_SIMULATOR, "Goto - Azimuth out of range");
        // 这不应该发生
        return false;
    }

    if (AltAz.azimuth < 0.0)
    {
        DEBUG(DBG_SIMULATOR, "Goto - Azimuth negative");
        AltAz.azimuth = 360.0 + AltAz.azimuth;
    }

    DEBUGF(DBG_SIMULATOR, "Goto - Scope reference frame target altitude %lf azimuth %lf", AltAz.altitude,
           AltAz.azimuth);

    GotoTargetMicrostepsDEC = int(AltAz.altitude * MICROSTEPS_PER_DEGREE);
    if (GotoTargetMicrostepsDEC == CurrentEncoderMicrostepsDEC)
        AxisStatusDEC = STOPPED;
    else
    {
        if (GotoTargetMicrostepsDEC > CurrentEncoderMicrostepsDEC)
            AxisDirectionDEC = FORWARD;
        else
            AxisDirectionDEC = REVERSE;
        AxisStatusDEC = SLEWING_TO;
    }
    GotoTargetMicrostepsRA = int(AltAz.azimuth * MICROSTEPS_PER_DEGREE);
    if (GotoTargetMicrostepsRA == CurrentEncoderMicrostepsRA)
        AxisStatusRA = STOPPED;
    else
    {
        if (GotoTargetMicrostepsRA > CurrentEncoderMicrostepsRA)
            AxisDirectionRA = (GotoTargetMicrostepsRA - CurrentEncoderMicrostepsRA) < MICROSTEPS_PER_REVOLUTION / 2.0 ?
                              FORWARD :
                              REVERSE;
        else
            AxisDirectionRA = (CurrentEncoderMicrostepsRA - GotoTargetMicrostepsRA) < MICROSTEPS_PER_REVOLUTION / 2.0 ?
                              REVERSE :
                              FORWARD;
        AxisStatusRA = SLEWING_TO;
    }

    TrackState = SCOPE_SLEWING;

    return true;
}

bool ScopeSim::initProperties()
{
    /* 确保先初始化父类属性 */
    INDI::Telescope::initProperties();

    TrackState = SCOPE_IDLE;

    /* 添加调试控件，以便在必要时调试驱动程序 */
    addDebugControl();

    // 添加对齐属性
    InitAlignmentProperties(this);

    return true;
}

bool ScopeSim::ISNewBLOB(const char *dev, const char *name, int sizes[], int blobsizes[], char *blobs[],
                         char *formats[], char *names[], int n)
{
    if (dev != nullptr && strcmp(dev, getDeviceName()) == 0)
    {
        // 处理对齐属性
        ProcessAlignmentBLOBProperties(this, name, sizes, blobsizes, blobs, formats, names, n);
    }
    // 传递给上层
    return INDI::Telescope::ISNewBLOB(dev, name, sizes, blobsizes, blobs, formats, names, n);
}

bool ScopeSim::ISNewNumber(const char *dev, const char *name, double values[], char *names[], int n)
{
    // 首先检查是否是我们的设备

    if (dev != nullptr && strcmp(dev, getDeviceName()) == 0)
    {
        // 处理对齐属性
        ProcessAlignmentNumberProperties(this, name, values, names, n);
    }

    // 如果我们没有处理它，继续传递给上层，让其他人处理
    return INDI::Telescope::ISNewNumber(dev, name, values, names, n);
}

bool ScopeSim::ISNewSwitch(const char *dev, const char *name, ISState *states, char *names[], int n)
{
    if (dev != nullptr && strcmp(dev, getDeviceName()) == 0)
    {
        // 处理对齐属性
        ProcessAlignmentSwitchProperties(this, name, states, names, n);
    }

    // 没有人认领这个，所以忽略它
    return INDI::Telescope::ISNewSwitch(dev, name, states, names, n);
}

bool ScopeSim::ISNewText(const char *dev, const char *name, char *texts[], char *names[], int n)
{
    if (dev != nullptr && strcmp(dev, getDeviceName()) == 0)
    {
        // 处理对齐属性
        ProcessAlignmentTextProperties(this, name, texts, names, n);
    }
    // 传递给上层
    return INDI::Telescope::ISNewText(dev, name, texts, names, n);
}

bool ScopeSim::MoveNS(INDI_DIR_NS dir, TelescopeMotionCommand command)
{
    AxisDirection axisDir = (dir == DIRECTION_NORTH) ? FORWARD : REVERSE;
    AxisStatus axisStat   = (command == MOTION_START) ? SLEWING : STOPPED;

    AxisSlewRateDEC  = DEFAULT_SLEW_RATE;
    AxisDirectionDEC = axisDir;
    AxisStatusDEC    = axisStat;

    return true;
}

bool ScopeSim::MoveWE(INDI_DIR_WE dir, TelescopeMotionCommand command)
{
    AxisDirection axisDir = (dir == DIRECTION_WEST) ? FORWARD : REVERSE;
    AxisStatus axisStat   = (command == MOTION_START) ? SLEWING : STOPPED;

    AxisSlewRateRA  = DEFAULT_SLEW_RATE;
    AxisDirectionRA = axisDir;
    AxisStatusRA    = axisStat;

    return true;
}

bool ScopeSim::ReadScopeStatus()
{
    INDI::IHorizontalCoordinates AltAz { CurrentEncoderMicrostepsRA / MICROSTEPS_PER_DEGREE, CurrentEncoderMicrostepsDEC / MICROSTEPS_PER_DEGREE };
    TelescopeDirectionVector TDV = TelescopeDirectionVectorFromAltitudeAzimuth(AltAz);
    double RightAscension, Declination;
    if (!TransformTelescopeToCelestial(TDV, RightAscension, Declination))
    {
        if (TraceThisTick)
            DEBUG(DBG_SIMULATOR, "ReadScopeStatus - TransformTelescopeToCelestial failed");

        TelescopeDirectionVector RotatedTDV(TDV);

        switch (GetApproximateMountAlignment())
        {
            case ZENITH:
                if (TraceThisTick)
                    DEBUG(DBG_SIMULATOR, "ReadScopeStatus - ApproximateMountAlignment ZENITH");
                break;

            case NORTH_CELESTIAL_POLE:
                if (TraceThisTick)
                    DEBUG(DBG_SIMULATOR, "ReadScopeStatus - ApproximateMountAlignment NORTH_CELESTIAL_POLE");
                // 绕 y 轴逆时针（正）旋转 90 减去（正）天文台纬度。矢量本身顺时针旋转
                RotatedTDV.RotateAroundY(90.0 - m_Location.latitude);
                AltitudeAzimuthFromTelescopeDirectionVector(RotatedTDV, AltAz);
                break;

            case SOUTH_CELESTIAL_POLE:
                if (TraceThisTick)
                    DEBUG(DBG_SIMULATOR, "ReadScopeStatus - ApproximateMountAlignment SOUTH_CELESTIAL_POLE");
                // 绕 y 轴顺时针（负）旋转 90 加上（负）天文台纬度。矢量本身逆时针旋转
                RotatedTDV.RotateAroundY(-90.0 - m_Location.latitude);
                AltitudeAzimuthFromTelescopeDirectionVector(RotatedTDV, AltAz);
                break;
        }

        INDI::IEquatorialCoordinates EquatorialCoordinates;
        INDI::HorizontalToEquatorial(&AltAz, &m_Location, ln_get_julian_from_sys(), &EquatorialCoordinates);
        // libnova 以十进制度工作
        RightAscension = EquatorialCoordinates.rightascension;
        Declination    = EquatorialCoordinates.declination;
    }

    if (TraceThisTick)
        DEBUGF(DBG_SIMULATOR, "ReadScopeStatus - RA %lf hours DEC %lf degrees", RightAscension, Declination);

    NewRaDec(RightAscension, Declination);

    return true;
}

bool ScopeSim::Sync(double ra, double dec)
{
    INDI::IHorizontalCoordinates AltAz { 0, 0 };
    AlignmentDatabaseEntry NewEntry;

    AltAz.altitude = double(CurrentEncoderMicrostepsDEC) / MICROSTEPS_PER_DEGREE;
    AltAz.azimuth  = double(CurrentEncoderMicrostepsRA) / MICROSTEPS_PER_DEGREE;

    NewEntry.ObservationJulianDate = ln_get_julian_from_sys();
    NewEntry.RightAscension        = ra;
    NewEntry.Declination           = dec;
    NewEntry.TelescopeDirection    = TelescopeDirectionVectorFromAltitudeAzimuth(AltAz);
    NewEntry.PrivateDataSize       = 0;

    if (!CheckForDuplicateSyncPoint(NewEntry))
    {
        GetAlignmentDatabase().push_back(NewEntry);

        // 告诉客户端大小已更改
        UpdateSize();

        // 告诉数学插件重新初始化
        Initialise(this);

        return true;
    }
    return false;
}

void ScopeSim::TimerHit()
{
    TraceThisTickCount++;
    if (60 == TraceThisTickCount)
    {
        TraceThisTick      = true;
        TraceThisTickCount = 0;
    }
    // 模拟安装移动

    static struct timeval ltv
    {
        0, 0
    }; // 上一次系统时间
    struct timeval tv
    {
        0, 0
    };         // 新的系统时间
    double dt;                 // 自上次滴答以来经过的时间（秒）

    gettimeofday(&tv, nullptr);

    if (ltv.tv_sec == 0 && ltv.tv_usec == 0)
        ltv = tv;

    dt  = tv.tv_sec - ltv.tv_sec + (tv.tv_usec - ltv.tv_usec) / 1e6;
    ltv = tv;

    // RA 轴
    long SlewSteps          = dt * AxisSlewRateRA;
    bool CompleteRevolution = SlewSteps >= MICROSTEPS_PER_REVOLUTION;
    SlewSteps               = SlewSteps % MICROSTEPS_PER_REVOLUTION; // 以防万一 ;-)

    switch (AxisStatusRA)
    {
        case STOPPED:
            // 什么都不做
            break;

        case SLEWING:
        {
            DEBUGF(DBG_SIMULATOR,
                   "TimerHit Slewing - RA Current Encoder %ld SlewSteps %ld Direction %d Target %ld Status %d",
                   CurrentEncoderMicrostepsRA, SlewSteps, AxisDirectionRA, GotoTargetMicrostepsRA, AxisStatusRA);

            // 更新编码器
            if (FORWARD == AxisDirectionRA)
                CurrentEncoderMicrostepsRA += SlewSteps;
            else
                CurrentEncoderMicrostepsRA -= SlewSteps;
            if (CurrentEncoderMicrostepsRA < 0)
                CurrentEncoderMicrostepsRA += MICROSTEPS_PER_REVOLUTION;
            else if (CurrentEncoderMicrostepsRA >= MICROSTEPS_PER_REVOLUTION)
                CurrentEncoderMicrostepsRA -= MICROSTEPS_PER_REVOLUTION;

            DEBUGF(DBG_SIMULATOR, "TimerHit Slewing - RA New Encoder %d New Status %d", CurrentEncoderMicrostepsRA,
                   AxisStatusRA);
            break;
        }

        case SLEWING_TO:
        {
            DEBUGF(DBG_SIMULATOR,
                   "TimerHit SlewingTo - RA Current Encoder %ld SlewSteps %ld Direction %d Target %ld Status %d",
                   CurrentEncoderMicrostepsRA, SlewSteps, AxisDirectionRA, GotoTargetMicrostepsRA, AxisStatusRA);

            long OldEncoder = CurrentEncoderMicrostepsRA;
            // 更新编码器
            if (FORWARD == AxisDirectionRA)
                CurrentEncoderMicrostepsRA += SlewSteps;
            else
                CurrentEncoderMicrostepsRA -= SlewSteps;
            if (CurrentEncoderMicrostepsRA < 0)
                CurrentEncoderMicrostepsRA += MICROSTEPS_PER_REVOLUTION;
            else if (CurrentEncoderMicrostepsRA >= MICROSTEPS_PER_REVOLUTION)
                CurrentEncoderMicrostepsRA -= MICROSTEPS_PER_REVOLUTION;

            if (CompleteRevolution)
            {
                // 必须找到目标
                AxisStatusRA               = STOPPED;
                CurrentEncoderMicrostepsRA = GotoTargetMicrostepsRA;
            }
            else
            {
                bool FoundTarget = false;
                if (FORWARD == AxisDirectionRA)
                {
                    if (CurrentEncoderMicrostepsRA < OldEncoder)
                    {
                        // 两个范围进行搜索
                        if ((GotoTargetMicrostepsRA >= OldEncoder) &&
                                (GotoTargetMicrostepsRA <= MICROSTEPS_PER_REVOLUTION))
                            FoundTarget = true;
                        else if ((GotoTargetMicrostepsRA >= 0) &&
                                 (GotoTargetMicrostepsRA <= CurrentEncoderMicrostepsRA))
                            FoundTarget = true;
                    }
                    else if ((GotoTargetMicrostepsRA >= OldEncoder) &&
                             (GotoTargetMicrostepsRA <= CurrentEncoderMicrostepsRA))
                        FoundTarget = true;
                }
                else
                {
                    if (CurrentEncoderMicrostepsRA > OldEncoder)
                    {
                        // 两个范围进行搜索
                        if ((GotoTargetMicrostepsRA >= 0) && (GotoTargetMicrostepsRA <= OldEncoder))
                            FoundTarget = true;
                        else if ((GotoTargetMicrostepsRA >= CurrentEncoderMicrostepsRA) &&
                                 (GotoTargetMicrostepsRA <= MICROSTEPS_PER_REVOLUTION))
                            FoundTarget = true;
                    }
                    else if ((GotoTargetMicrostepsRA >= CurrentEncoderMicrostepsRA) &&
                             (GotoTargetMicrostepsRA <= OldEncoder))
                        FoundTarget = true;
                }
                if (FoundTarget)
                {
                    AxisStatusRA               = STOPPED;
                    CurrentEncoderMicrostepsRA = GotoTargetMicrostepsRA;
                }
            }
            DEBUGF(DBG_SIMULATOR, "TimerHit SlewingTo - RA New Encoder %d New Status %d", CurrentEncoderMicrostepsRA,
                   AxisStatusRA);
            break;
        }
    }

    // DEC 轴
    SlewSteps = dt * AxisSlewRateDEC;

    switch (AxisStatusDEC)
    {
        case STOPPED:
            // 什么都不做
            break;

        case SLEWING:
        {
            DEBUGF(DBG_SIMULATOR,
                   "TimerHit Slewing - DEC Current Encoder %ld SlewSteps %d Direction %ld Target %ld Status %d",
                   CurrentEncoderMicrostepsDEC, SlewSteps, AxisDirectionDEC, GotoTargetMicrostepsDEC, AxisStatusDEC);

            // 更新编码器
            SlewSteps = SlewSteps % MICROSTEPS_PER_REVOLUTION; // 以防万一 ;-)
            if (FORWARD == AxisDirectionDEC)
                CurrentEncoderMicrostepsDEC += SlewSteps;
            else
                CurrentEncoderMicrostepsDEC -= SlewSteps;
            if (CurrentEncoderMicrostepsDEC > MAX_DEC)
            {
                CurrentEncoderMicrostepsDEC = MAX_DEC;
                AxisStatusDEC               = STOPPED; // 碰到缓冲区
                DEBUG(DBG_SIMULATOR, "TimerHit - DEC 轴在 MAX_DEC 处碰到缓冲区");
            }
            else if (CurrentEncoderMicrostepsDEC < MIN_DEC)
            {
                CurrentEncoderMicrostepsDEC = MIN_DEC;
                AxisStatusDEC               = STOPPED; // 碰到缓冲区
                DEBUG(DBG_SIMULATOR, "TimerHit - DEC 轴在 MIN_DEC 处碰到缓冲区");
            }

            DEBUGF(DBG_SIMULATOR, "TimerHit Slewing - DEC New Encoder %d New Status %d", CurrentEncoderMicrostepsDEC,
                   AxisStatusDEC);
            break;
        }

        case SLEWING_TO:
        {
            DEBUGF(DBG_SIMULATOR,
                   "TimerHit SlewingTo - DEC Current Encoder %ld SlewSteps %d Direction %ld Target %ld Status %d",
                   CurrentEncoderMicrostepsDEC, SlewSteps, AxisDirectionDEC, GotoTargetMicrostepsDEC, AxisStatusDEC);

            // 计算到目标的步数
            int StepsToTarget;
            if (FORWARD == AxisDirectionDEC)
            {
                if (CurrentEncoderMicrostepsDEC <= GotoTargetMicrostepsDEC)
                    StepsToTarget = GotoTargetMicrostepsDEC - CurrentEncoderMicrostepsDEC;
                else
                    StepsToTarget = CurrentEncoderMicrostepsDEC - GotoTargetMicrostepsDEC;
            }
            else
            {
                // 轴在反向
                if (CurrentEncoderMicrostepsDEC >= GotoTargetMicrostepsDEC)
                    StepsToTarget = CurrentEncoderMicrostepsDEC - GotoTargetMicrostepsDEC;
                else
                    StepsToTarget = GotoTargetMicrostepsDEC - CurrentEncoderMicrostepsDEC;
            }
            if (StepsToTarget <= SlewSteps)
            {
                // 目标在此刻被击中
                AxisStatusDEC               = STOPPED;
                CurrentEncoderMicrostepsDEC = GotoTargetMicrostepsDEC;
            }
            else
            {
                if (FORWARD == AxisDirectionDEC)
                    CurrentEncoderMicrostepsDEC += SlewSteps;
                else
                    CurrentEncoderMicrostepsDEC -= SlewSteps;
                if (CurrentEncoderMicrostepsDEC < 0)
                    CurrentEncoderMicrostepsDEC += MICROSTEPS_PER_REVOLUTION;
                else if (CurrentEncoderMicrostepsDEC >= MICROSTEPS_PER_REVOLUTION)
                    CurrentEncoderMicrostepsDEC -= MICROSTEPS_PER_REVOLUTION;
            }

            DEBUGF(DBG_SIMULATOR, "TimerHit SlewingTo - DEC New Encoder %d New Status %d", CurrentEncoderMicrostepsDEC,
                   AxisStatusDEC);
            break;
        }
    }

    INDI::Telescope::TimerHit(); // 这将调用 ReadScopeStatus

    // 好的，我在 ReadScopeStatus 中更新了天体参考系 RA/DEC
    // 现在处理跟踪状态
    switch (TrackState)
    {
        case SCOPE_SLEWING:
            if ((STOPPED == AxisStatusRA) && (STOPPED == AxisStatusDEC))
            {
                if (CoordSP.isSwitchOn("TRACK"))
                {
                    // Goto 已完成，开始跟踪
                    DEBUG(DBG_SIMULATOR, "TimerHit - Goto 完成，开始跟踪");
                    TrackState = SCOPE_TRACKING;
                    // 继续跟踪情况
                }
                else
                {
                    TrackState = SCOPE_IDLE;
                    break;
                }
            }
            break;

        case SCOPE_TRACKING:
        {
            // 继续或开始跟踪
            // 计算安装在 POLLMS 时间内需要的位置
            // POLLMS 硬编码为一秒
            // TODO 可能需要更长时间才能获得有意义的结果
            double JulianOffset = 1.0 / (24.0 * 60 * 60);
            TelescopeDirectionVector TDV;
            INDI::IHorizontalCoordinates AltAz { 0, 0 };

            if (TransformCelestialToTelescope(CurrentTrackingTarget.rightascension, CurrentTrackingTarget.declination, JulianOffset,
                                              TDV))
                AltitudeAzimuthFromTelescopeDirectionVector(TDV, AltAz);
            else
            {

                INDI::IEquatorialCoordinates EquatorialCoordinates { 0, 0 };
                EquatorialCoordinates.rightascension  = CurrentTrackingTarget.rightascension;
                EquatorialCoordinates.declination = CurrentTrackingTarget.declination;
                INDI::EquatorialToHorizontal(&EquatorialCoordinates, &m_Location, ln_get_julian_from_sys() + JulianOffset, &AltAz);
                INDI::EquatorialToHorizontal(&EquatorialCoordinates, &m_Location, ln_get_julian_from_sys() + JulianOffset,
                                             &AltAz);

            }

            // 我的高度编码器范围为 -90 到 +90
            if ((AltAz.altitude > 90.0) || (AltAz.altitude < -90.0))
            {
                DEBUG(DBG_SIMULATOR, "TimerHit tracking - Altitude out of range");
                // 这不应该发生
                return;
            }

            // 我的极轴编码器范围为 0 到 +360
            if ((AltAz.azimuth > 360.0) || (AltAz.azimuth < -360.0))
            {
                DEBUG(DBG_SIMULATOR, "TimerHit tracking - Azimuth out of range");
                // 这不应该发生
                return;
            }

            if (AltAz.azimuth < 0.0)
            {
                DEBUG(DBG_SIMULATOR, "TimerHit tracking - Azimuth negative");
                AltAz.azimuth = 360.0 + AltAz.azimuth;
            }

            long AltitudeOffsetMicrosteps = int(AltAz.altitude * MICROSTEPS_PER_DEGREE - CurrentEncoderMicrostepsDEC);
            long AzimuthOffsetMicrosteps  = int(AltAz.azimuth * MICROSTEPS_PER_DEGREE - CurrentEncoderMicrostepsRA);

            DEBUGF(DBG_SIMULATOR, "TimerHit - Tracking AltitudeOffsetMicrosteps %d AzimuthOffsetMicrosteps %d",
                   AltitudeOffsetMicrosteps, AzimuthOffsetMicrosteps);

            if (0 != AzimuthOffsetMicrosteps)
            {
                // 计算到达该位置所需的步进速率
                // 在正确的时间。这很简单，因为间隔为一秒
                if (AzimuthOffsetMicrosteps > 0)
                {
                    if (AzimuthOffsetMicrosteps < MICROSTEPS_PER_REVOLUTION / 2.0)
                    {
                        // 前进
                        AxisDirectionRA = FORWARD;
                        AxisSlewRateRA  = AzimuthOffsetMicrosteps;
                    }
                    else
                    {
                        // 反向
                        AxisDirectionRA = REVERSE;
                        AxisSlewRateRA  = MICROSTEPS_PER_REVOLUTION - AzimuthOffsetMicrosteps;
                    }
                }
                else
                {
                    AzimuthOffsetMicrosteps = std::abs(AzimuthOffsetMicrosteps);
                    if (AzimuthOffsetMicrosteps < MICROSTEPS_PER_REVOLUTION / 2.0)
                    {
                        // 前进
                        AxisDirectionRA = REVERSE;
                        AxisSlewRateRA  = AzimuthOffsetMicrosteps;
                    }
                    else
                    {
                        // 反向
                        AxisDirectionRA = FORWARD;
                        AxisSlewRateRA  = MICROSTEPS_PER_REVOLUTION - AzimuthOffsetMicrosteps;
                    }
                }
                AxisSlewRateRA  = std::abs(AzimuthOffsetMicrosteps);
                AxisDirectionRA = AzimuthOffsetMicrosteps > 0 ? FORWARD : REVERSE; // !!!! 小心无惯性安装
                AxisStatusRA    = SLEWING;
                DEBUGF(DBG_SIMULATOR, "TimerHit - Tracking AxisSlewRateRA %lf AxisDirectionRA %d", AxisSlewRateRA,
                       AxisDirectionRA);
            }
            else
            {
                // 无事可做 - 停止轴
                AxisStatusRA = STOPPED; // !!!! 小心无惯性安装
                DEBUG(DBG_SIMULATOR, "TimerHit - Tracking nothing to do stopping RA axis");
            }

            if (0 != AltitudeOffsetMicrosteps)
            {
                // 计算到达该位置所需的步进速率
                // 在正确的时间。
                AxisSlewRateDEC  = std::abs(AltitudeOffsetMicrosteps);
                AxisDirectionDEC = AltitudeOffsetMicrosteps > 0 ? FORWARD : REVERSE; // !!!! 小心无惯性安装
                AxisStatusDEC    = SLEWING;
                DEBUGF(DBG_SIMULATOR, "TimerHit - Tracking AxisSlewRateDEC %lf AxisDirectionDEC %d", AxisSlewRateDEC,
                       AxisDirectionDEC);
            }
            else
            {
                // 无事可做 - 停止轴
                AxisStatusDEC = STOPPED; // !!!! 小心无惯性安装
                DEBUG(DBG_SIMULATOR, "TimerHit - Tracking nothing to do stopping DEC axis");
            }

            break;
        }

        default:
            break;
    }

    TraceThisTick = false;
}

bool ScopeSim::updateLocation(double latitude, double longitude, double elevation)
{
    UpdateLocation(latitude, longitude, elevation);
    return true;
}
