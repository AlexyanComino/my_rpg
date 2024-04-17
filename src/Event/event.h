/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** event
*/
#pragma once

#include "rpg.h"

// Event
void event(rpg_t *rpg);

// Player
state_warrior_t get_player_state(rpg_t *rpg);

// Player move
void player_move(rpg_t *rpg, float dt);

// Player attack
void player_attack(rpg_t *rpg);
void event_player_attack(rpg_t *rpg);
