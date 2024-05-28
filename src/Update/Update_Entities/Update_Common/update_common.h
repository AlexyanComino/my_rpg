/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_common
*/

#pragma once

#include "rpg.h"

// damage text
void add_dmg_text(rpg_t *rpg, entity_t *entity, int attack,
    damage_text_state_t state);
void update_damage_texts(damage_text_t **damage_texts);

// Entity attack
void entity_is_dead(rpg_t *rpg, entity_t *entity);
void decrease_health(rpg_t *rpg, entity_t *entity, entity_t *target);
void entity_attack(rpg_t *rpg, entity_t *entity);

// Update entity detection
void update_entity_detection(rpg_t *rpg, entity_t *entity);

// Update common
void update_grade_icon_pos(entity_t *entity);
void update_common(rpg_t *rpg, entity_t *entity);

// Update common2
void update_entity_sprite(entity_t *entity);

// Entity move
void entity_move(rpg_t *rpg, entity_t *entity, sfVector2f target_pos,
    float min_lenght);

// Init entity action
void init_entity_action(entity_t *entity);

// Entity stun
void entity_stun(rpg_t *rpg, entity_t *entity);

// Update entity pos
sfVector2f get_movement(sfVector2f center_target, sfVector2f center_entity,
    float distance, int speed);
void update_entity_pos(rpg_t *rpg, entity_t *entity, sfVector2f movement);

// Get hitbox foot
sfIntRect get_hitbox_foot(entity_t *entity, sfVector2f pos);

// Update health bar
void fill_round(round_rectangle_t *rect, float r, sfVector2f pos,
    sfVector2f size);
void update_health_bar(entity_t *entity);
void update_health_bar_boss(rpg_t *rpg, entity_t *entity);

// Flee entity
bool flee_entity(rpg_t *rpg, entity_t *entity, entity_t *enemy);

// Update eff
void update_effs(rpg_t *rpg, entity_t *entity);

// Eff entity attack
void burn_entity(rpg_t *rpg, entity_t *target, unsigned int attack);
void poison_entity(entity_t *target, unsigned int attack);
