/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** defines
*/
#pragma once

#include "rpg.h"

// Defines 1
bool is_alive(warrior_t *warrior);
bool is_player(rpg_t *rpg, warrior_t *mwarrior);
bool is_dead(warrior_t *warrior);
bool is_discreet(warrior_t *warrior);
bool is_attacking(warrior_t *warrior);

// Defines 2
bool not_attacking(warrior_t *warrior);
bool player_is_not_attacking(rpg_t *rpg);
