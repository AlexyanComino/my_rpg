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

int manage_xp(rpg_t *rpg)
{
    attributes_t *attribute = get_player(rpg)->common->attributes;

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
        attribute->max_health = (*inventory())->player_status->max_hp;
        attribute->attack = (*inventory())->player_status->attack;
        attribute->defense = (*inventory())->player_status->defense;
        attribute->speed = (*inventory())->player_status->speed;
        attribute->level = (*inventory())->player_status->level;
        attribute->xp = (*inventory())->player_status->xp;
    }
    
    return 0;
}
