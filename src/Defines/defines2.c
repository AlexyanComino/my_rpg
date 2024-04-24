/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** defines2
*/

#include "rpg.h"

bool not_attacking(warrior_t *warrior)
{
    return warrior->state != ATTACK && warrior->state != ST_ATT;
}

bool player_is_not_attacking(rpg_t *rpg)
{
    return not_attacking(rpg->lwarrior->warrior);
}
