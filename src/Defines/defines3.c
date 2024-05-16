/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** defines3
*/

#include "rpg.h"

bool is_stunned(entity_t *entity)
{
    return entity->common->stun->is_stunned;
}

bool is_slow(entity_t *entity)
{
    return entity->common->state == WALK ||
        entity->common->state == MOVE_CARRY;
}

bool is_working(entity_t *entity)
{
    return entity->common->state == WORK || entity->common->state == ST_WORK;
}

bool is_carrying(entity_t *entity)
{
    return entity->type == PAWN && entity->spe->pawn->job == CARRY &&
        (entity->common->state == MOVE_CARRY ||
            entity->common->state == IDLE_CARRY);
}

bool cooldown_is_over(mark_t *mark, float cooldown)
{
    return mark->anim->myclock->seconds > cooldown;
}
