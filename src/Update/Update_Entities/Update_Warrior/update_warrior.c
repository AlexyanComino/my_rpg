/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_warrior
*/

#include "rpg.h"

void update_warrior(void *vrpg, entity_t *entity)
{
    rpg_t *rpg = vrpg;

    if (entity->common->state == RIEN)
        return;
    update_common(rpg, entity);
    anim_warrior(rpg, entity);
    if (!is_player(rpg, entity) && is_alive(entity))
        update_pnj_warrior(rpg, entity);
}
