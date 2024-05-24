/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** menu
*/

#include "rpg.h"

void slct_button_event(rpg_t *rpg, select_button_t *buttons)
{
    select_button_t *tmp = buttons;

    while (tmp) {
        is_select_button_clicked(tmp, rpg);
        is_select_button_hovered(tmp, rpg);
        if (tmp->state == HOVERED)
            sfText_setColor(tmp->text, sfWhite);
        if (tmp->state == CLICKED) {
            sfText_setColor(tmp->text, sfRed);
        }
        if (tmp->state == NOTHING) {
            sfText_setColor(tmp->text, sfBlack);
        }
        is_select_button_released(tmp, rpg);
        if (tmp->state == RELEASED)
            tmp->action(rpg);
        tmp = tmp->next;
    }
}

void save_button_event(rpg_t *rpg, save_button_t *buttons)
{
    save_button_t *tmp = buttons;

    while (tmp) {
        is_s_button_clicked(tmp, rpg);
        is_s_button_hovered(tmp, rpg);
        if (tmp->state == HOVERED)
            sfText_setColor(tmp->text, sfYellow);
        if (tmp->state == CLICKED) {
            tmp->rect.left = BUTTON_WIDTH;
            sfText_setColor(tmp->text, sfRed);
        }
        if (tmp->state == NOTHING) {
            tmp->rect.left = 0;
            sfText_setColor(tmp->text, sfWhite);
        }
        is_s_button_released(tmp, rpg);
        if (tmp->state == RELEASED)
            tmp->action(rpg);
        tmp = tmp->next;
    }
}

void menu_button_event(rpg_t *rpg, button_t *buttons)
{
    button_t *tmp = buttons;

    while (tmp) {
        is_button_clicked(tmp, rpg);
        is_button_hovered(tmp, rpg);
        if (tmp->state == CLICKED)
            sfText_setColor(tmp->text, tmp->click_color);
        if (tmp->state == NOTHING)
            sfText_setColor(tmp->text, tmp->color);
        is_button_released(tmp, rpg);
        if (tmp->state == RELEASED)
            tmp->action(rpg);
        tmp = tmp->next;
    }
}
