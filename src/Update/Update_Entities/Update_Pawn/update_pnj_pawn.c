/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_pnj_pawn
*/

#include "rpg.h"

static void work_pawn(entity_t *entity)
{
    update_clock_seconds(entity->spe->pawn->myclock);
    if (entity->spe->pawn->myclock->seconds >=
        entity->spe->pawn->job_cooldown) {
        entity->common->state = ST_WORK;
        init_entity_action(entity);
    }
}

static void cut_pawn(entity_t *entity)
{
    update_clock_seconds(entity->spe->pawn->myclock);
    if (entity->spe->pawn->myclock->seconds >=
        entity->spe->pawn->job_cooldown) {
        entity->common->state = ST_ATT;
        init_entity_action(entity);
    }
}

static void update_entity_side(entity_t *entity, side_x_t side)
{
    entity->common->x = side;
}

static void update_pawn_working_cut(rpg_t *rpg, entity_t *entity)
{
    float min_lenght = 10;
    sfVector2f target_pos = entity->spe->pawn->job_pos;

    entity->common->x = get_entity_side(entity, entity->spe->pawn->job_pos);
    if (get_distance(entity->common->pos,
        entity->spe->pawn->job_pos) < min_lenght) {
        update_entity_side(entity, entity->spe->pawn->job_side);
        if (entity->spe->pawn->job == WORKING)
            work_pawn(entity);
        if (entity->spe->pawn->job == CUT)
            cut_pawn(entity);
    } else {
        entity->common->state = RUN;
        entity_move(rpg, entity, target_pos, min_lenght);
    }
}

static void pawn_attack(rpg_t *rpg, entity_t *entity, entity_t *enemy)
{
    float min_lenght = MIN_PAWN_LENGTH;
    sfVector2f target_pos = enemy->common->pos;

    entity->common->state = RUN;
    entity->common->x = get_entity_side(entity, enemy->common->pos);
    entity_move(rpg, entity, target_pos, min_lenght);
    if (entity_can_attack(rpg, entity, enemy)) {
        entity->common->state = ST_ATT;
        init_entity_action(entity);
    }
}

static void update_item_size(entity_t *entity)
{
    sfVector2f scale =
        sfSprite_getScale(entity->spe->pawn->carry->item->sprite);

    if (entity->common->x == RIGHT && scale.x < 0)
        scale.x *= -1;
    if (entity->common->x == LEFT && scale.x > 0)
        scale.x *= -1;
}

static void update_pawn_carrying(rpg_t *rpg, entity_t *entity)
{
    float min_lenght = 10;
    sfVector2f target_pos = entity->spe->pawn->carry->obj_pos;

    entity->common->state = MOVE_CARRY;
    entity_move(rpg, entity, target_pos, min_lenght);
    update_item_size(entity);
}

static void update_pawn_carry(rpg_t *rpg, entity_t *entity)
{
    float min_lenght = 10;
    sfVector2f target_pos;

    update_clock_seconds(entity->spe->pawn->myclock);
    if (entity->spe->pawn->myclock->seconds < entity->spe->pawn->job_cooldown)
        return;
    if (is_carrying(entity)) {
        update_pawn_carrying(rpg, entity);
    } else {
        target_pos = entity->spe->pawn->job_pos;
        if (get_distance(entity->common->pos,
            entity->spe->pawn->job_pos) < min_lenght) {
            entity->common->state = IDLE_CARRY;
            return;
        }
        entity->common->state = RUN;
        entity_move(rpg, entity, target_pos, min_lenght);
    }
}

static void update_no_job_pawn(rpg_t *rpg, entity_t *entity)
{
    float min_length = 10;
    sfVector2f target_pos = entity->spe->pawn->job_pos;

    if (get_distance(entity->common->pos,
        entity->spe->pawn->job_pos) < min_length) {
        if (entity->spe->pawn->job == EMOTE)
            entity->common->state = IDLE_CARRY;
        else
            entity->common->state = IDLE;
        return;
    }
    entity->common->state = WALK;
    entity_move(rpg, entity, target_pos, min_length);
}

void update_pnj_pawn(rpg_t *rpg, entity_t *entity)
{
    entity_t *enemy = get_nearest_entity(rpg, entity, false);

    if (is_working(entity) || is_attacking(entity) || is_stunned(entity))
        return;
    if (enemy && enemy->common->faction == AGAINST_ALL &&
        entity_see_enemy(rpg, entity, enemy)) {
        pawn_attack(rpg, entity, enemy);
        return;
    }
    if (entity->spe->pawn->job == WORKING || entity->spe->pawn->job == CUT)
        update_pawn_working_cut(rpg, entity);
    else if (entity->spe->pawn->job == CARRY)
        update_pawn_carry(rpg, entity);
    else
        update_no_job_pawn(rpg, entity);
}
