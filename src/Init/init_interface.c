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

interface_t *init_interface(void)
{
    interface_t *interface = malloc(sizeof(interface_t));

    interface->restricted = init_restricted();
    return interface;
}
