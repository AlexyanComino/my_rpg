/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** destroy
*/

#include "my.h"

void destroy_rpg(rpg_t *rpg)
{
    sfRenderWindow_destroy(rpg->win->window);
    free(rpg->win);
    free(rpg);
}
