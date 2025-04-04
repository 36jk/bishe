/*
   INDI 开发者手册
   教程 #2

   "简单望远镜驱动程序"

   我们开发了一个简单的望远镜模拟器。

   请参考 README，其中包含有关如何构建此驱动程序并将其与兼容 INDI 的客户端一起使用的说明。

*/

/** \file simplescope.h
    \brief 构建一个基本的 INDI 望远镜设备，用于模拟 GOTO 命令。
    \author Jasem Mutlaq

    \example simplescope.h
    一个简单的 GOTO 望远镜，模拟平移操作。
*/

#pragma once

#include "inditelescope.h"

class SimpleScope : public INDI::Telescope
{
    public:
        SimpleScope();

    protected:
        bool Handshake() override;

        const char *getDefaultName() override;
        bool initProperties() override;

        // 望远镜特定功能
        bool ReadScopeStatus() override;
        bool Goto(double, double) override;
        bool Abort() override;

    private:
        double currentRA {0};  // 当前赤经
        double currentDEC {90};  // 当前赤纬
        double targetRA {0};  // 目标赤经
        double targetDEC {0};  // 目标赤纬

        // 用于写入安装座日志的调试通道
        // 默认的 INDI::Logger 调试/日志记录通道包括 Message、Warn、Error 和 Debug
        // 由于望远镜信息可能非常详细，我们创建了另一个通道 SCOPE 专门用于额外的调试日志。
        // 用户可以根据需要打开/关闭此通道。
        uint8_t DBG_SCOPE { INDI::Logger::DBG_IGNORE };

        // 平移速率（度/秒）
        static const uint8_t SLEW_RATE = 3;
};
