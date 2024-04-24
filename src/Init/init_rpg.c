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

    win->window = sfRenderWindow_create(mode, "My_RPG", sfDefaultStyle, NULL);
    win->view = sfView_createFromRect((sfFloatRect){0, 0, width, height});
    sfView_setViewport(win->view, (sfFloatRect){0, 0, 1, 1});
    sfRenderWindow_setView(win->window, win->view);
    win->width = width;
    win->height = height;
    win->framerate = 60;
    win->clock = sfClock_create();
    sfRenderWindow_setFramerateLimit(win->window, win->framerate);
    return win;
}

static map_t *init_map(void)
{
    map_t *map = malloc(sizeof(map_t));

    map->ground_texture = sfTexture_createFromFile("assets/ground.png", NULL);
    map->ground_sprite = sfSprite_create();
    sfSprite_setTexture(map->ground_sprite, map->ground_texture, sfTrue);
    map->high_texture = sfTexture_createFromFile("assets/bat.png", NULL);
    map->high_sprite = sfSprite_create();
    sfSprite_setTexture(map->high_sprite, map->high_texture, sfTrue);
    return map;
}

rpg_t *init_rpg(void)
{
    rpg_t *rpg = malloc(sizeof(rpg_t));

    srand(time(NULL));
    rpg->gamestate = MAIN_MENU;
    rpg->win = init_win(WIDTH, HEIGHT);
    rpg->map = init_map();
    rpg->lwarrior = init_lwarrior();
    rpg->event = (sfEvent){0};
    rpg->debug = true;
    update_all(rpg);
    rpg->main_menu = init_menu();
    rpg->settings = init_settings();
    return rpg;
}
