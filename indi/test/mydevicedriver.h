#pragma once

#include <defaultdevice.h>

class MyDeviceDriver : public INDI::DefaultDevice
{
public:
    MyDeviceDriver();
    virtual ~MyDeviceDriver() = default;

    // DefaultDevice overrides
    virtual const char *getDefaultName() override;
    virtual bool initProperties() override;
    virtual bool updateProperties() override;
    virtual bool ISNewNumber(const char *dev, const char *name, double values[], char *names[], int n) override;
    virtual bool ISNewSwitch(const char *dev, const char *name, ISState *states, char *names[], int n) override;
    virtual void TimerHit() override;

    // Connection overrides
    virtual bool Connect() override;
    virtual bool Disconnect() override;

private:
    // Helper methods
    bool sendCommand(const char *cmd, char *res = nullptr, int reslen = 0);
    bool readResponse(char *res, int reslen);

    // Properties
    INDI::PropertySwitch PowerSP {2};
    // Use built-in INDI_ENABLED and INDI_DISABLED for toggle switches

    INDI::PropertyNumber ValueNP {1};
    // No need for enum when property size is 1

    // Connection
    int PortFD = -1;
};

