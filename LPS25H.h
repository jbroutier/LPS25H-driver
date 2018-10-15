#ifndef LPS25H_H
#define LPS25H_H

#include <stdexcept>

#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

static constexpr auto LPS25H_DEVICE_ADDRESS = 0x5C;

class LPS25H
{
public:
	explicit LPS25H(const char* devicePath, uint8_t deviceAddress = LPS25H_DEVICE_ADDRESS);
	virtual ~LPS25H();

	typedef enum
	{
		LPS25H_REGISTER_REF_P_XL				= 0x08,
		LPS25H_REGISTER_REF_P_L					= 0x09,
		LPS25H_REGISTER_REF_P_H					= 0x0A,
		LPS25H_REGISTER_WHO_AM_I				= 0x0F,
		LPS25H_REGISTER_RES_CONF				= 0x10,
		LPS25H_REGISTER_CTRL_REG1				= 0x20,
		LPS25H_REGISTER_CTRL_REG2				= 0x21,
		LPS25H_REGISTER_CTRL_REG3				= 0x22,
		LPS25H_REGISTER_CTRL_REG4				= 0x23,
		LPS25H_REGISTER_INTERRUPT_CFG			= 0x24,
		LPS25H_REGISTER_INT_SOURCE				= 0x25,
		LPS25H_REGISTER_STATUS_REG				= 0x27,
		LPS25H_REGISTER_PRESS_OUT_XL			= 0x28,
		LPS25H_REGISTER_PRESS_OUT_L				= 0x29,
		LPS25H_REGISTER_PRESS_OUT_H				= 0x2A,
		LPS25H_REGISTER_TEMP_OUT_L				= 0x2B,
		LPS25H_REGISTER_TEMP_OUT_H				= 0x2C,
		LPS25H_REGISTER_FIFO_CTRL				= 0x2E,
		LPS25H_REGISTER_FIFO_STATUS				= 0x2F,
		LPS25H_REGISTER_THS_P_L					= 0x30,
		LPS25H_REGISTER_THS_P_H					= 0x31,
		LPS25H_REGISTER_RPDS_L					= 0x39,
		LPS25H_REGISTER_RPDS_H					= 0x3A,
	} LPS25HRegisters_t;

	typedef enum
	{
		LPS25H_AVERAGE_PRESSURE_8_SAMPLES		= 0b00,
		LPS25H_AVERAGE_PRESSURE_32_SAMPLES		= 0b01,
		LPS25H_AVERAGE_PRESSURE_128_SAMPLES		= 0b10,
		LPS25H_AVERAGE_PRESSURE_512_SAMPLES		= 0b11,
	} LPS25HAveragePressureSamples_t;

	typedef enum
	{
		LPS25H_AVERAGE_TEMPERATURE_8_SAMPLES	= (0b00 << 2),
		LPS25H_AVERAGE_TEMPERATURE_16_SAMPLES	= (0b01 << 2),
		LPS25H_AVERAGE_TEMPERATURE_32_SAMPLES	= (0b10 << 2),
		LPS25H_AVERAGE_TEMPERATURE_64_SAMPLES	= (0b11 << 2),
	} LPS25HAverageTemperatureSamples_t;

	typedef enum
	{
		LPS25H_DATARATE_ONE_SHOT				= (0b000 << 4),
		LPS25H_DATARATE_1_HZ					= (0b001 << 4),
		LPS25H_DATARATE_7_HZ					= (0b010 << 4),
		LPS25H_DATARATE_12_5_HZ					= (0b011 << 4),
		LPS25H_DATARATE_25_HZ					= (0b100 << 4),
	} LPS25HDataRate_t;

	typedef enum
	{
		LPS25H_BDU_DISABLE						= (0b0 << 2),
		LPS25H_BDU_ENABLE						= (0b1 << 2),
	} LPS25HDataUpdateMode_t;

	typedef enum
	{
		LPS25H_POWER_DOWN						= (0b0 << 7),
		LPS25H_POWER_UP							= (0b1 << 7),
	} LPS25HPowerMode_t;

	void powerUp();
	void powerDown();

	double getPressure();
	double getTemperature();
	void triggerMeasurement();

	void setAveragePressureSamples(LPS25HAveragePressureSamples_t averagePressureSamples);
	void setAverageTemperatureSamples(LPS25HAverageTemperatureSamples_t averageTemperatureSamples);
	void setDataRate(LPS25HDataRate_t dataRate);

private:
	int device;
};

#endif // LPS25H_H