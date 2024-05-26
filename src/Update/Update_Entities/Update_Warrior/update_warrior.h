/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_warriors
*/
#pragma once

// Update warrior
void update_warrior(rpg_t *rpg, entity_t *entity);

// Update pnj warrior
void update_pnj_warrior(rpg_t *rpg, entity_t *tmp);

// Update warrior marks
void update_warrior_marks(entity_t *entity);

// Update warrior pos
void update_warrior_pos(rpg_t *rpg, entity_t *tmp, entity_t *enemy);

// Anim warrior
void anim_warrior(rpg_t *rpg, entity_t *entity);

// Hitbox_warrior
sfIntRect get_hitbox_warrior(sfVector2f pos, float scale);
sfIntRect get_warrior_hitbox_attack(sfVector2f pos, side_x_t, side_y_t y,
    float scale);
sfIntRect get_hitbox_warrior_foot(sfVector2f pos, float scale);
