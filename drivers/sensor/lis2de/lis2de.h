
#ifndef DRIVER_SENSOR_LIS2DE_H
#define DRIVER_SENSOR_LIS2DE_H

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/sys/util.h>
#include <stdint.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>
// TODO: Add spi if I'm bored
#include <zephyr/drivers/i2c.h>
#include <string.h>

// TODO: Start this as big endian for no

#define LIS2DE_ENABLE          0b1U
#define LIS2DE_DISABLE         0b0U

// I2C device addr for if the SA0=0 (Low) or SA0=1 (High)
#define LIS2DE_I2C_ADDR_L      0x31U
#define LIS2DE_I2C_ADDR_H      0x33U

// Status register aux
#define LIS2DE_STATUS_REG_AUX  0x07U
typedef struct {
    uint8_t not_used_3         :2;
    uint8_t tda                :1;
    uint8_t not_used_2         :3;
    uint8_t tor                :1;
    uint8_t not_used_1         :1;
} lis2de_status_reg_aux_t;


// Temp data, two-complement, left justified
#define LIS2DE12_OUT_TEMP_L    0x0CU
#define LIS2DE12_OUT_TEMP_H    0x0CU

// WHO_AM_I dev identification
#define LIS2DE12_CHIP_ID       0x33U
#define LIS2DE12_WHO_AM_I      0x0FU

// Control Reg 0
#define LIS2DE12_CTRL_REG_0    0x1EU
typedef struct {
    uint8_t sdo_pu_disc        :1;
    uint8_t not_used_1         :7;
} lis2de12_ctrl_reg_0_t;


// Temp Config Reg
#define LIS2DE12_TEMP_CFG_REG  0x1FU

typedef enum {
    LIS2DE12_TEMP_DIS          = 0x0U,
    LIS2DE12_TEMP_EN           = 0x3U,
} lis2de12_temp_en_t;

typedef struct {
    uint8_t temp_en            :2;
    uint8_t not_used_1         :6;
} lis2de12_temp_cfg_reg_t;

// Control Reg 1
#define LIS2DE12_CTRL_REG_1    0x20U

typedef enum {
    LIS2DE12_ODR_PWR_DWN       = 0x0U,
    LIS2DE12_ODR_1_HZ          = 0x1U,
    LIS2DE12_ODR_10_HZ         = 0x2U,
    LIS3DE12_ODR_25_HZ         = 0x3U,
    LIS3DE12_ODR_50_HZ         = 0x4U,
    LIS3DE12_ODR_100_HZ        = 0x5U,
    LIS3DE12_ODR_200_HZ        = 0x6U,
    LIS3DE12_ODR_400_HZ        = 0x7U,
    LIS3DE12_ODR_1_620_KHZ     = 0x8U,
    LIS3DE12_ODR_5_376_KHZ     = 0x9U,
} lis2de12_temp_en_t;

typedef struct {
    uint8_t odr                :4;
    uint8_t lp_en              :1;
    uint8_t z_en               :1;
    uint8_t y_en               :1;
    uint8_t x_en               :1;
} lis2de12_ctrl_reg_1_t;

// Control Reg 2
#define LIS2DE12_CTRL_REG_2    0x21U

typedef enum {
    LIS2DE12_HPCF_HIGH         = 0x0U,
    LIS3DE12_HPCF_MED_HIGH     = 0x1U,
    LIS4DE12_HPCF_MED_LOW      = 0x2U,
    LIS4DE12_HPCF_LOW          = 0x3U,
} lis2de12_hpcf_t;

typedef enum {
    LIS2DE12_HP_NORMAL         = 0x0U,
    LIS3DE12_HP_REF_SIG        = 0x1U,
    LIS4DE12_HP_NORMAL         = 0x2U,
    LIS4DE12_HP_AUTORESET      = 0x3U,
} lis2de12_hp_mode_t;

typedef struct {
    uint8_t hpm                :2;
    uint8_t hpcf               :2;
    uint8_t fds                :1;
    uint8_t cp_click           :1;
    uint8_t hp_ia2             :1;
    uint8_t hp_ia1             :1;
} lis2de12_ctrl_reg_2_t;

// Control Reg 3
#define LIS2DE12_CTRL_REG_3    0x22U
typedef struct {
    uint8_t i1_click           :1;
    uint8_t i1_ia1             :1;
    uint8_t i1_ia2             :1;
    uint8_t i1_zyxda           :1;
    uint8_t not_used_1         :1;
    uint8_t i1_wtm             :1;
    uint8_t i1_or              :1;
} lis2de12_ctrl_reg_3_t;

// Control Reg 4
#define LIS2DE12_CTRL_REG_4    0x23U

typedef enum {
    LIS2DE12_SCALE_2G          = 0x0U,
    LIS3DE12_SCALE_4G          = 0x1U,
    LIS4DE12_SCALE_8G          = 0x2U,
    LIS4DE12_SCALE_16G         = 0x3U,
} lis2de12_scale_t;

