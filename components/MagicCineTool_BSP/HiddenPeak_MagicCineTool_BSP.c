#include "HiddenPeak_MagicCineTool_BSP.h"

static const char *TAG = "LVGL_PORT";
/* LVGL display and Encoder Buttons */
lv_disp_t *lvgl_disp = NULL;
lv_indev_t *encoder_handle = NULL;
lv_group_t *g = NULL;

void HiddenPeak_MagicCineTool_init(void)
{
    // 初始化I2C总线
    i2c_config_t i2c_config = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = HiddenPeak_MagicCineTool__I2C_MASTER_SDA,
        .scl_io_num = HiddenPeak_MagicCineTool__I2C_MASTER_SCL,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = HiddenPeak_MagicCineTool__I2C_CLOCK_HZ,
    };
    ESP_ERROR_CHECK(i2c_param_config(I2C_NUM_0, &i2c_config));
    ESP_LOGI("i2c", "i2c_param_config done");
    ESP_ERROR_CHECK(i2c_driver_install(I2C_NUM_0, i2c_config.mode, 0, 0, 0));
    ESP_LOGI("i2c", "i2c_driver_install done");

    // 初始化GPIO

    // 初始化SPI总线
    // 这里需要根据你的硬件配置来设置SPI的参数

    // 初始化UART
    // 这里需要根据你的硬件配置来设置UART的参数

    // 初始化按钮组件
    // 这里需要根据你的硬件配置来设置按钮的参数

    // 初始化旋钮组件
    // 这里需要根据你的硬件配置来设置旋钮的参数

    // 初始化LCD面板
    /* LCD HW initialization */
    ESP_ERROR_CHECK(app_lcd_init());

    /* LVGL initialization */
    ESP_ERROR_CHECK(app_lvgl_init());

    // 拉低GPIO 38，打开背光
    gpio_set_direction(38, GPIO_MODE_OUTPUT);
    gpio_set_level(38, 0);
}