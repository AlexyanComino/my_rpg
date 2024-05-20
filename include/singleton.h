/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** singleton
*/

#pragma once
#include "rpg.h"
#include "../src/Inventory/inventory.h"

sfVector2f *view_pos(void);
inventory_t **inventory(void);
sfText *init_text(sfVector2f pos, int size, sfColor color, char *val);
