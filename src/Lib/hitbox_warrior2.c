/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** hitbox_warrior2
*/

#include "rpg.h"

bool warrior_can_attack_enemy(rpg_t *rpg, warrior_t *warrior)
{
    lwarrior_t *tmp = rpg->lwarrior;

    while (tmp) {
        if (warrior != tmp->warrior && tmp->warrior->faction != warrior->faction
            && warrior_can_attack_target(warrior, tmp->warrior))
            return true;
        tmp = tmp->next;
    }
    return false;
}
