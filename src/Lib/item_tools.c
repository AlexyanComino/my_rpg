/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** item_tools
*/

#include "rpg.h"

item_t *get_item_from_name(rpg_t *rpg, char *name, enum item_type type)
{
    for (int i = 0; i < (int)rpg->items_size; i++) {
        if (rpg->items[i]->type == type && !strcmp(rpg->items[i]->name, name))
            return (rpg->items[i]);
    }
    fprintf(stderr, "Item %s not found\n", name);
    return (NULL);
}

void add_item_from_type(rpg_t *rpg, char *name, enum item_type type)
{
    if (type == WEAPON)
        add_item(create_weapon(rpg, name), WEAPON, name);
    if (type == ARMOR)
        add_item(create_armor(rpg, name), ARMOR, name);
}
