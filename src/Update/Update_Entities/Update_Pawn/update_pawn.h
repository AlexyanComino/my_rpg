/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_pawn
*/
#pragma once

// Get Hitbox Pawn
sfIntRect get_hitbox_pawn(sfVector2f pos, float scale);
sfIntRect get_hitbox_attack_pawn(sfVector2f pos, side_x_t x, side_y_t y,
    float scale);
sfIntRect get_hitbox_pawn_foot(sfVector2f pos, float scale);

// Anim Pawn
void anim_pawn(rpg_t *rpg, entity_t *entity);

// Update Pawn
void update_pawn(rpg_t *rpg, entity_t *entity);

// Update Pnj Pawn
void update_pnj_pawn(rpg_t *rpg, entity_t *entity);
