#include "mydevicedriver.h"

#include <memory>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <connectionplugins/connectionserial.h>

// We declare an auto pointer to MyDeviceDriver
static std::unique_ptr<MyDeviceDriver> mydevice(new MyDeviceDriver());

MyDeviceDriver::MyDeviceDriver()
{
    // Set the driver version
    setVersion(1, 0);

    // Set up the connection
    setConnectionMode(CONNECTION_SERIAL);
    serialConnection = new Connection::Serial(this);
    serialConnection->registerHandshake([&]() { return Handshake(); });
    serialConnection->setDefaultBaudRate(Connection::Serial::B_9600);
    serialConnection->setDefaultPort("/dev/ttyUSB0");
    registerConnection(serialConnection);
}

const char *MyDeviceDriver::getDefaultName()
{
    return "My Device";
}

bool MyDeviceDriver::initProperties()
{
    // Initialize the parent's properties
    INDI::DefaultDevice::initProperties();

    // Initialize power switch
    PowerSP[INDI_ENABLED].fill("POWER_ON", "On", ISS_OFF);
    PowerSP[INDI_DISABLED].fill("POWER_OFF", "Off", ISS_ON);
    PowerSP.fill(getDeviceName(), "POWER", "Power", MAIN_CONTROL_TAB, IP_RW, ISR_1OFMANY, 60, IPS_IDLE);

    // Initialize value number
    ValueNP[0].fill("VALUE", "Value", "%6.2f", 0, 100, 1, 50);
    ValueNP.fill(getDeviceName(), "DEVICE_VALUE", "Value", MAIN_CONTROL_TAB, IP_RW, 60, IPS_IDLE);

    // Add debug, simulation, and configuration controls
    addAuxControls();

    return true;
}

bool MyDeviceDriver::updateProperties()
{
    // Call the parent's updateProperties
    INDI::DefaultDevice::updateProperties();

    if (isConnected())
    {
        // Define properties when connected
        defineProperty(PowerSP);
        defineProperty(ValueNP);

        // Start the timer
        SetTimer(POLLMS);
    }
    else
    {
        // Delete properties when disconnected
        deleteProperty(PowerSP);
        deleteProperty(ValueNP);
    }

    return true;
}

bool MyDeviceDriver::ISNewNumber(const char *dev, const char *name, double values[], char *names[], int n)
{
    // Check if the message is for this device
    if (!strcmp(dev, getDeviceName()))
    {
        // Check if the message is for the value property
        if (!strcmp(name, ValueNP.name))
        {
            // Update the property values
            ValueNP.update(values, names, n);

            // Send the new value to the device
            char cmd[32];
            snprintf(cmd, sizeof(cmd), "SET_VALUE %.2f\r\n", ValueNP[0].getValue());
            if (!sendCommand(cmd))
            {
                LOG_ERROR("Failed to set value");
                ValueNP.setState(IPS_ALERT);
                ValueNP.apply();
                return false;
            }

            // Value set successfully
            LOG_INFO("Value set successfully");
            ValueNP.setState(IPS_OK);
            ValueNP.apply();
            return true;
        }
    }

    // If the message is not for this device or property, call the parent's ISNewNumber
    return INDI::DefaultDevice::ISNewNumber(dev, name, values, names, n);
}

bool MyDeviceDriver::ISNewSwitch(const char *dev, const char *name, ISState *states, char *names[], int n)
{
    // Check if the message is for this device
    if (!strcmp(dev, getDeviceName()))
    {
        // Check if the message is for the power property
        if (!strcmp(name, PowerSP.name))
        {
            // Update the property values
            PowerSP.update(states, names, n);

            // Send the power command to the device
            const char *cmd = (PowerSP[INDI_ENABLED].getState() == ISS_ON) ? "POWER_ON\r\n" : "POWER_OFF\r\n";
            if (!sendCommand(cmd))
            {
                LOG_ERROR("Failed to set power state");
                PowerSP.setState(IPS_ALERT);
                PowerSP.apply();
                return false;
            }

            // Power state set successfully
            LOG_INFO("Power state set successfully");
            PowerSP.setState(IPS_OK);
            PowerSP.apply();
            return true;
        }
    }

    // If the message is not for this device or property, call the parent's ISNewSwitch
    return INDI::DefaultDevice::ISNewSwitch(dev, name, states, names, n);
}

void MyDeviceDriver::TimerHit()
{
    // Check if the device is connected
    if (!isConnected())
        return;

    // Get the current value from the device
    char res[32];
    if (sendCommand("GET_VALUE\r\n", res, sizeof(res)))
    {
        // Parse the response
        float value;
        if (sscanf(res, "VALUE=%f", &value) == 1)
        {
            // Update the value property
            ValueNP[0].setValue(value);
            ValueNP.setState(IPS_OK);
            ValueNP.apply();
        }
    }

    // Get the current power state from the device
    if (sendCommand("GET_POWER\r\n", res, sizeof(res)))
    {
        // Parse the response
        if (strstr(res, "POWER=ON"))
        {
            // Update the power property
            PowerSP[INDI_ENABLED].setState(ISS_ON);
            PowerSP[INDI_DISABLED].setState(ISS_OFF);
            PowerSP.setState(IPS_OK);
            PowerSP.apply();
        }
        else if (strstr(res, "POWER=OFF"))
        {
            // Update the power property
            PowerSP[INDI_ENABLED].setState(ISS_OFF);
            PowerSP[INDI_DISABLED].setState(ISS_ON);
            PowerSP.setState(IPS_OK);
            PowerSP.apply();
        }
    }

    // Set the timer for the next update
    SetTimer(POLLMS);
}

bool MyDeviceDriver::Connect()
{
    // Call the parent's Connect method
    bool result = INDI::DefaultDevice::Connect();

    if (result)
    {
        // Get the file descriptor for the serial port
        PortFD = serialConnection->getPortFD();

        // Send a test command to verify the connection
        if (!sendCommand("PING\r\n"))
        {
            LOG_ERROR("Failed to communicate with the device");
            return false;
        }

        LOG_INFO("Device connected successfully");
    }

    return result;
}

bool MyDeviceDriver::Disconnect()
{
    // Close the serial port
    if (PortFD > 0)
    {
        close(PortFD);
        PortFD = -1;
    }

    // Call the parent's Disconnect method
    return INDI::DefaultDevice::Disconnect();
}

bool MyDeviceDriver::sendCommand(const char *cmd, char *res, int reslen)
{
    // Check if the port is open
    if (PortFD < 0)
    {
        LOG_ERROR("Serial port not open");
        return false;
    }

    // Write the command
    int nbytes_written = write(PortFD, cmd, strlen(cmd));
    if (nbytes_written < 0)
    {
        LOGF_ERROR("Error writing to device: %s", strerror(errno));
        return false;
    }

    // If no response is expected, return success
    if (res == nullptr || reslen <= 0)
        return true;

    // Read the response
    if (!readResponse(res, reslen))
    {
        LOG_ERROR("Error reading response from device");
        return false;
    }

    return true;
}

bool MyDeviceDriver::readResponse(char *res, int reslen)
{
    // Check if the port is open
    if (PortFD < 0)
    {
        LOG_ERROR("Serial port not open");
        return false;
    }

    // Read the response
    int nbytes_read = read(PortFD, res, reslen - 1);
    if (nbytes_read < 0)
    {
        LOGF_ERROR("Error reading from device: %s", strerror(errno));
        return false;
    }

    // Null-terminate the response
    res[nbytes_read] = '\0';

    return true;
}

