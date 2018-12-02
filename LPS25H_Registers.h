#ifndef LPS25H_REGISTERS_H
#define LPS25H_REGISTERS_H

static constexpr auto LPS25H_REGISTER_REF_P_XL      = 0x08;
static constexpr auto LPS25H_REGISTER_REF_P_L       = 0x09;
static constexpr auto LPS25H_REGISTER_REF_P_H       = 0x0A;
static constexpr auto LPS25H_REGISTER_WHO_AM_I      = 0x0F;
static constexpr auto LPS25H_REGISTER_RES_CONF      = 0x10;
static constexpr auto LPS25H_REGISTER_CTRL_REG1     = 0x20;
static constexpr auto LPS25H_REGISTER_CTRL_REG2     = 0x21;
static constexpr auto LPS25H_REGISTER_CTRL_REG3     = 0x22;
static constexpr auto LPS25H_REGISTER_CTRL_REG4     = 0x23;
static constexpr auto LPS25H_REGISTER_INTERRUPT_CFG = 0x24;
static constexpr auto LPS25H_REGISTER_INT_SOURCE    = 0x25;
static constexpr auto LPS25H_REGISTER_STATUS_REG    = 0x27;
static constexpr auto LPS25H_REGISTER_PRESS_OUT_XL  = 0x28;
static constexpr auto LPS25H_REGISTER_PRESS_OUT_L   = 0x29;
static constexpr auto LPS25H_REGISTER_PRESS_OUT_H   = 0x2A;
static constexpr auto LPS25H_REGISTER_TEMP_OUT_L    = 0x2B;
static constexpr auto LPS25H_REGISTER_TEMP_OUT_H    = 0x2C;
static constexpr auto LPS25H_REGISTER_FIFO_CTRL     = 0x2E;
static constexpr auto LPS25H_REGISTER_FIFO_STATUS   = 0x2F;
static constexpr auto LPS25H_REGISTER_THS_P_L       = 0x30;
static constexpr auto LPS25H_REGISTER_THS_P_H       = 0x31;
static constexpr auto LPS25H_REGISTER_RPDS_L        = 0x39;
static constexpr auto LPS25H_REGISTER_RPDS_H        = 0x3A;

#endif // #ifndef LPS25H_REGISTERS_H
