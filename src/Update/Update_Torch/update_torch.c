/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_torch
*/

#include "rpg.h"

void update_torch(void *vrpg, entity_t *entity)
{
    rpg_t *rpg = vrpg;

    if (entity->common->state == RIEN)
        return;
    update_common(rpg, entity);
    anim_torch(rpg, entity);
}
