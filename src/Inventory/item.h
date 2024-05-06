/*
** EPITECH PROJECT, 2024
** inventory_sys
** File description:
** item
*/

#pragma once

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "rpg.h"

weapon_t *create_weapon(int damage);
armor_t *create_armor(int defense, int speed, int armor_type, int endurance);
