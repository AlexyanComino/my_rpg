/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** lib
*/
#pragma once

#include "rpg.h"

// Hitbox_warrior
sfIntRect get_hitbox_warrior(sfVector2f pos, x_warrior_t x);
sfIntRect get_hitbox_attack(sfVector2f pos, x_warrior_t x, y_warrior_t y);
bool is_warrior_hitbox_collide(rpg_t *rpg, warrior_t *warrior,
    sfIntRect hitbox);
bool is_warrior_attack_collide(warrior_t *target, sfIntRect attack);
bool hitbox_in_detection(sfIntRect hitbox, unsigned int radius,
    sfVector2f circle_pos);

// Tools
bool is_warrior_in_view(rpg_t *rpg, warrior_t *warrior);
