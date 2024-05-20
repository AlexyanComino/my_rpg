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

weapon_t *create_weapon(int damage, char *name)
{
    weapon_t *weapon = malloc(sizeof(weapon_t));

    weapon->damage = damage;
    weapon->name = name;
    weapon->is_equipped = 0;
    weapon->sprite = init_sprite_from_file
    ("assets/item/Weapon & Tool/Iron Sword.png");
    sfSprite_setScale(weapon->sprite, (sfVector2f){1.5, 1.5});
    return (weapon);
}

armor_t *create_armor(int defense, int speed, int armor_type, char *name)
{
    armor_t *armor = malloc(sizeof(armor_t));

    armor->defense = defense;
    armor->speed = speed;
    armor->armor_type = armor_type;
    armor->is_equipped = 0;
    armor->name = name;
    armor->sprite = init_sprite_from_file
    ("assets/item/Equipment/Iron Armor.png");
    sfSprite_setScale(armor->sprite, (sfVector2f){1.5, 1.5});
    return (armor);
}
