/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_pawn
*/

#include "rpg.h"

static pawn_job_t get_job(char *job)
{
    if (!strcmp(job, "W"))
        return WORKING;
    if (!strcmp(job, "CA"))
        return CARRY;
    if (!strcmp(job, "CU"))
        return CUT;
    if (!strcmp(job, "E"))
        return EMOTE;
    return NO_JOB;
}

float get_new_job_cooldown(pawn_job_t job)
{
    float cooldown = 0;

    if (job == WORKING)
        cooldown = 1.5 + ((float)rand() / RAND_MAX) * 2.0;
    if (job == CUT)
        cooldown = 3.0 + ((float)rand() / RAND_MAX) * 2.0;
    if (job == CARRY)
        cooldown = 2.0 + ((float)rand() / RAND_MAX) * 2.0;
    return cooldown;
}

static side_x_t get_job_side(char *side)
{
    if (!strcmp(side, "R"))
        return RIGHT;
    return LEFT;
}

static item_pawn_type_t get_item_type(char *item)
{
    if (!strcmp(item, "W"))
        return WOOD;
    if (!strcmp(item, "M"))
        return MEAT;
    if (!strcmp(item, "G"))
        return GOLD;
    return NO_ITEM;
}

static carry_t *get_pawn_carry(pawn_t *pawn, char **infos)
{
    carry_t *carry = NULL;

    if (pawn->job != CARRY)
        return NULL;
    carry = malloc(sizeof(carry_t));
    carry->obj_pos = (sfVector2f){atoi(infos[19]), atoi(infos[20])};
    carry->item_type = get_item_type(infos[21]);
    carry->item = init_item_pawn(carry->item_type);
    return carry;
}

static pawn_t *init_pawn(char **infos)
{
    pawn_t *pawn = malloc(sizeof(pawn_t));

    pawn->job = get_job(infos[15]);
    pawn->job_pos = (sfVector2f){atoi(infos[16]), atoi(infos[17])};
    if (pawn->job == NO_JOB)
        return pawn;
    pawn->myclock = init_my_clock();
    pawn->job_cooldown = get_new_job_cooldown(pawn->job);
    pawn->job_side = get_job_side(infos[18]);
    pawn->carry = get_pawn_carry(pawn, infos);
    return pawn;
}

static spe_t *init_spe_pawn(char **infos)
{
    spe_t *spe = malloc(sizeof(spe_t));

    spe->pawn = init_pawn(infos);
    return spe;
}

entity_t *init_entity_pawn(char **infos)
{
    entity_t *entity = malloc(sizeof(entity_t));

    entity->type = PAWN;
    entity->common = init_common(infos, PAWN);
    entity->spe = init_spe_pawn(infos);
    entity->in_view = false;
    entity->updt = &update_pawn;
    entity->disp = &display_pawn;
    entity->anim = &anim_pawn;
    entity->destroy = &destroy_entity_pawn;
    entity->get_hitbox = &get_hitbox_pawn;
    entity->get_hitbox_attack = &get_hitbox_attack_pawn;
    entity->get_hitbox_foot = &get_hitbox_pawn_foot;
    return entity;
}
