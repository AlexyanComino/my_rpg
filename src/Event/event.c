/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** event
*/

#include "rpg.h"

void event(rpg_t *rpg)
{
    while (sfRenderWindow_pollEvent(rpg->win->window, &rpg->event)) {
        if (rpg->event.type == sfEvtClosed ||
            rpg->event.key.code == sfKeyEscape)
            sfRenderWindow_close(rpg->win->window);
        if (rpg->gamestate == MAIN_MENU) {
            menu_button_event(rpg, rpg->main_menu->buttons);
            break;
        }
        if (rpg->gamestate == SETTINGS) {
            menu_button_event(rpg, rpg->settings->buttons);
            break;
        }
    }
}
