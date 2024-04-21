/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_warrior2
*/

#include "rpg.h"

unsigned int get_max_health(color_warrior_t color)
{
    if (color == BLUE)
        return 100;
    else
        return 150;
}

faction_t get_faction(warrior_t *warrior)
{
    if (warrior->color == BLUE)
        return BLUE_TEAM;
    if (warrior->color == PURPLE)
        return PURPLE_TEAM;
    if (warrior->color == RED)
        return RED_TEAM;
    if (warrior->color == YELLOW)
        return YELLOW_TEAM;
    return GOBLIN_TEAM;
}
