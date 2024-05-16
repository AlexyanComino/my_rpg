/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** defines
*/

#include "rpg.h"

bool is_alive(entity_t *entity)
{
    return entity->common->state != DEAD && entity->common->state != RIEN;
}

bool is_player(rpg_t *rpg, entity_t *entity)
{
    return rpg->ent[rpg->player_index] == entity;
}

bool is_dead(entity_t *entity)
{
    return entity->common->state == DEAD;
}

bool is_discreet(entity_t *entity)
{
    if (!entity)
        return false;
    return entity->common->state == WALK || entity->common->state == IDLE ||
        entity->common->state == ST_ATT || entity->common->state == ST_WORK;
}

bool is_attacking(entity_t *entity)
{
    return entity->common->state == ATTACK || entity->common->state == ST_ATT;
}
