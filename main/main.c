/* MagicCineTool BSP  */
#include "HiddenPeak_MagicCineTool_BSP.h"
#include "../managed_components/lvgl__lvgl/demos/widgets/lv_demo_widgets.h"
#include "lvgl_app.h"

void app_main()
{
    ESP_LOGI("main", "Hello world!");
    HiddenPeak_MagicCineTool_init();
    app_main_display();
        // lv_demo_benchmark();
        // lv_demo_music();
        // lv_demo_keypad_encoder();
        // lv_demo_stress();
        // lv_demo_widgets();
}