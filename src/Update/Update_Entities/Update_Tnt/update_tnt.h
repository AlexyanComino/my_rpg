/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_tnt
*/
#pragma once

// Update tnt
void update_tnt(void *vrpg, entity_t *entity);

// Get hitbox tnt
sfIntRect get_hitbox_tnt(sfVector2f pos);
sfIntRect get_hitbox_attack_tnt(sfVector2f pos, side_x_t x, side_y_t y);
sfIntRect get_hitbox_tnt_foot(sfVector2f pos);

// Anim tnt
void anim_tnt(entity_t *entity);

// Launch dyna
void launch_dyna(entity_t *entity);

// Update pnj tnt
void update_pnj_tnt(rpg_t *rpg, entity_t *entity);

// Update dyna
void update_dyna(rpg_t *rpg, entity_t *entity);
