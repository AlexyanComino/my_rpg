/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** lib
*/
#pragma once

#include "rpg.h"

// Hitbox_warrior
sfIntRect get_hitbox_warrior(sfVector2f pos);
sfIntRect get_hitbox_attack(sfVector2f pos, x_warrior_t x, y_warrior_t y);
bool is_warrior_hitbox_collide(rpg_t *rpg, warrior_t *warrior,
    sfIntRect hitbox);
bool warrior_can_attack_target(warrior_t *attacker, warrior_t *target);
bool hitbox_in_detection(sfIntRect hitbox, unsigned int radius,
    sfVector2f circle_pos);

// Hitbox warrior2
bool warrior_can_attack_enemy(rpg_t *rpg, warrior_t *warrior);

// Tools
bool is_warrior_in_view(rpg_t *rpg, warrior_t *warrior);
float get_distance_between_pos(sfVector2f center1, sfVector2f center2);
warrior_t *get_nearest_warrior(rpg_t *rpg, warrior_t *warrior);
void update_clock_seconds(my_clock_t *myclock);
bool warrior_look_at_enemy(warrior_t *warrior, warrior_t *enemy);
bool warrior_see_enemy(warrior_t *warrior, warrior_t *enemy);
sfColor get_color_from_faction(warrior_t *warrior);
