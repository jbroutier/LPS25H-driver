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

	data = i2c_smbus_read_byte_data(device, LPS25H_WHO_AM_I_REG);

	if (!(data & LPS25H_WHO_AM_I_RESPONSE)) {
		throw std::runtime_error("Failed to verify the device identity.");
	}

	i2c_smbus_write_byte_data(device, LPS25H_CTRL_REG1, 0x00);
	i2c_smbus_write_byte_data(device, LPS25H_CTRL_REG1, LPS25H_ODR_SET + LPS25H_BDU_SET);
}

double LPS25H::getPressure()
{
	int32_t data = 0;
	int32_t pressure = 0;

	data = i2c_smbus_read_byte_data(device, LPS25H_STATUS_REG);

	if (!(data & LPS25H_PRESSURE_READY)) {
		throw std::runtime_error("The pressure sensor is not ready.");
	}

	data = i2c_smbus_read_byte_data(device, LPS25H_PRESSURE_XL_REG);
	pressure = data;

	data = i2c_smbus_read_byte_data(device, LPS25H_PRESSURE_L_REG);
	pressure |= data << 8;

	data = i2c_smbus_read_byte_data(device, LPS25H_PRESSURE_H_REG);
	pressure |= data << 16;

	return pressure / 4096.0;
}

double LPS25H::getTemperature()
{
	int32_t data = 0;
	int32_t temperature = 0;

	data = i2c_smbus_read_byte_data(device, LPS25H_STATUS_REG);

	if (!(data & LPS25H_TEMPERATURE_READY)) {
		throw std::runtime_error("The temperature sensor is not ready.");
	}

	data = i2c_smbus_read_byte_data(device, LPS25H_TEMP_L_REG);
	temperature = data;

	data = i2c_smbus_read_byte_data(device, LPS25H_TEMP_H_REG);
	temperature |= data << 8;

	if (temperature > 32768) {
		temperature -= 65536;
	}

	return 42.5 + (temperature / 480.0);
}

void LPS25H::initialize()
{
	int32_t data = 0;

	data = i2c_smbus_read_byte_data(device, LPS25H_CTRL_REG1);

	data |= LPS25H_POWER_UP;

	i2c_smbus_write_byte_data(device, LPS25H_CTRL_REG1, (uint8_t)data);
}

void LPS25H::shutdown()
{
	int32_t data = 0;

	data = i2c_smbus_read_byte_data(device, LPS25H_CTRL_REG1);

	data &= ~LPS25H_POWER_UP;

	i2c_smbus_write_byte_data(device, LPS25H_CTRL_REG1, (uint8_t)data);
}

LPS25H::~LPS25H()
{
	close(device);
}