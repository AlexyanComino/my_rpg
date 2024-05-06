/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_entity_action
*/

#include "rpg.h"

static void init_warrior_attack(entity_t *entity)
{
    entity->spe->warrior->line_attack = 0;
    entity->spe->warrior->max_line_attack = 0;
    if (entity->common->y == NONE)
        entity->common->anim->rect.top = WARRIOR_WIDTH * 2;
    if (entity->common->y == DOWN)
        entity->common->anim->rect.top = WARRIOR_WIDTH * 4;
    if (entity->common->y == UP)
        entity->common->anim->rect.top = WARRIOR_WIDTH * 6;
}

static void init_pawn_action(entity_t *entity)
{
    if (entity->common->state == ST_WORK)
        entity->common->anim->rect.top = PAWN_WIDTH * 2;
    if (entity->common->state == ST_ATT)
        entity->common->anim->rect.top = PAWN_WIDTH * 3;
    if (entity->common->state == IDLE_CARRY)
        entity->common->anim->rect.top = PAWN_WIDTH * 4;
}

static void init_torch_attack(entity_t *entity)
{
    if (entity->common->y == NONE)
        entity->common->anim->rect.top = TORCH_WIDTH * 2;
    if (entity->common->y == DOWN)
        entity->common->anim->rect.top = TORCH_WIDTH * 3;
    if (entity->common->y == UP)
        entity->common->anim->rect.top = TORCH_WIDTH * 4;
}

void init_entity_action(entity_t *entity)
{
    entity->common->anim->rect.left = 0;
    if (entity->type == WARRIOR && entity->common->state == ST_ATT)
        init_warrior_attack(entity);
    if (entity->type == PAWN)
        init_pawn_action(entity);
    if (entity->type == TORCH && entity->common->state == ST_ATT)
        init_torch_attack(entity);
    sfClock_restart(entity->common->anim->myclock->clock);
}
