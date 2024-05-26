/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** xp
*/

#include "rpg.h"


int add_xp(int xp)
{
    (*inventory())->player_status->xp += xp;
    return 0;
}

int manage_xp(void)
{
    if ((*inventory())->player_status->xp >=
        (*inventory())->player_status->max_xp) {
        (*inventory())->player_status->xp = 0;
        (*inventory())->player_status->max_xp *= 1.5;
        (*inventory())->player_status->level += 1;
        (*inventory())->player_status->skill_points += 1;
        (*inventory())->player_status->max_hp += 10;
        (*inventory())->player_status->hp =
        (*inventory())->player_status->max_hp;
        (*inventory())->player_status->attack += 5;
        (*inventory())->player_status->defense += 5;
        (*inventory())->player_status->speed += 5;
    }
    return 0;
}
