/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_rpg
*/

#include "my.h"

win_t *create_window(unsigned int width, unsigned int height)
{
    win_t *win = malloc(sizeof(win_t));
    sfVideoMode mode = {width, height, 32};

    win->window = sfRenderWindow_create(mode, "My_RPG", sfClose, NULL);
    win->width = width;
    win->height = height;
    return win;
}

rpg_t *init_rpg(void)
{
    rpg_t *rpg = malloc(sizeof(rpg_t));

    rpg->win = create_window(WIDTH, HEIGHT);
    rpg->event = (sfEvent){0};
    return rpg;
}
