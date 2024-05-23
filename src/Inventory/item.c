/*
** EPITECH PROJECT, 2024
** inventory_sys
** File description:
** weapon
*/

#include <stdio.h>
#include <stdlib.h>
#include "inventory.h"
#include "item.h"

weapon_t *create_weapon(rpg_t *rpg, char *name)
{
    weapon_t *weapon = malloc(sizeof(weapon_t));
    item_t *item = get_item_from_name(rpg, name, WEAPON);

    weapon->damage = item->damage;
    weapon->is_equipped = 0;
    weapon->name = strdup(item->name);
    weapon->sprite = init_sprite_from_file
    (item->texture_path);
    sfSprite_setScale(weapon->sprite, (sfVector2f){1.5, 1.5});
    return (weapon);
}

armor_t *create_armor(rpg_t *rpg, char *name)
{
    armor_t *armor = malloc(sizeof(armor_t));
    item_t *item = get_item_from_name(rpg, name, ARMOR);

    armor->defense = item->defense;
    armor->speed = item->speed;
    armor->armor_type = item->armor_type;
    armor->is_equipped = 0;
    armor->name = item->name;
    armor->endurance = item->endurance;
    armor->sprite = init_sprite_from_file
    (item->texture_path);
    sfSprite_setScale(armor->sprite, (sfVector2f){1.5, 1.5});
    return (armor);
}

int add_item(void *item, int type, char *name)
{
    slot_t *tmp = (*inventory())->slot;
    int empty_id = -1;
    static int id = 1;

    for (; tmp; tmp = tmp->next) {
        if (tmp->is_empty == 1) {
            empty_id = tmp->id;
            break;
        }
    }
    if (empty_id == -1 && id > (*inventory())->size)
        return (0);
    if (empty_id == -1)
        if (manage_slot(tmp, item, type, &id) == 1)
            return (0);
    tmp->is_empty = 0;
    tmp->type = type;
    tmp->item = item;
    tmp->name = strdup(name);
    return (0);
}

int remove_item(int id, slot_t *tmp)
{
    while (tmp != NULL) {
        if (tmp->id == id) {
            tmp->is_empty = 1;
            tmp->item = NULL;
            tmp->type = OTHER;
            tmp->name = NULL;
            return (0);
        }
        tmp = tmp->next;
    }
    return (0);
}
