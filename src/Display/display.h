/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** display
*/
#pragma once

#include "rpg.h"

// Display
void display(rpg_t *rpg);

// Display menus
void display_main_menu(rpg_t *rpg);
void display_settings(rpg_t *rpg);
void display_save_menu(rpg_t *rpg);
void display_selector(rpg_t *rpg);

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
void display_game_interface(rpg_t *rpg);

// Display loading
void display_anim_text(rpg_t *rpg, anim_text_t *anim_text);
void display_loading(rpg_t *rpg);

// Display end menu
void display_end_menu(rpg_t *rpg);
