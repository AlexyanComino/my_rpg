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

// Player move
void player_move(rpg_t *rpg);

// Player attack
void player_attack(rpg_t *rpg);
void event_player_attack(rpg_t *rpg);

// Quest event
void quest_event(rpg_t *rpg);
