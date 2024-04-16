/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** event
*/

#include "rpg.h"


void event(rpg_t *rpg)
{
    button_t *tmp = rpg->main_menu->buttons;

    while (sfRenderWindow_pollEvent(rpg->win->window, &rpg->event)) {
        if (rpg->event.type == sfEvtClosed || rpg->event.key.code == sfKeyEscape)
            sfRenderWindow_close(rpg->win->window);
        while (tmp) {
            is_button_clicked(tmp, &rpg->event.mouseButton);
            is_button_hovered(tmp, &rpg->event.mouseMove);
            if (tmp->state == HOVERED) {
                tmp->rect.left = 96;
            } else if (tmp->state == CLICKED) {
                tmp->rect.left = 48;
            } else
                tmp->rect.left = 0;
            is_button_released(tmp, &rpg->event.mouseButton);
            if (tmp->state == RELEASED)
                tmp->action(rpg);
            tmp = tmp->next;
        }
    }
}
