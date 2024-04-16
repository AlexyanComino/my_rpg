/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_rpg
*/

#include "rpg.h"

static win_t *init_win(unsigned int width, unsigned int height)
{
    win_t *win = malloc(sizeof(win_t));
    sfVideoMode mode = {width, height, 32};

    win->window = sfRenderWindow_create(mode, "My_RPG", sfClose, NULL);
    win->view = sfView_createFromRect((sfFloatRect){0, 0, width, height});
    sfRenderWindow_setView(win->window, win->view);
    sfView_setViewport(win->view, (sfFloatRect){0, 0, 1, 1});
    win->width = width;
    win->height = height;
    win->framerate = 60;
    win->clock = sfClock_create();
    sfRenderWindow_setFramerateLimit(win->window, win->framerate);
    return win;
}

rpg_t *init_rpg(void)
{
    rpg_t *rpg = malloc(sizeof(rpg_t));

    rpg->win = init_win(WIDTH, HEIGHT);
    rpg->lwarrior = init_lwarrior();
    rpg->event = (sfEvent){0};
    rpg->debug = true;
    return rpg;
}
