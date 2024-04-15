/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** displayAll
*/

#include "rpg.h"

void display_all(rpg_t *rpg)
{
    sfRenderWindow_clear(rpg->win->window, sfBlack);
    sfRenderWindow_display(rpg->win->window);
}
