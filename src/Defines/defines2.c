/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** defines2
*/

#include "rpg.h"

bool not_attacking(entity_t *entity)
{
    return entity->common->state != ATTACK && entity->common->state != ST_ATT;
}

bool player_is_not_attacking(rpg_t *rpg)
{
    return not_attacking(rpg->ent[0]);
}

bool player_is_alive(rpg_t *rpg)
{
    return is_alive(rpg->ent[0]);
}

bool entities_in_same_faction(entity_t *entity1, entity_t *entity2)
{
    return entity1->common->faction == entity2->common->faction;
}

bool entity_has_base(entity_t *entity)
{
    return (entity->type == WARRIOR && entity->spe->warrior->base != NULL);
}
