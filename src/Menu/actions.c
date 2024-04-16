/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** actions
*/

#include "rpg.h"

void quit(rpg_t *rpg)
{
    sfRenderWindow_close(rpg->win->window);
}
