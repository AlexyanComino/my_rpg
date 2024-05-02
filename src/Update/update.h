/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update
*/
#pragma once

// Update_all
void update_all(rpg_t *rpg);

// Update background
void update_background(rpg_t *rpg);

// Update quests
void update_quests(rpg_t *rpg);

// Update interface pos
void update_interface_pos(rpg_t *rpg, entity_t *player, sfVector2f oldPos);

// Update game interface
void update_game_interface(rpg_t *rpg);
