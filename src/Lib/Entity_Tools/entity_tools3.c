/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** entity_tools3
*/

#include "rpg.h"

bool entity_can_attack_target(entity_t *entity, entity_t *target)
{
    sfIntRect hitbox_attack = entity->common->zones->hitbox_attack;
    sfIntRect hitbox = target->common->zones->hitbox;

    if (!entity_look_at_enemy(entity, target))
        return false;
    if (sfIntRect_intersects(&hitbox_attack, &hitbox, NULL))
        return true;
    return false;
}
