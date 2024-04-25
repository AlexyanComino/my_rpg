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

    win->window = sfRenderWindow_create(mode, "My_RPG", sfFullscreen, NULL);
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
    sfSprite_setScale(map->ground_sprite,
        (sfVector2f){TILE_SCALE, TILE_SCALE});
    map->high_texture = sfTexture_createFromFile("assets/bat.png", NULL);
    map->high_sprite = sfSprite_create();
    sfSprite_setTexture(map->high_sprite, map->high_texture, sfTrue);
    sfSprite_setScale(map->high_sprite, (sfVector2f){TILE_SCALE, TILE_SCALE});
    return map;
}

static sfVector2f *get_collisions_pos(unsigned int *size)
{
    sfVector2f *pos = NULL;
    size_t len = 0;
    char *line = NULL;
    FILE *file = fopen("Collisions/res.coll", "r");

    while (getline(&line, &len, file) != -1) {
        pos = realloc(pos, sizeof(sfVector2f) * (*size + 1));
        pos[*size].x = atoi(strtok(line, " ")) * TILE_SCALE + TILE_SIZE * 12 -
            TILE_SIZE / 2;
        pos[*size].y = atoi(strtok(NULL, " ")) * TILE_SCALE;
        (*size)++;
    }
    free(line);
    fclose(file);
    return pos;
}

static collision_t *init_collision(void)
{
    collision_t *collision = malloc(sizeof(collision_t));

    collision->rect = (sfIntRect){0, 0, TILE_SIZE, TILE_SIZE};
    collision->size = 0;
    collision->pos = get_collisions_pos(&collision->size);
    collision->shape = sfRectangleShape_create();
    sfRectangleShape_setFillColor(collision->shape, sfTransparent);
    sfRectangleShape_setOutlineColor(collision->shape, sfBlack);
    sfRectangleShape_setOutlineThickness(collision->shape, 2);
    sfRectangleShape_setSize(collision->shape, (sfVector2f){TILE_SIZE,
        TILE_SIZE});
    return collision;
}

rpg_t *init_rpg(void)
{
    rpg_t *rpg = malloc(sizeof(rpg_t));

    srand(time(NULL));
    rpg->gamestate = GAME;
    rpg->win = init_win(WIDTH, HEIGHT);
    rpg->lwarrior = init_lwarrior();
    rpg->event = (sfEvent){0};
    rpg->debug = true;
    rpg->main_menu = init_menu();
    rpg->save_menu = init_save_menu();
    rpg->settings = init_settings();
    init_all_quests(rpg);
    rpg->interface = init_interface();
    rpg->collision = init_collision();
    rpg->map = init_map();
    return rpg;
}
