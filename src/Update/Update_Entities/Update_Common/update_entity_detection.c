/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_entity_detection
*/

#include "rpg.h"

static bool enemy_is_in_small_detect(rpg_t *rpg, entity_t *entity,
    entity_t *enemy)
{
    if (enemy == NULL)
        return false;
    if (!hitbox_in_detection(enemy->common->zones->hitbox, entity->common->
        zones->s_radius, entity->common->pos))
        return false;
    if (!entity_look_at_enemy(entity, enemy) && is_discreet(enemy))
        return false;
    if (is_in_line_of_sight(rpg, entity,
        entity->common->pos, enemy->common->pos))
        return false;
    return true;
}

static void update_small_detection(rpg_t *rpg, entity_t *entity,
    entity_t *enemy,
    bool in_base)
{
    if (enemy_is_in_small_detect(rpg, entity, enemy) && in_base) {
        entity->common->zones->s_detect = true;
        if (!is_player(rpg, entity) && !is_stunned(entity))
            entity->common->x = get_entity_side(entity, enemy->common->pos);
    } else {
        entity->common->zones->s_detect = false;
    }
}

static void update_medium_detection(rpg_t *rpg, entity_t *entity,
    entity_t *enemy)
{
    if (entity_see_enemy(rpg, entity, enemy) &&
        !enemy_is_in_small_detect(rpg, entity, enemy)) {
        entity->common->zones->m_detect = true;
        if (!is_player(rpg, entity) && !is_stunned(entity))
            entity->common->x = get_entity_side(entity, enemy->common->pos);
    } else {
        entity->common->zones->m_detect = false;
    }
}

void update_entity_detection(rpg_t *rpg, entity_t *entity)
{
    entity_t *enemy = get_nearest_entity(rpg, entity, false);
    bool in_base;

    if (!enemy || !is_alive(entity))
        return;
    in_base = entity_has_base(entity) && enemy_is_in_base(entity, enemy);
    if (!in_base && !entity_has_base(entity))
        in_base = true;
    update_small_detection(rpg, entity, enemy, in_base);
    update_medium_detection(rpg, entity, enemy);
}
