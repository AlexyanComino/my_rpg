/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_interface_pos
*/

#include "rpg.h"

void update_interface_pos(rpg_t *rpg, entity_t *player, sfVector2f oldPos)
{
    float diff_x = player->common->pos.x - oldPos.x;
    float diff_y = player->common->pos.y - oldPos.y;

    rpg->interface->restricted->danger_pos.x += diff_x;
    rpg->interface->restricted->danger_pos.y += diff_y;
    sfSprite_setPosition(rpg->interface->restricted->sprite,
        rpg->interface->restricted->danger_pos);
}
