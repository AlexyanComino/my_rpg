/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** draw
*/

#include "my.h"

void draw(rpg_t *rpg)
{
    sfRenderWindow_clear(rpg->win->window, sfBlack);
    sfRenderWindow_display(rpg->win->window);
}
