/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** singleton
*/

#include "inventory.h"

inventory_t **inventory(void)
{
    static inventory_t *inventory = NULL;

    if (inventory == NULL)
        inventory = malloc(sizeof(inventory_t));
    return (&inventory);
}

sfVector2f *view_pos(void)
{
    static sfVector2f view_pos = {0, 0};

    return (&view_pos);
}
