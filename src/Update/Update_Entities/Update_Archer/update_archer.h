/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_archer
*/

#pragma once

// Update archer
void remove_arrow(arrows_t **head, arrows_t *tmp, arrows_t *prev);
void update_archer(rpg_t *rpg, entity_t *entity);

// Anim archer
void anim_archer(rpg_t *rpg, entity_t *entity);

// Get hitbox archer
sfIntRect get_hitbox_archer(sfVector2f pos, float scale);
sfIntRect get_hitbox_attack_archer(sfVector2f pos, side_x_t x, side_y_t y,
    float scale);
sfIntRect get_hitbox_archer_foot(sfVector2f pos, float scale);

// Shoot arrow
void shoot_arrow(rpg_t *rpg, entity_t *entity, arrow_dir_t dir);

// Update pnj archer
void update_pnj_archer(rpg_t *rpg, entity_t *entity);

// Update archer pos
void update_archer_pos(rpg_t *rpg, entity_t *entity, entity_t *enemy);

// Update archer marks
void update_archer_marks(entity_t *entity);
