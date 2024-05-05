/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_entities
*/
#pragma once

// damage text
void add_dmg_text(rpg_t *rpg, entity_t *entity, int attack,
    damage_text_state_t state);
void update_damage_texts(damage_text_t **damage_texts);

// Update entities
void update_entities(rpg_t *rpg);

// Entity attack
void entity_attack(rpg_t *rpg, entity_t *entity);

// Update entity detection
void update_entity_detection(rpg_t *rpg, entity_t *entity);

// Update common
void update_common(rpg_t *rpg, entity_t *entity);

// Entity move
sfVector2f get_movement(sfVector2f center_target, sfVector2f center_entity,
    float distance, int speed);
void update_side_x(entity_t *entity, sfVector2f movement);
void update_side_y(entity_t *entity, sfVector2f movement);
void update_entity_pos(rpg_t *rpg, entity_t *entity, sfVector2f movement);
