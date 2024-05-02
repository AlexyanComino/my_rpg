/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** move_warrior
*/

#include "rpg.h"

static unsigned int get_warrior_speed(entity_t *entity)
{
    if (entity->common->state == WALK)
        return entity->common->attributes->speed / 2;
    return entity->common->attributes->speed;
}

static sfVector2f get_target_pos_and_min_lenght(rpg_t *rpg, entity_t *entity,
    float *min_lenght)
{
    sfVector2f target_pos;
    entity_t *target;

    if (entity_has_base(entity) && entity->spe->warrior->base->come_back) {
        target_pos = entity->spe->warrior->base->pattern_pos[entity->spe->
            warrior->base->pattern_pos_index];
        *min_lenght = 10;
    } else {
        target = get_nearest_entity(rpg, entity, false);
        target_pos = target->common->pos;
        *min_lenght = MIN_WARRIOR_LENGTH;
    }
    return target_pos;
}

static bool entity_is_arrived(entity_t *entity, float distance,
    float min_lenght, sfVector2f movement)
{
    if (distance < min_lenght && entity_has_base(entity) &&
        entity->spe->warrior->base->come_back) {
        entity->common->state = IDLE;
        entity->spe->warrior->base->in_cooldown = true;
        sfClock_restart(entity->spe->warrior->base->myclock->clock);
        return true;
    } else if (distance < min_lenght) {
        entity->common->state = IDLE;
        update_side_x(entity, movement);
        update_side_y(entity, movement);
        return true;
    }
    return false;
}

static void check_entity_is_stuck(entity_t *entity,
    sfVector2f oldPos)
{
    if (fabs(entity->common->pos.x - oldPos.x) < 0.1 &&
        fabs(entity->common->pos.y - oldPos.y) < 0.1)
        entity->common->state = IDLE;
}

void warrior_move(rpg_t *rpg, entity_t *entity)
{
    sfVector2f movement;
    sfVector2f target_pos;
    float min_lenght;
    float distance;
    float speed = get_warrior_speed(entity);
    sfVector2f oldPos = entity->common->pos;

    if (entity_has_base(entity) &&
        entity->spe->warrior->base->in_cooldown) {
        entity->common->state = IDLE;
        return;
    }
    target_pos = get_target_pos_and_min_lenght(rpg, entity, &min_lenght);
    distance = get_distance_between_pos(entity->common->pos, target_pos);
    movement = get_movement(target_pos, entity->common->pos, distance, speed);
    if (entity_is_arrived(entity, distance, min_lenght, movement))
        return;
    update_entity_pos(rpg, entity, movement);
    check_entity_is_stuck(entity, oldPos);
}
