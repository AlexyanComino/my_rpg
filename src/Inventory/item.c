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

int add_gold(int gold)
{
    inventory_t *inv = *inventory();
    char *gold_str = malloc(sizeof(char) * 10);

    inv->gold += gold;
    sprintf(gold_str, "%d", inv->gold);
    sfText_setString(inv->player_status->t_gold, gold_str);
    return (0);
}

int remove_gold(int gold)
{
    inventory_t *inv = *inventory();
    char *gold_str = malloc(sizeof(char) * 10);

    inv->gold -= gold;
    sprintf(gold_str, "%d", inv->gold);
    sfText_setString(inv->player_status->t_gold, gold_str);
    return (0);
}

weapon_t *create_weapon(rpg_t *rpg, char *name)
{
    weapon_t *weapon = malloc(sizeof(weapon_t));
    item_t *item = get_item_from_name(rpg, name, WEAPON);

    weapon->damage = item->damage;
    weapon->is_equipped = 0;
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
    armor->endurance = item->endurance;
    armor->sprite = init_sprite_from_file
    (item->texture_path);
    sfSprite_setScale(armor->sprite, (sfVector2f){1.5, 1.5});
    return (armor);
}
