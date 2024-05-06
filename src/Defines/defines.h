/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** defines
*/
#pragma once

#include "rpg.h"

// Defines 1
bool is_alive(entity_t *entity);
bool is_player(rpg_t *rpg, entity_t *entity);
bool is_dead(entity_t *entity);
bool is_discreet(entity_t *entity);
bool is_attacking(entity_t *entity);

// Defines 2
bool player_is_not_in_action(rpg_t *rpg);
bool player_is_alive(rpg_t *rpg);
bool entities_in_same_faction(entity_t *entity1, entity_t *entity2);
bool entity_has_base(entity_t *entity);
bool in_action(entity_t *entity);

// Defines 3
bool is_stunned(entity_t *entity);
bool is_slow(entity_t *entity);
bool is_working(entity_t *entity);
bool is_carrying(entity_t *entity);
