/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** tools2
*/

#include "rpg.h"

bool warrior_see_enemy(warrior_t *warrior, warrior_t *enemy)
{
    if (warrior_look_at_enemy(warrior, enemy))
        return hitbox_in_detection(enemy->zones->hitbox,
            warrior->zones->radius_max_detection, warrior->pos);
    else if (!IS_DISCREET(enemy))
        return hitbox_in_detection(enemy->zones->hitbox,
            warrior->inter->radius, warrior->pos);
    else
        return false;
}

sfColor get_color_from_faction(warrior_t *warrior)
{
    faction_t faction = warrior->faction;

    if (faction == BLUE_TEAM)
        return DAMAGE_COLOR_BLUE;
    if (faction == PURPLE_TEAM)
        return DAMAGE_COLOR_PURPLE;
    if (faction == YELLOW_TEAM)
        return DAMAGE_COLOR_YELLOW;
    if (faction == RED_TEAM)
        return DAMAGE_COLOR_RED;
    if (faction == GOBLIN_TEAM)
        return DAMAGE_COLOR_GREEN;
    return sfWhite;
}