typedef enum {
    LIS2DE12_ST_DIABLED        = 0x0U,
    LIS3DE12_ST_0              = 0x1U,
    LIS3DE12_ST_1              = 0x2U,
} lis2de12_self_test_t;

typedef struct {
    uint8_t bdu                :1;
    uint8_t not_used_1         :1;
    uint8_t fs                 :2;
    uint8_t not_used_1         :1;
    uint8_t st                 :2;
    uint8_t sim                :1;
} lis2de12_ctrl_reg_4_t;

// Control Reg 5
#define LIS2DE12_CTRL_REG_5    0x24U
typedef struct {
    uint8_t boot               :1;
    uint8_t fifo_en            :1;
    uint8_t not_used_1         :2;
    uint8_t lir_int_1          :1;
    uint8_t d4d_int_1          :1;
    uint8_t lir_int_2          :1;
    uint8_t d4d_int_2          :1;
} lis2de12_ctrl_reg_5_t;

// Control Reg 6
#define LIS2DE12_CTRL_REG_6    0x25U
typedef struct {
    uint8_t i2_click           :1;
    uint8_t i2_ia1             :1;
    uint8_t i2_ia2             :1;
    uint8_t i2_boot            :1;
    uint8_t i2_act             :1;
    uint8_t not_used_1         :1;
    uint8_t int_polarity       :1;
} lis2de12_ctrl_reg_6_t;

// Reference
#define LIS2DE12_REFERENCE    0x26U
typedef struct {
    uint8_t reference,
} lis2de12_reference_t;

// Fifo read start reg
#define LIS2DE12_FIFO_RD_START 0x27U

// XYZ Acceleration Data, two's complement left-justified
#define LIS2DE12_OUT_X_H       0x29U
#define LIS2DE12_OUT_Y_H       0x2BU
#define LIS2DE12_OUT_Z_H       0x2DU

#define LIS2DE12_DATA_SZ       0x6U

typedef union {
    uint8_t raw[LIS2DE12_DATA_SZ];

    struct {
        int16_t x;
        int16_t y;
        int16_t z;
    } __packed;
} lis2de12_data_t;


// Fifo Control Reg
#define LIS2DE12_FIFO_CTRL_REG 0x2EU

typedef enum {
    LIS2DE12_FM_BYPASS         = 0x0U,
    LIS3DE12_FM_FIFO           = 0x1U,
    LIS4DE12_FM_STREAM         = 0x2U,
    LIS4DE12_FM_STREAM_FIFO    = 0x3U,
} lis2de12_fifo_mode_t;

typedef struct {
    uint8_t fm                 :2;
    uint8_t th                 :1;
    uint8_t fth                :5;
} lis2de12_reference_t;

// TODO: Add the rest as needed cause I'm bored

// Zephyr sensor configurations
union lis2de_bus_cfg {
#if DT_ANY_INST_ON_BUS_STATUS_OKAY(i2c)
	struct i2c_dt_spec i2c;
#endif

#if DT_ANY_INST_ON_BUS_STATUS_OKAY(spi)
	struct spi_dt_spec spi;
#endif /* DT_ANY_INST_ON_BUS_STATUS_OKAY(spi) */
};

struct lis2de_config {
    int (*bus_init)(const struct device *dev);
    const union lis2de_bus_cfg;
    // TODO: Surround with trigger config
    const struct gpio_dt_spec gpio_drdy;
    const struct gpio_dt_spec gpio_int;
    /*
        TODO: Add hw configurations
        struct{latch, etc}
    */
};

struct lis2de_transfer_function {
    int (*read_data)(const struct device *dev, uint8_t reg_addr, uint8_t *val, uint8_t len);
    int (*write_data)(const struct device *dev, uint8_t reg_addr, uint8_t *val, uint8_t len);
    int (*read_reg)(const struct device *dev, uint8_t reg_addr, uint8_t *val);
    int (*write_reg)(const struct device *dev, uint8_t reg_addr, uint8_t val);
};

struct lis2de_data {
    const struct device *bus;
    const struct lis2de_transfer_function *hw_tf;

    union lis2de_data sample;
    lis2de12_scale_t scale;

    // TODO: Config something with the trigger?
    const struct device *dev;
    struct gpio_callback gpio_int1_cb;
    struct gpio_callback gpio_int2_cb;

    // TODO: update this to be handler function
    sensor_trigger_handler_t click;
    enum sensor_channel channel;
    // TODO: Add info for the thread for the handler here
};


// TODO: Add other interrupt configs
int lis2de_trigger_set(
    const struct device *dev,
    const struct sensor_trigger *trig,
    sensor_trigger_handler_t handler
);

int lis2de_interrupt_init(const struct device *dev);

// TODO: Add spi
int lis2de_i2c_init(const struct device *dev);

#endif // DRIVER_SENSOR_LIS2DE_H
