#include "HiddenPeak_MagicCineTool_LVGL_port.h"

static const char *TAG = "LVGL_PORT";

/* LCD IO and panel */
static esp_lcd_panel_io_handle_t lcd_io = NULL;
static esp_lcd_panel_handle_t lcd_panel = NULL;

// /* LVGL display and Encoder Buttons */
// static lv_disp_t *lvgl_disp = NULL;
// static lv_indev_t *encoder_handle = NULL;
// static lv_indev_t *buttons_handle = NULL;

// static lv_group_t * g;

esp_err_t app_lcd_init(void)
{
    esp_err_t ret = ESP_OK;

    /* LCD initialization */
    ESP_LOGD(TAG, "Initialize SPI bus");
    const spi_bus_config_t buscfg = {
        .sclk_io_num = HiddenPeak_MagicCineTool_LCD_GPIO_SCLK,
        .mosi_io_num = HiddenPeak_MagicCineTool_LCD_GPIO_MOSI,
        .miso_io_num = GPIO_NUM_NC,
        .quadwp_io_num = GPIO_NUM_NC,
        .quadhd_io_num = GPIO_NUM_NC,
        .max_transfer_sz = HiddenPeak_MagicCineTool_LCD_H_RES * HiddenPeak_MagicCineTool_LCD_DRAW_BUFF_HEIGHT * sizeof(uint16_t),
    };
    ESP_RETURN_ON_ERROR(spi_bus_initialize(HiddenPeak_MagicCineTool_LCD_SPI_NUM, &buscfg, SPI_DMA_CH_AUTO), TAG, "SPI init failed");

    ESP_LOGD(TAG, "Install panel IO");
    const esp_lcd_panel_io_spi_config_t io_config = {
        .dc_gpio_num = HiddenPeak_MagicCineTool_LCD_GPIO_DC,
        .cs_gpio_num = HiddenPeak_MagicCineTool_LCD_GPIO_CS,
        .pclk_hz = HiddenPeak_MagicCineTool_LCD_PIXEL_CLK_HZ,
        .lcd_cmd_bits = HiddenPeak_MagicCineTool_LCD_CMD_BITS,
        .lcd_param_bits = HiddenPeak_MagicCineTool_LCD_PARAM_BITS,
        .spi_mode = 0,
        .trans_queue_depth = 10,
    };
    ESP_GOTO_ON_ERROR(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)HiddenPeak_MagicCineTool_LCD_SPI_NUM, &io_config, &lcd_io), err, TAG, "New panel IO failed");

    ESP_LOGD(TAG, "Install LCD driver");
    const esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = HiddenPeak_MagicCineTool_LCD_GPIO_RST,
        .color_space = HiddenPeak_MagicCineTool_LCD_COLOR_SPACE,
        .bits_per_pixel = HiddenPeak_MagicCineTool_LCD_BITS_PER_PIXEL,
    };
    ESP_GOTO_ON_ERROR(esp_lcd_new_panel_st7789(lcd_io, &panel_config, &lcd_panel), err, TAG, "New panel failed");

    esp_lcd_panel_reset(lcd_panel);
    esp_lcd_panel_set_gap(lcd_panel, HiddenPeak_MagicCineTool_LCD_OFFSET_X, HiddenPeak_MagicCineTool_LCD_OFFSET_Y);
    esp_lcd_panel_init(lcd_panel);
    esp_lcd_panel_mirror(lcd_panel, true, true);
    esp_lcd_panel_disp_on_off(lcd_panel, true);

    return ret;

err:
    if (lcd_panel)
    {
        esp_lcd_panel_del(lcd_panel);
    }
    if (lcd_io)
    {
        esp_lcd_panel_io_del(lcd_io);
    }
    spi_bus_free(HiddenPeak_MagicCineTool_LCD_SPI_NUM);
    return ret;
}

