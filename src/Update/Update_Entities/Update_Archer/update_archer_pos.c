/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_archer_pos
*/

#include "rpg.h"

static void update_base_cooldown(entity_t *entity)
{
    update_clock_seconds(entity->spe->archer->base->myclock);
    if (entity->spe->archer->base->in_cooldown &&
        entity->spe->archer->base->myclock->seconds >
        entity->spe->archer->base->cooldown) {
        entity->spe->archer->base->in_cooldown = false;
        entity->spe->archer->base->pattern_pos_index =
        (entity->spe->archer->base->pattern_pos_index + 1) %
        entity->spe->archer->base->max_pos_index;
    }
}

static void come_back_to_next_point(entity_t *tmp,
    entity_t *enemy)
{
    if (!enemy) {
        tmp->spe->archer->base->come_back = true;
        return;
    }
    if (!tmp->common->zones->m_detect && !tmp->common->zones->s_detect)
        tmp->spe->archer->base->come_back = true;
    else
        tmp->spe->archer->base->come_back = false;
}

static void archer_come_back(rpg_t *rpg, entity_t *tmp)
{
    float min_lenght = 10;
    sfVector2f target_pos = tmp->spe->archer->base->pattern_pos[tmp->spe->
        archer->base->pattern_pos_index];

    if (tmp->spe->archer->base->in_cooldown) {
        tmp->common->state = IDLE;
        return;
    }
    tmp->common->state = WALK;
    entity_move(rpg, tmp, target_pos, min_lenght);
}

static void update_archer_defend_base(rpg_t *rpg, entity_t *tmp,
    entity_t *enemy)
{
    float min_lenght = MIN_ARCHER_LENGTH;
    sfVector2f target_pos;

    if (flee_entity(rpg, tmp, enemy))
        return;
    if (!enemy_is_in_base(tmp, enemy)) {
        tmp->common->state = IDLE;
        return;
    }
    target_pos = enemy->common->pos;
    tmp->common->state = RUN;
    tmp->common->x = get_entity_side(tmp, enemy->common->pos);
    entity_move(rpg, tmp, target_pos, min_lenght);
}

static void update_archer_pos_base(rpg_t *rpg, entity_t *entity,
    entity_t *enemy)
{
    come_back_to_next_point(entity, enemy);
    update_base_cooldown(entity);
    if (entity->spe->archer->base->come_back)
        archer_come_back(rpg, entity);
    else
        update_archer_defend_base(rpg, entity, enemy);
}

static void update_archer_pos_no_base(rpg_t *rpg, entity_t *entity,
    entity_t *enemy)
{
    float min_lenght = MIN_ARCHER_LENGTH;
    sfVector2f target_pos;

    if (flee_entity(rpg, entity, enemy))
        return;
    if (enemy && entity->common->zones->m_detect) {
        target_pos = enemy->common->pos;
        entity->common->state = RUN;
        entity->common->x = get_entity_side(entity, enemy->common->pos);
        entity_move(rpg, entity, target_pos, min_lenght);
    } else if (get_distance(entity->common->pos,
        entity->common->init_pos) > 10) {
        min_lenght = 10;
        target_pos = entity->common->init_pos;
        entity->common->state = WALK;
        entity->common->x = get_entity_side(entity, target_pos);
        entity_move(rpg, entity, target_pos, min_lenght);
    } else {
        entity->common->state = IDLE;
    }
}

void update_archer_pos(rpg_t *rpg, entity_t *entity, entity_t *enemy)
{
    if (entity_has_base(entity))
        update_archer_pos_base(rpg, entity, enemy);
    else
        update_archer_pos_no_base(rpg, entity, enemy);
}
