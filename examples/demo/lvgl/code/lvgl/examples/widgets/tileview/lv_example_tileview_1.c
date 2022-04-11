#include "../../lv_examples.h"
#if LV_USE_TILEVIEW && LV_BUILD_EXAMPLES

/**
 * Create a 2x2 tile view and allow scrolling only in an "L" shape.
 * Demonstrate scroll chaining with a long list that
 * scrolls the tile view when it cant't be scrolled further.
 */
void lv_example_tileview_1(void)
{
    lv_obj_t *tv = lv_tileview_create(lv_scr_act());

    /*Tile1: just a label*/
    lv_obj_t * tile1 = lv_tileview_add_tile(tv, 0, 0, LV_DIR_BOTTOM);
    lv_obj_t * label = lv_label_create(tile1);
    lv_label_set_text(label, "Scroll down");
    lv_obj_center(label);


    /*Tile2: a button*/
    lv_obj_t * tile2 = lv_tileview_add_tile(tv, 0, 1, LV_DIR_TOP | LV_DIR_RIGHT);

    lv_obj_t * btn = lv_btn_create(tile2);

    label = lv_label_create(btn);
    lv_label_set_text(label, "Scroll up or right");

    lv_obj_set_size(btn, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_center(btn);

    /*Tile3: a list*/
    lv_obj_t * tile3 =  lv_tileview_add_tile(tv, 1, 1, LV_DIR_LEFT);
    lv_obj_t * list = lv_list_create(tile3);
    lv_obj_set_size(list, LV_SIZE_PCT(100), LV_SIZE_PCT(100));

    lv_list_add_btn(list, NULL, "One", NULL);
    lv_list_add_btn(list, NULL, "Two", NULL);
    lv_list_add_btn(list, NULL, "Three", NULL);
    lv_list_add_btn(list, NULL, "Four", NULL);
    lv_list_add_btn(list, NULL, "Five", NULL);
    lv_list_add_btn(list, NULL, "Six", NULL);
    lv_list_add_btn(list, NULL, "Seven", NULL);
    lv_list_add_btn(list, NULL, "Eight", NULL);
    lv_list_add_btn(list, NULL, "Nine", NULL);
    lv_list_add_btn(list, NULL, "Ten", NULL);

}

#endif
