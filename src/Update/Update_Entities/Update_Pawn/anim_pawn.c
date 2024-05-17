/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** anim_pawn
*/

#include "rpg.h"

static void reset_attack_work_pawn(entity_t *entity)
{
    entity->common->anim->rect.top = 0;
    entity->common->anim->rect.left = 0;
    sfClock_restart(entity->common->clock_cooldown_attack->clock);
    if (entity->spe->pawn->job != NO_JOB)
        sfClock_restart(entity->spe->pawn->myclock->clock);
    if (is_working(entity) || is_attacking(entity))
        entity->spe->pawn->job_cooldown =
            get_new_job_cooldown(entity->spe->pawn->job);
    entity->common->state = IDLE;
}

static void animation_attack_work_pawn2(rpg_t *rpg, entity_t *entity)
{
    if (entity->common->anim->rect.left == PAWN_WIDTH * 3) {
        if (is_attacking(entity))
            entity_attack(rpg, entity);
        if (entity->common->state == ST_WORK)
            entity_stun(rpg, entity);
    }
    if (entity->common->anim->rect.left >= PAWN_OFFSET) {
        entity->common->anim->rect.left = 0;
        reset_attack_work_pawn(entity);
    } else
        entity->common->anim->rect.left += PAWN_WIDTH;
}

static void animation_attack_work_pawn(rpg_t *rpg, entity_t *entity)
{
    if (entity->common->anim->myclock->seconds > 0.1) {
        animation_attack_work_pawn2(rpg, entity);
        sfSprite_setTextureRect(entity->common->anim->sprite,
            entity->common->anim->rect);
        sfClock_restart(entity->common->anim->myclock->clock);
    }
}

static void animation_pawn_carrying(entity_t *entity)
{
    if (entity->common->state == IDLE_CARRY) {
        entity->common->anim->rect.top = PAWN_WIDTH * 4;
        anim_line(entity->common->anim, PAWN_OFFSET, PAWN_WIDTH, 0.1);
    }
    if (entity->common->state == MOVE_CARRY) {
        entity->common->anim->rect.top = PAWN_WIDTH * 5;
        anim_line(entity->common->anim, PAWN_OFFSET, PAWN_WIDTH, 0.1);
    }
}

static void animation_pawn(rpg_t *rpg, entity_t *entity)
{
    if (entity->common->state == IDLE || entity->common->state == INTERACT) {
        entity->common->anim->rect.top = 0;
        return anim_line(entity->common->anim, PAWN_OFFSET, PAWN_WIDTH, 0.1);
    }
    if (entity->common->state == WALK || entity->common->state == RUN) {
        entity->common->anim->rect.top = PAWN_WIDTH;
        return anim_line(entity->common->anim, PAWN_OFFSET, PAWN_WIDTH, 0.1);
    }
    if (entity->common->state == WORK || entity->common->state == ST_WORK) {
        entity->common->anim->rect.top = PAWN_WIDTH * 2;
        return animation_attack_work_pawn(rpg, entity);
    }
    if (is_attacking(entity)) {
        entity->common->anim->rect.top = PAWN_WIDTH * 3;
        return animation_attack_work_pawn(rpg, entity);
    }
    animation_pawn_carrying(entity);
}

void anim_pawn(rpg_t *rpg, entity_t *entity)
{
    update_clock_seconds(entity->common->anim->myclock);
    if (is_dead(entity))
        animation_death(entity->common);
    else if (!is_stunned(entity))
        animation_pawn(rpg, entity);
}
