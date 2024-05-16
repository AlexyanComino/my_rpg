/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_torch
*/
#pragma once

// Update torch
void update_torch(void *vrpg, entity_t *entity);

// Get hitbox torch
sfIntRect get_hitbox_torch(sfVector2f pos);
sfIntRect get_hitbox_attack_torch(sfVector2f pos, side_x_t x, side_y_t y);
sfIntRect get_hitbox_torch_foot(sfVector2f pos);

// Anim torch
void anim_torch(rpg_t *rpg, entity_t *entity);
