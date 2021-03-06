#ifndef LPS25H_TYPES_H
#define LPS25H_TYPES_H

typedef enum
{
    LPS25H_AVERAGE_PRESSURE_8_SAMPLES   = 0b00,
    LPS25H_AVERAGE_PRESSURE_32_SAMPLES  = 0b01,
    LPS25H_AVERAGE_PRESSURE_128_SAMPLES = 0b10,
    LPS25H_AVERAGE_PRESSURE_512_SAMPLES = 0b11,
} LPS25HAveragePressureSamples_t;

typedef enum
{
    LPS25H_AVERAGE_TEMPERATURE_8_SAMPLES  = (0b00 << 2),
    LPS25H_AVERAGE_TEMPERATURE_16_SAMPLES = (0b01 << 2),
    LPS25H_AVERAGE_TEMPERATURE_32_SAMPLES = (0b10 << 2),
    LPS25H_AVERAGE_TEMPERATURE_64_SAMPLES = (0b11 << 2),
} LPS25HAverageTemperatureSamples_t;

typedef enum
{
    LPS25H_DATARATE_ONE_SHOT = (0b000 << 4),
    LPS25H_DATARATE_1_HZ     = (0b001 << 4),
    LPS25H_DATARATE_7_HZ     = (0b010 << 4),
    LPS25H_DATARATE_12_5_HZ  = (0b011 << 4),
    LPS25H_DATARATE_25_HZ    = (0b100 << 4),
} LPS25HDataRate_t;

typedef enum
{
    LPS25H_BDU_DISABLE = (0b0 << 2),
    LPS25H_BDU_ENABLE  = (0b1 << 2),
} LPS25HDataUpdateMode_t;

typedef enum
{
    LPS25H_POWER_DOWN = (0b0 << 7),
    LPS25H_POWER_UP   = (0b1 << 7),
} LPS25HPowerMode_t;

#endif // #ifndef LPS25H_TYPES_H
