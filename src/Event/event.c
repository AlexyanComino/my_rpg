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
        if (rpg->event.type == sfEvtClosed)
            sfRenderWindow_close(rpg->win->window);
    }
}
