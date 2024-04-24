/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** defines
*/

#include "rpg.h"

bool is_alive(warrior_t *warrior)
{
    return warrior->state != DEAD && warrior->state != RIEN;
}

bool is_player(rpg_t *rpg, warrior_t *mwarrior)
{
    return rpg->lwarrior->warrior == mwarrior;
}

bool is_dead(warrior_t *warrior)
{
    return warrior->state == DEAD;
}

bool is_discreet(warrior_t *warrior)
{
    return warrior->state == WALK || warrior->state == IDLE ||
        warrior->state == ST_ATT;
}

bool is_attacking(warrior_t *warrior)
{
    return warrior->state == ATTACK || warrior->state == ST_ATT;
}
