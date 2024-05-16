/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_interface
*/

#include "rpg.h"

static restricted_t *init_restricted(void)
{
    restricted_t *restricted = malloc(sizeof(restricted_t));
    sfFloatRect rect;

    restricted->texture = sfTexture_createFromFile(
        "assets/interface/danger.png", NULL);
    restricted->sprite = sfSprite_create();
    sfSprite_setTexture(restricted->sprite, restricted->texture, sfTrue);
    rect = sfSprite_getGlobalBounds(restricted->sprite);
    sfSprite_setOrigin(restricted->sprite,
        (sfVector2f){rect.width / 2, rect.height / 2});
    sfSprite_setColor(restricted->sprite, (sfColor){255, 255, 255, 0});
    sfSprite_setScale(restricted->sprite, (sfVector2f){1.1, 1.1});
    restricted->in_base = false;
    restricted->animation = false;
    return restricted;
}

static health_bar_t *init_health_bar_interface(void)
{
    health_bar_t *health_bar = malloc(sizeof(health_bar_t));
    sfVector2f back_size = {WIDTH / 3, HEIGHT / 30};
    sfVector2f front_size = {WIDTH / 3 - 10, HEIGHT / 30 - 10};

    health_bar->back = init_round_rectangle((sfVector2f){0, 0}, 15,
        back_size, sfBlack);
    health_bar->front = init_round_rectangle((sfVector2f){0, 0}, 10,
        front_size, sfGreen);
    return health_bar;
}

interface_t *init_interface(void)
{
    interface_t *interface = malloc(sizeof(interface_t));

    interface->restricted = init_restricted();
    interface->health_bar = init_health_bar_interface();
    return interface;
}
