/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** anim
*/
#pragma once

#include "rpg.h"

// Anim warrior
void anim_warrior(rpg_t *rpg, warrior_t *warrior);

// Classic anim warrior
void animation_alive(rpg_t *rpg, warrior_t *warrior);
void animation_dead(warrior_t *warrior);
