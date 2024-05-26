/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_menus
*/

#include "rpg.h"

static void update_menu_selector(rpg_t *rpg)
{
    select_button_t *tmp = rpg->selector->buttons;

    while (tmp != NULL) {
        if (tmp->entity != NULL)
            tmp->entity->anim(rpg, tmp->entity);
        tmp = tmp->next;
    }
}

static void set_color_alpha(sfColor *color, int diff)
{
    if (diff > 0) {
        if (color->a + diff > 255)
            color->a = 255;
        else
            color->a += diff;
    } else {
        if (color->a + diff < 0)
            color->a = 0;
        else
            color->a += diff;
    }
}

void update_shadow_buttons(button_t *buttons)
{
    button_t *tmp = buttons;
    sfColor color = {0, 0, 0, 0};

    while (tmp != NULL) {
        color = sfText_getColor(tmp->shadow);
        if ((tmp->state == HOVERED || tmp->state == CLICKED) &&
            color.a < 255) {
            set_color_alpha(&color, 9);
            sfText_setColor(tmp->shadow, color);
            sfText_setOutlineColor(tmp->shadow, color);
            tmp = tmp->next;
            continue;
        }
        if (tmp->state == NOTHING && color.a > 0) {
            set_color_alpha(&color, -5);
            sfText_setColor(tmp->shadow, color);
            sfText_setOutlineColor(tmp->shadow, color);
        }
        tmp = tmp->next;
    }
}

static void update_main_menu(rpg_t *rpg)
{
    anim_text_anim(rpg->main_menu->title1);
    anim_text_anim(rpg->main_menu->title2);
    update_shadow_buttons(rpg->main_menu->buttons);
}

void update_end_menu(rpg_t *rpg)
{
    anim_text_anim(rpg->end_menu->title1);
    anim_text_anim(rpg->end_menu->title2);
    update_shadow_buttons(rpg->end_menu->buttons);
}

void update_menus(rpg_t *rpg)
{
    move_view_menu(rpg);
    if (rpg->gamestate == SELECTOR)
        update_menu_selector(rpg);
    if (rpg->gamestate == MAIN_MENU)
        update_main_menu(rpg);
    if (rpg->gamestate == SETTINGS)
        update_shadow_buttons(rpg->settings->buttons);
    update_decors_anim(rpg, intrect_is_in_view_menu);
}
