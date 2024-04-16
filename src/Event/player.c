/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** player
*/

#include "rpg.h"

state_warrior_t get_player_state(rpg_t *rpg)
{
    return rpg->lwarrior->warrior->state;
}
