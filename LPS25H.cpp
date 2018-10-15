#include "LPS25H.h"

LPS25H::LPS25H(const char* devicePath, uint8_t deviceAddress)
{
    if ((device = open(devicePath, O_RDWR)) < 0) {
        throw std::runtime_error("Failed to open the I2C bus.");
    }

    if (ioctl(device, I2C_SLAVE, deviceAddress) < 0) {
        close(device);
        throw std::runtime_error("Failed to configure the I2C device.");
    }

    int32_t data = 0;

    data = i2c_smbus_read_byte_data(device, LPS25H_REGISTER_WHO_AM_I);

    if (data != 0xBD) {
        throw std::runtime_error("Failed to verify the device identity.");
    }

    data = 0x00000000;

    data |= LPS25H_BDU_ENABLE;
    data |= LPS25H_DATARATE_1_HZ;
    data |= LPS25H_AVERAGE_PRESSURE_8_SAMPLES;
    data |= LPS25H_AVERAGE_TEMPERATURE_8_SAMPLES;

    i2c_smbus_write_byte_data(device, LPS25H_REGISTER_CTRL_REG1, (uint8_t)data);
}

double LPS25H::getPressure()
{
    int32_t data = 0;
    int32_t pressure = 0;

    data = i2c_smbus_read_byte_data(device, LPS25H_REGISTER_STATUS_REG);

    if (!(data & 0b10)) {
        throw std::runtime_error("The pressure sensor is not ready.");
    }

    data = i2c_smbus_read_byte_data(device, LPS25H_REGISTER_PRESS_OUT_XL);
    pressure = data;

    data = i2c_smbus_read_byte_data(device, LPS25H_REGISTER_PRESS_OUT_L);
    pressure |= data << 8;

    data = i2c_smbus_read_byte_data(device, LPS25H_REGISTER_PRESS_OUT_H);
    pressure |= data << 16;

    return pressure / 4096.0;
}

double LPS25H::getTemperature()
{
    int32_t data = 0;
    int32_t temperature = 0;

    data = i2c_smbus_read_byte_data(device, LPS25H_REGISTER_STATUS_REG);

    if (!(data &0b01)) {
        throw std::runtime_error("The temperature sensor is not ready.");
    }

    data = i2c_smbus_read_byte_data(device, LPS25H_REGISTER_TEMP_OUT_L);
    temperature = data;

    data = i2c_smbus_read_byte_data(device, LPS25H_REGISTER_TEMP_OUT_H);
    temperature |= data << 8;

    if (temperature > 32768) {
        temperature -= 65536;
    }

    return 42.5 + (temperature / 480.0);
}

void LPS25H::powerDown()
{
    int32_t data = 0;

    data = i2c_smbus_read_byte_data(device, LPS25H_REGISTER_CTRL_REG1);

    data &= ~(0b1 << 7);
    data |= LPS25H_POWER_DOWN;

    i2c_smbus_write_byte_data(device, LPS25H_REGISTER_CTRL_REG1, (uint8_t)data);
}

void LPS25H::powerUp()
{
    int32_t data = 0;

    data = i2c_smbus_read_byte_data(device, LPS25H_REGISTER_CTRL_REG1);

    data &= ~(0b1 << 7);
    data |= LPS25H_POWER_UP;

    i2c_smbus_write_byte_data(device, LPS25H_REGISTER_CTRL_REG1, (uint8_t)data);
}

void LPS25H::setAveragePressureSamples(LPS25HAveragePressureSamples_t averagePressureSamples)
{
    int32_t data = 0;

    data = i2c_smbus_read_byte_data(device, LPS25H_REGISTER_CTRL_REG1);

    data &= ~0b11;
    data |= averagePressureSamples;

    i2c_smbus_write_byte_data(device, LPS25H_REGISTER_CTRL_REG1, (uint8_t)data);
}

void LPS25H::setAverageTemperatureSamples(LPS25HAverageTemperatureSamples_t averageTemperatureSamples)
{
    int32_t data = 0;

    data = i2c_smbus_read_byte_data(device, LPS25H_REGISTER_CTRL_REG1);

    data &= ~(0b11 << 2);
    data |= averageTemperatureSamples;

    i2c_smbus_write_byte_data(device, LPS25H_REGISTER_CTRL_REG1, (uint8_t)data);
}

void LPS25H::setDataRate(LPS25HDataRate_t dataRate)
{
    int32_t data = 0;

    data = i2c_smbus_read_byte_data(device, LPS25H_REGISTER_CTRL_REG1);

    data &= ~(0b111 << 4);
    data |= dataRate;

    i2c_smbus_write_byte_data(device, LPS25H_REGISTER_CTRL_REG1, (uint8_t)data);
}

void LPS25H::triggerMeasurement()
{
    int32_t data = 0;

    data = i2c_smbus_read_byte_data(device, LPS25H_REGISTER_CTRL_REG1);

    if ((data & (0b111 << 4)) == LPS25H_DATARATE_ONE_SHOT) {
        i2c_smbus_write_byte_data(device, LPS25H_REGISTER_CTRL_REG2, 0b1);
    }
}

LPS25H::~LPS25H()
{
    close(device);
}