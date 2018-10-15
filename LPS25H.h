#ifndef LPS25H_H
#define LPS25H_H

#include <stdexcept>

#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

static constexpr auto LPS25H_DEVICE_ADDRESS		= 0x5C;

static constexpr auto LPS25H_WHO_AM_I_REG		= 0x0F;
static constexpr auto LPS25H_WHO_AM_I_RESPONSE	= 0xBD;

static constexpr auto LPS25H_POWER_UP			= 0x80;
static constexpr auto LPS25H_ODR_SET			= 0x10;
static constexpr auto LPS25H_BDU_SET			= 0x04;

static constexpr auto LPS25H_CTRL_REG1			= 0x20;
static constexpr auto LPS25H_CTRL_REG2			= 0x21;
static constexpr auto LPS25H_CTRL_REG3			= 0x22;
static constexpr auto LPS25H_CTRL_REG4			= 0x23;

static constexpr auto LPS25H_STATUS_REG			= 0x27;
static constexpr auto LPS25H_PRESSURE_XL_REG	= 0x28;
static constexpr auto LPS25H_PRESSURE_L_REG		= 0x29;
static constexpr auto LPS25H_PRESSURE_H_REG		= 0x2A;
static constexpr auto LPS25H_TEMP_L_REG			= 0x2B;
static constexpr auto LPS25H_TEMP_H_REG			= 0x2C;

static constexpr auto LPS25H_TEMPERATURE_READY	= 0x01;
static constexpr auto LPS25H_PRESSURE_READY		= 0x02;

class LPS25H
{
public:
	explicit LPS25H(const char* devicePath, uint8_t deviceAddress = LPS25H_DEVICE_ADDRESS);
	virtual ~LPS25H();

	void initialize();
	void shutdown();

	double getPressure();
	double getTemperature();

private:
	int device;
};

#endif // LPS25H_H