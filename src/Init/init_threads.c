/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_map
*/

#include "rpg.h"

static map_t *init_map(void)
{
    map_t *map = malloc(sizeof(map_t));

    map->ground_texture = sfTexture_createFromFile("assets/bas.png", NULL);
    map->ground_sprite = sfSprite_create();
    sfSprite_setTexture(map->ground_sprite, map->ground_texture, sfTrue);
    sfSprite_setScale(map->ground_sprite,
        (sfVector2f){TILE_SCALE, TILE_SCALE});
    map->high_texture = sfTexture_createFromFile("assets/haut.png", NULL);
    map->high_sprite = sfSprite_create();
    sfSprite_setTexture(map->high_sprite, map->high_texture, sfTrue);
    sfSprite_setScale(map->high_sprite, (sfVector2f){TILE_SCALE, TILE_SCALE});
    return map;
}

void *load_data(void *arg)
{
    shared_data_t *shared_data = (shared_data_t *)arg;

    shared_data->map = init_map();
    shared_data->loaded = 1;
    printf("\033[0;32mMap loaded\033[0m\n");
    pthread_exit(NULL);
}

void *load_entities(void *arg)
{
    shared_data2_t *shared_data = (shared_data2_t *)arg;

    shared_data->nb_entities = 0;
    shared_data->entities = init_ent(&shared_data->nb_entities);
    shared_data->loaded = 1;
    printf("\033[0;31mEntities loaded\033[0m\n");
    pthread_exit(NULL);
}
