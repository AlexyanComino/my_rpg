/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_all
*/

#include "rpg.h"

void update_all(rpg_t *rpg)
{
    if (rpg->gamestate == GAME) {
        sfView_setCenter(rpg->win->view, rpg->lwarrior->warrior->pos);
        sfRenderWindow_setView(rpg->win->window, rpg->win->view);
        update_warriors(rpg);
    }
}
