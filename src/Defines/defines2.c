/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** defines2
*/

#include "rpg.h"

bool entities_in_same_faction(entity_t *entity1, entity_t *entity2)
{
    return entity1->common->faction == entity2->common->faction;
}

bool entity_has_base(entity_t *entity)
{
    return (entity->type == WARRIOR && entity->spe->warrior->base != NULL) ||
        (entity->type == ARCHER && entity->spe->archer->base != NULL);
}

bool in_action(entity_t *entity)
{
    return is_attacking(entity) || entity->common->state == WORK ||
        entity->common->state == ST_WORK;
}
