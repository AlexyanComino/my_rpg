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

weapon_t *create_weapon(rpg_t *rpg, char *name);
armor_t *create_armor(rpg_t *rpg, char *name);
