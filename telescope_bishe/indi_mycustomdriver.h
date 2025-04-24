#pragma once

#include "inditelescope.h"

class MyCustomDriver : public INDI::Telescope
{
    public:
        MyCustomDriver();

    protected:
        bool Handshake() override;
        
        const char *getDefaultName() override;
        bool initProperties() override;
        bool ReadScopeStatus() override;
        bool Goto(double, double) override;
        bool Abort() override;
        bool Connect() override;
        bool Disconnect() override;
        
    private:
        double currentRA {0};
        double currentDEC {90};
        double targetRA {0};
        double targetDEC {0};


        uint8_t DBG_SCOPE { INDI::Logger::DBG_IGNORE };
        static const uint8_t SLEW_RATE = 3;
    
};
