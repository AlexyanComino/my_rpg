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

// Display warriors
void display_warrior(rpg_t *rpg, warrior_t *warrior);
void display_warriors(rpg_t *rpg);

// Display menus
void display_main_menu(rpg_t *rpg);
void display_settings(rpg_t *rpg);
void display_save_menu(rpg_t *rpg);
