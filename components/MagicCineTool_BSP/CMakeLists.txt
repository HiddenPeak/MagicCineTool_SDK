
idf_component_register(SRCS "HiddenPeak_MagicCineTool_BSP.c" "HiddenPeak_MagicCineTool_LVGL_port.c" "drivers/i2c_bus/i2c_drv.c" "drivers/i2c_bus/i2cdev_esp32.c"
                    INCLUDE_DIRS "include" "drivers/i2c_bus/include"
                    REQUIRES freertos esp_system esp_wifi esp_event vfs 
                    nvs_flash lwip driver espressif__button espressif__knob espressif__esp_lvgl_port)
