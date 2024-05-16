/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_pawn
*/

#include "rpg.h"

void update_pawn(void *vrpg, entity_t *entity)
{
    rpg_t *rpg = vrpg;

    if (entity->common->state == RIEN)
        return;
    update_common(rpg, entity);
    anim_pawn(rpg, entity);
    if (!is_player(rpg, entity) && is_alive(entity))
        update_pnj_pawn(rpg, entity);
}
