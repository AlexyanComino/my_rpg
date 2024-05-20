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

weapon_t *create_weapon(int damage, char *name);
armor_t *create_armor(int defense, int speed, int armor_type, char *name);
sfText *init_text(sfVector2f pos, int size, sfColor color, char *val);