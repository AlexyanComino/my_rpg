/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_pawn
*/
#pragma once

// Get Hitbox Pawn
sfIntRect get_hitbox_pawn(sfVector2f pos);
sfIntRect get_hitbox_attack_pawn(sfVector2f pos, side_x_t x, side_y_t y);

// Anim Pawn
void anim_pawn(rpg_t *rpg, entity_t *entity);

// Update Pawn
void update_pawn(void *vrpg, entity_t *entity);
