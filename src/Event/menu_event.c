/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** menu
*/

#include "rpg.h"

void menu_button_event(rpg_t *rpg, button_t *buttons)
{
    button_t *tmp = buttons;

    while (tmp) {
        is_button_clicked(tmp, &rpg->event.mouseButton);
        is_button_hovered(tmp, &rpg->event.mouseMove);
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
        is_button_released(tmp, &rpg->event.mouseButton);
        if (tmp->state == RELEASED)
            tmp->action(rpg);
        tmp = tmp->next;
    }
}
