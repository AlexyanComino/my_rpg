/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** warrior_x_y
*/

#include "rpg.h"

static unsigned int get_entity_speed(rpg_t *rpg, entity_t *entity)
{
    if (entity->common->state == WALK || entity->common->state == MOVE_CARRY)
        return entity->common->attributes->speed / 2 * rpg->win->dt;
    return entity->common->attributes->speed * rpg->win->dt;
}

static bool pawn_is_arrived(entity_t *entity, float distance,
    float min_lenght)
{
    if (distance < min_lenght) {
        entity->common->state = IDLE;
        if (entity->spe->pawn->job != NO_JOB)
            sfClock_restart(entity->spe->pawn->myclock->clock);
        return true;
    }
    return false;
}

static bool warrior_is_arrived(entity_t *entity, float distance,
    float min_lenght)
{
    if (distance < min_lenght && entity_has_base(entity) &&
        entity->spe->warrior->base->come_back) {
        entity->common->state = IDLE;
        entity->spe->warrior->base->in_cooldown = true;
        sfClock_restart(entity->spe->warrior->base->myclock->clock);
        return true;
    } else if (distance < min_lenght) {
        entity->common->state = IDLE;
        return true;
    }
    return false;
}

static bool archer_is_arrived(entity_t *entity, float distance,
    float min_lenght)
{
    if (distance < min_lenght && entity_has_base(entity) &&
        entity->spe->archer->base->come_back) {
        entity->common->state = IDLE;
        entity->spe->archer->base->in_cooldown = true;
        sfClock_restart(entity->spe->archer->base->myclock->clock);
        return true;
    } else if (distance < min_lenght) {
        entity->common->state = IDLE;
        return true;
    }
    return false;
}

static bool entity_is_arrived(entity_t *entity, float distance,
    float min_lenght)
{
    switch (entity->type) {
    case PAWN:
        return pawn_is_arrived(entity, distance, min_lenght);
    case WARRIOR:
        return warrior_is_arrived(entity, distance, min_lenght);
    case ARCHER:
        return archer_is_arrived(entity, distance, min_lenght);
    default:
        return false;
    }
}

static void check_entity_is_stuck(entity_t *entity,
    sfVector2f oldPos)
{
    if (fabs(entity->common->pos.x - oldPos.x) < 0.1 &&
        fabs(entity->common->pos.y - oldPos.y) < 0.1) {
            if (entity->common->state == MOVE_CARRY)
                entity->common->state = IDLE_CARRY;
            else
                entity->common->state = IDLE;
        }
}

void entity_move(rpg_t *rpg, entity_t *entity, sfVector2f target_pos,
    float min_lenght)
{
    sfVector2f movement;
    float distance;
    float speed = get_entity_speed(rpg, entity);
    sfVector2f oldPos = entity->common->pos;
    float new_distance;

    distance = get_distance(entity->common->pos, target_pos);
    if (distance < min_lenght) {
        entity_is_arrived(entity, distance, min_lenght);
        return;
    }
    movement = get_movement(target_pos, entity->common->pos, distance, speed);
    update_entity_pos(rpg, entity, movement);
    new_distance = get_distance(entity->common->pos, target_pos);
    if (entity_is_arrived(entity, new_distance, min_lenght))
        return;
    check_entity_is_stuck(entity, oldPos);
}
