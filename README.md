# LPS25H driver

## Description

A C++ driver for the LPS25H atmospheric pressure and temperature sensor manufactured by STMicroelectronics and used in the
RaspberryPi Sense Hat board.

## License

This piece of software is available under the terms of the [MIT License](LICENSE).

## Changelog

**r1.0.0**

* Initial release.

## Example

```cpp
#include "LPS25H.h"
#include <iostream>

int main(int argc, char** argv)
{
    double pressure, temperature;

    LPS25H sensor("/dev/i2c-1");
    sensor.powerUp();

    pressure = sensor.getPressure();
    std::cout << "Pressure: " << pressure << " hPa" << std::endl;

    temperature = sensor.getTemperature();
    std::cout << "Temperature: " << temperature << " °C" << std::endl;

    return 0;
}
```

## Documentation

### LPS25H::LPS25H(const char* devicePath, uint8_t deviceAddress = LPS25H_DEVICE_ADDRESS)
Creates a LPS25H object.

The *devicePath* parameter corresponds to the path of the I2C bus on the system.  
The optional parameter *deviceAddress* allows you to override the address of the sensor, in case you are using a
standalone sensor or a modified version of the Sense Hat board.

Upon creation of the object, the sensor is configured with the following options:

|Option|Value|
|--|--|
|Output data rate|LPS25H_DATARATE_1_HZ|
|Pressure samples|LPS25H_AVERAGE_PRESSURE_8_SAMPLES|
|Temperature samples|LPS25H_AVERAGE_TEMPERATURE_8_SAMPLES|

Throws an `std::runtime_error` exception if the communication with the sensor fails for any reason.

### LPS25H::~LPS25H()
Destroys the object, closing the connection to the sensor.

### double LPS25H::getPressure()
Returns the atmospheric pressure value measured by the sensor, in hectopascals.

Throws an `std::runtime_error` exception if the atmospheric pressure value can't be read.

### double LPS25H::getTemperature()
Returns the temperature value measured by the sensor, in Celsius degrees.

Throws an `std::runtime_error` exception if the temperature value can't be read.

### void LPS25H::powerDown()
Turns the sensor off, to reduce power consumption.

### void LPS25H::powerUp()
Turns the sensor on.

### void LPS25H::setAveragePressureSamples(LPS25HAveragePressureSamples_t averagePressureSamples)
Sets the number of samples used to compute the atmospheric pressure value.

The *averagePressureSamples* parameter can take one of the following values:

|Value|
|--|
|LPS25H_AVERAGE_PRESSURE_8_SAMPLES|
|LPS25H_AVERAGE_PRESSURE_32_SAMPLES|
|LPS25H_AVERAGE_PRESSURE_128_SAMPLES|
|LPS25H_AVERAGE_PRESSURE_512_SAMPLES|

### void LPS25H::setAverageTemperatureSamples(LPS25HAverageTemperatureSamples_t averageTemperatureSamples)
Sets the number of samples used to compute the temperature value.

The *averageTemperatureSamples* parameter can take one of the following values:

|Value|
|--|
|LPS25H_AVERAGE_TEMPERATURE_8_SAMPLES|
|LPS25H_AVERAGE_TEMPERATURE_16_SAMPLES|
|LPS25H_AVERAGE_TEMPERATURE_32_SAMPLES|
|LPS25H_AVERAGE_TEMPERATURE_64_SAMPLES|

### void LPS25H::setDataRate(LPS25HDataRate_t dataRate)
Sets the output data rate of the sensor.

The *dataRate* parameter can take one of the following values:

|Value|Measurement interval|
|--|--|
|LPS25H_DATARATE_ONE_SHOT|Manual|
|LPS25H_DATARATE_1_HZ|1000 ms|
|LPS25H_DATARATE_7_HZ|142.8 ms|
|LPS25H_DATARATE_12_5_HZ|80 ms|
|LPS25H_DATARATE_25_HZ|40 ms|

Trying to read the atmospheric pressure or temperature values more frequently than permitted by the measurement interval will raise an exception.

### void LPS25H::triggerMeasurement()
Manually triggers a measurement of atmospheric pressure and temperature values.

If the output data rate of the sensor is set to `LPS25H_DATARATE_ONE_SHOT`, you must call this method to trigger a
measurement before any attempt to read the atmospheric pressure or temperature values.

## Useful resources

[LPS25H datasheet](https://www.st.com/resource/en/datasheet/lps25h.pdf)