esp_err_t app_lvgl_init(void)
{
    /* Initialize LVGL */
    const lvgl_port_cfg_t lvgl_cfg = {
        .task_priority = 4,       /* LVGL task priority */
        .task_stack = 4096,       /* LVGL task stack size */
        .task_affinity = -1,      /* LVGL task pinned to core (-1 is no affinity) */
        .task_max_sleep_ms = 500, /* Maximum sleep in LVGL task */
        .timer_period_ms = 5      /* LVGL timer tick period in ms */
    };
    ESP_RETURN_ON_ERROR(lvgl_port_init(&lvgl_cfg), TAG, "LVGL port initialization failed");

    /* Add LCD screen */
    ESP_LOGD(TAG, "Add LCD screen");
    const lvgl_port_display_cfg_t disp_cfg = {
        .io_handle = lcd_io,
        .panel_handle = lcd_panel,
        .buffer_size = HiddenPeak_MagicCineTool_LCD_H_RES * HiddenPeak_MagicCineTool_LCD_DRAW_BUFF_HEIGHT * sizeof(uint16_t),
        .double_buffer = HiddenPeak_MagicCineTool_LCD_DRAW_BUFF_DOUBLE,
        .hres = HiddenPeak_MagicCineTool_LCD_H_RES,
        .vres = HiddenPeak_MagicCineTool_LCD_V_RES,
        .monochrome = false,
        /* Rotation values must be same as used in esp_lcd for initial settings of the screen */
        .rotation = {
            .swap_xy = false,
            .mirror_x = true,
            .mirror_y = true,
        },
        .flags = {
            .buff_dma = true,
        }};
    lvgl_disp = lvgl_port_add_disp(&disp_cfg);
    lv_disp_set_rotation(lvgl_disp, LV_DISP_ROT_90);

    // /* Buttons configuration structure */
    // const button_config_t button_config[] = {{.type = BUTTON_TYPE_GPIO,
    //                                           .gpio_button_config.active_level = false,
    //                                           .gpio_button_config.gpio_num = GPIO_BUTTON_1_1},
    //                                          {.type = BUTTON_TYPE_GPIO,
    //                                           .gpio_button_config.active_level = false,
    //                                           .gpio_button_config.gpio_num = GPIO_BUTTON_1_2},
    //                                          {.type = BUTTON_TYPE_GPIO,
    //                                           .gpio_button_config.active_level = false,
    //                                           .gpio_button_config.gpio_num = GPIO_BUTTON_1_3},
    //                                          {.type = BUTTON_TYPE_GPIO,
    //                                           .gpio_button_config.active_level = false,
    //                                           .gpio_button_config.gpio_num = GPIO_BUTTON_2_1},
    //                                          {.type = BUTTON_TYPE_GPIO,
    //                                           .gpio_button_config.active_level = false,
    //                                           .gpio_button_config.gpio_num = GPIO_BUTTON_2_2},
    //                                          {.type = BUTTON_TYPE_GPIO,
    //                                           .gpio_button_config.active_level = false,
    //                                           .gpio_button_config.gpio_num = GPIO_BUTTON_2_3}};

    // const lvgl_port_nav_btns_cfg_t btns = {
    //     .disp = lvgl_disp,
    //     .button_prev = &button_config[3],
    //     .button_next = &button_config[4],
    //     .button_enter = &button_config[2]};
    // buttons_handle = lvgl_port_add_navigation_buttons(&btns);

    const button_config_t encoder_btn_config = {
        .type = BUTTON_TYPE_GPIO,
        .gpio_button_config.active_level = false,
        .gpio_button_config.gpio_num = GPIO_KNOB_BUTTON,
    };

    const knob_config_t encoder_a_b_config = {
        .default_direction = 0,
        .gpio_encoder_a = GPIO_KNOB_A,
        .gpio_encoder_b = GPIO_KNOB_B,
    };

    /* Encoder configuration structure */
    const lvgl_port_encoder_cfg_t encoder = {
        .disp = lvgl_disp,
        .encoder_a_b = &encoder_a_b_config,
        .encoder_enter = &encoder_btn_config};

    /* Add encoder input (for selected screen) */
    encoder_handle = lvgl_port_add_encoder(&encoder);

    return ESP_OK;
}