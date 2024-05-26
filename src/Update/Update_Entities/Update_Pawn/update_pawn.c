/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_pawn
*/

#include "rpg.h"

void update_pawn(rpg_t *rpg, entity_t *entity)
{
    update_common(rpg, entity);
    if (entity->common->state == RIEN)
        return;
    anim_pawn(rpg, entity);
    if (!is_player(rpg, entity) && is_alive(entity))
        update_pnj_pawn(rpg, entity);
}
