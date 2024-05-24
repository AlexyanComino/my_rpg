/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_warrior
*/

#include "rpg.h"

void update_warrior(rpg_t *rpg, entity_t *entity)
{
    update_common(rpg, entity);
    if (entity->common->state == RIEN)
        return;
    entity->anim(rpg, entity);
    if (!is_player(rpg, entity) && is_alive(entity))
        update_pnj_warrior(rpg, entity);
}
