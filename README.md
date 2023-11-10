| Supported Targets | MagicCineTool |

# HiddenPeak_MagicCineTool SDK

## 必要组件：
- espressif/esp_lvgl_port
- eil/i2cdev
- espressif/button
- espressif/knob

```
idf.py add-dependency "espressif/button^3.1.2"
idf.py add-dependency "espressif/knob^0.1.3"
idf.py add-dependency "eil/i2cdev^1.5.1"
idf.py add-dependency "espressif/esp_lvgl_port^1.3.0"
```

## 板载硬件说明

- ESP32S3 内置PSRAM 8MB
- 外置Flash 16MB
- AXP173 电源管理芯片
- EC11 按钮编码器
- 电源按钮
- 自定义功能按钮
- 震动马达
- 18650电池座
- 扩展锂电池座
- 1.4英寸 LCD显示器