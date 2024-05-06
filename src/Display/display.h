/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** display
*/
#pragma once

#include "rpg.h"

// Display
void display_all(rpg_t *rpg);

// Display menus
void display_main_menu(rpg_t *rpg);
void display_settings(rpg_t *rpg);
void display_save_menu(rpg_t *rpg);

void display_warrior(void *vrpg, entity_t *entity);

// Display entities
void display_entities(rpg_t *rpg);
