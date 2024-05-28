/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_game
*/

#pragma once

#include "rpg.h"

// Update interface pos
void update_interface_pos(rpg_t *rpg, entity_t *player, sfVector2f oldPos);

// Update game interface
void update_game_interface(rpg_t *rpg);

// Update minimap
bool is_valid_minimap_view_pos(minimap_t *minimap, sfVector2f new_pos);
void init_map_pos(rpg_t *rpg);
void update_map(rpg_t *rpg);

// Update popup item
void update_popup_item(rpg_t *rpg);

// Update game
void update_game(rpg_t *rpg);

// Update quests
void update_quests(rpg_t *rpg);
void update_quest_header(rpg_t *rpg);
void quest_done_item(rpg_t *rpg, char *item);

// Update quest header
void update_quest_header(rpg_t *rpg);
int *scroll_quest(int *scroll, int *scroll_max);

// Update chests
void update_chests(rpg_t *rpg);
