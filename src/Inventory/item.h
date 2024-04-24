/*
** EPITECH PROJECT, 2024
** inventory_sys
** File description:
** item
*/

#pragma once

#include <SFML/Graphics.h>

typedef struct weapon_s {
    int damage;
    int is_equipped;
    sfSprite *sprite;
} weapon_t;

enum armor_type {
    HELMET,
    CHESTPLATE,
    BOOTS
};

typedef struct armor_s {
    int defense;
    int speed;
    int armor_type;
    int is_equipped;
    int endurance;
    sfSprite *sprite;
} armor_t;

weapon_t *create_weapon(int damage);
armor_t *create_armor(int defense, int speed, int armor_type, int endurance);
