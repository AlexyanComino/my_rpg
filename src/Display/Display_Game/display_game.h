/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** display_game
*/

#pragma once

#include "rpg.h"

// Display game
void display_game(rpg_t *rpg);

// Display quests
void display_quests(rpg_t *rpg);

// Display text box
void display_text_box(rpg_t *rpg);

// Display decors
void display_decors_ground(rpg_t *rpg, bool(*in_view)(rpg_t *, sfIntRect));
void display_decors_high(rpg_t *rpg, bool(*in_view)(rpg_t *, sfIntRect));

// Display game interface
void display_command_help(rpg_t *rpg);
void display_game_interface(rpg_t *rpg);
