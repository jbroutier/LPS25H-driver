#ifndef LPS25H_H
#define LPS25H_H

#include <stdexcept>

#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#include "LPS25H_Registers.h"
#include "LPS25H_Types.h"

static constexpr auto LPS25H_DEVICE_ADDRESS = 0x5C;

class LPS25H
{
public:
    explicit LPS25H(const char* devicePath, uint8_t deviceAddress = LPS25H_DEVICE_ADDRESS);
    virtual ~LPS25H();

    double getPressure();
    double getTemperature();

    void powerDown();
    void powerUp();

    void setAveragePressureSamples(LPS25HAveragePressureSamples_t averagePressureSamples);
    void setAverageTemperatureSamples(LPS25HAverageTemperatureSamples_t averageTemperatureSamples);
    void setDataRate(LPS25HDataRate_t dataRate);
    
    void triggerMeasurement();

private:
    int device;
};

#endif // LPS25H_H
