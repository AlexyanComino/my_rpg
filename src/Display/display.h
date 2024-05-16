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

// Display common
void display_common(rpg_t *rpg, entity_t *entity);

// Display menus
void display_main_menu(rpg_t *rpg);
void display_settings(rpg_t *rpg);
void display_save_menu(rpg_t *rpg);
void display_selector(rpg_t *rpg);

// Display warriors
void display_warrior(void *vrpg, entity_t *entity);

// Display pawns
void display_pawn(void *vrpg, entity_t *entity);

// Display torch
void display_torch(void *vrpg, entity_t *entity);

// Display entities
void display_entities(rpg_t *rpg);

// Display quests
void display_quests(rpg_t *rpg);
void display_text_box(rpg_t *rpg);
