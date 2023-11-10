#include "HiddenPeak_MagicCineTool_BSP.h"
#include "lvgl_app.h"

static void _app_button_cb(lv_event_t *e)
{
    lv_disp_rot_t rotation = lv_disp_get_rotation(lvgl_disp);
    rotation += 2;
    if (rotation > LV_DISP_ROT_270)
    {
        rotation = LV_DISP_ROT_90;
    }

    /* LCD HW rotation */
    lv_disp_set_rotation(lvgl_disp, rotation);

    lv_obj_invalidate(lv_scr_act());
    lv_refr_now(NULL);
}

void app_main_display(void)
{
    g = lv_group_get_default();
    if (g == NULL)
    {
        g = lv_group_create();
        lv_group_set_default(g);
    }

    lv_indev_t *cur_drv = NULL;
    for (;;)
    {
        cur_drv = lv_indev_get_next(cur_drv);
        if (!cur_drv)
        {
            break;
        }

        if (cur_drv->driver->type == LV_INDEV_TYPE_KEYPAD)
        {
            lv_indev_set_group(cur_drv, g);
        }

        if (cur_drv->driver->type == LV_INDEV_TYPE_ENCODER)
        {
            lv_indev_set_group(cur_drv, g);
        }
    }

    lv_obj_t *scr = lv_scr_act();
    lv_obj_clean(scr);
    /* Task lock */
    lvgl_port_lock(0);

    /* Your LVGL objects code here .... */

    /* Label */
    lv_obj_t *label = lv_label_create(scr);
    lv_label_set_recolor(label, true);
    lv_obj_set_width(label, HiddenPeak_MagicCineTool_LCD_H_RES);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_text(label, "Hello world, use HiddenPeak MagicCineTool");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, -20);

    /* Button */
    lv_obj_t *btn = lv_btn_create(scr);
    label = lv_label_create(btn);
    lv_label_set_text_static(label, "Rotate screen");
    lv_obj_align(btn, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_obj_add_event_cb(btn, _app_button_cb, LV_EVENT_CLICKED, NULL);

    /* Task unlock */
    lvgl_port_unlock();
}
