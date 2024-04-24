/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_warrior
*/

#include "rpg.h"


void update_warriors(rpg_t *rpg)
{
    lwarrior_t *tmp = rpg->lwarrior;
    warrior_t *player = rpg->lwarrior->warrior;

    while (tmp) {
        if (!is_warrior_in_view(rpg, tmp->warrior) &&
            tmp->warrior->state == RIEN)
            return;
        update_all_warriors(rpg, tmp->warrior);
        if (tmp->warrior != player && is_alive(tmp->warrior))
            update_pnj_warrior(rpg, tmp->warrior);
        tmp = tmp->next;
    }
}
