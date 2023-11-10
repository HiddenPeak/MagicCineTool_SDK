#ifndef MAGICCINETOOL_BSP_H
#define MAGICCINETOOL_BSP_H
/* 标准C库头文件  */
#include <stdio.h>   // 标准输入/输出库
#include <unistd.h>  // 标准符号常量和类型
#include <string.h>  // 字符串处理函数
#include <stdarg.h>  // 可变参数处理函数
#include <pthread.h> // POSIX线程库

#include "sys/time.h" // 时间函数

/* FreeRTOS头文件 */
#include "freertos/FreeRTOS.h"     // FreeRTOS实时操作系统
#include "freertos/task.h"         // FreeRTOS任务相关函数
#include "freertos/queue.h"        // FreeRTOS队列相关函数
#include "freertos/event_groups.h" // FreeRTOS事件组相关函数

/* ESP32头文件 */
#include "esp_system.h"   // ESP32系统头文件
#include "esp_wifi.h"     // ESP32 Wi-Fi相关函数
#include "esp_event.h"    // ESP32事件处理函数
#include "esp_err.h"      // ESP32错误处理函数
#include "esp_log.h"      // ESP32日志处理函数
#include "esp_check.h"    // ESP32检查函数
#include "esp_task_wdt.h" // ESP32任务看门狗定时器函数
#include "esp_vfs_dev.h"  // ESP32虚拟文件系统设备相关函数
#include "esp_netif.h"
#include "esp_netif_ppp.h"
#include "esp_sntp.h"
#include "esp_heap_caps.h"

/* NVS头文件 */
#include "nvs_flash.h" // NVS闪存库

/* LwIP头文件 */
#include "lwip/ip.h"
#include "lwip/err.h" // LwIP错误处理函数
#include "lwip/sys.h" // LwIP系统函数

/* 驱动程序头文件 */
#include "driver/i2c.h"        // I2C总线驱动程序
#include "driver/gpio.h"       // GPIO驱动程序
#include "driver/spi_master.h" // SPI总线驱动程序
#include "driver/uart.h"       // UART驱动程序

/* I2C DEV头文件 */
#include "i2cdev.h" // I2C设备驱动程序

/* ESP_IoT组件头文件（来自ESP托管组件） */
#include "iot_button.h"        // 按钮组件
#include "iot_knob.h"          // 旋钮组件

/* LCD 头文件（来自ESP托管组件） */
#include "esp_lcd_panel_io.h"   // LCD面板IO接口
#include "esp_lcd_panel_vendor.h"  // LCD面板供应商
#include "esp_lcd_panel_ops.h"  // LCD面板操作函数
#include "esp_lvgl_port.h"      // LVGL图形库移植

#include "HiddenPeak_MagicCineTool_LVGL_port.h"


/* Knob GPIO */

#define GPIO_KNOB_BUTTON (46)
#define GPIO_KNOB_A (45)
#define GPIO_KNOB_B (42)

/* LCD size */
#define HiddenPeak_MagicCineTool_LCD_H_RES (172)
#define HiddenPeak_MagicCineTool_LCD_V_RES (320)
#define HiddenPeak_MagicCineTool_LCD_OFFSET_X (0)
#define HiddenPeak_MagicCineTool_LCD_OFFSET_Y (34)

/* LCD settings */
#define HiddenPeak_MagicCineTool_LCD_SPI_NUM (SPI3_HOST)
#define HiddenPeak_MagicCineTool_LCD_PIXEL_CLK_HZ (40 * 1000 * 1000)
#define HiddenPeak_MagicCineTool_LCD_CMD_BITS (8)
#define HiddenPeak_MagicCineTool_LCD_PARAM_BITS (8)
#define HiddenPeak_MagicCineTool_LCD_COLOR_SPACE (ESP_LCD_COLOR_SPACE_BGR)
#define HiddenPeak_MagicCineTool_LCD_BITS_PER_PIXEL (16)
#define HiddenPeak_MagicCineTool_LCD_DRAW_BUFF_DOUBLE (1)
#define HiddenPeak_MagicCineTool_LCD_DRAW_BUFF_HEIGHT (50)
#define HiddenPeak_MagicCineTool_LCD_BL_ON_LEVEL (1)

/* LCD pins */
#define HiddenPeak_MagicCineTool_LCD_GPIO_SCLK (GPIO_NUM_15)
#define HiddenPeak_MagicCineTool_LCD_GPIO_MOSI (GPIO_NUM_13)
#define HiddenPeak_MagicCineTool_LCD_GPIO_RST (GPIO_NUM_17)
#define HiddenPeak_MagicCineTool_LCD_GPIO_DC (GPIO_NUM_14)
#define HiddenPeak_MagicCineTool_LCD_GPIO_CS (GPIO_NUM_16)

#define HiddenPeak_MagicCineTool__I2C_MASTER_SDA (GPIO_NUM_21) // GPIO assignment for I2C master data
#define HiddenPeak_MagicCineTool__I2C_MASTER_SCL (GPIO_NUM_18) // GPIO assignment for I2C master clock
#define HiddenPeak_MagicCineTool__I2C_CLOCK_HZ (100000)        // I2C master clock frequency

extern lv_disp_t *lvgl_disp;
extern lv_indev_t *encoder_handle;
extern lv_group_t * g;

void HiddenPeak_MagicCineTool_init(void);


#endif // MAGICCINETOOL_BSP_H