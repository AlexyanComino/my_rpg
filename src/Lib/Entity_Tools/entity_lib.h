/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** entity_lib
*/
#pragma once


// Entity Colliders
bool is_entity_hitbox_collide(rpg_t *rpg, entity_t *entity,
    sfIntRect hitbox);

// Entity Tools
entity_t *get_nearest_entity(rpg_t *rpg, entity_t *entity, bool same_faction);
bool entity_look_at_enemy(entity_t *entity, entity_t *enemy);
bool is_player_interact_entity(rpg_t *rpg, entity_t *entity);

// Entity Tools2
bool entity_see_enemy(rpg_t *rpg, entity_t *entity, entity_t *enemy);
sfColor get_color_from_faction(entity_t *entity);
bool hitbox_in_detection(sfIntRect hitbox, unsigned int radius,
    sfVector2f circle_pos);
bool entity_can_attack_enemy(rpg_t *rpg, entity_t *entity);

// Entity Tools3
bool entity_can_attack_target(rpg_t *rpg, entity_t *entity, entity_t *target);
bool entity_can_attack(rpg_t *rpg, entity_t *entity, entity_t *target);
side_x_t get_entity_side(entity_t *entity, sfVector2f pos);
entity_t *get_player(rpg_t *rpg);
bool enemy_is_in_base(entity_t *enemy, entity_t *entity);

// Line of sight
bool is_in_line_of_sight(rpg_t *rpg, entity_t *entity, sfVector2f start,
    sfVector2f end);
