/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_all
*/

#include "rpg.h"

void update_all(rpg_t *rpg)
{
    lwarrior_t *tmp = rpg->lwarrior;

    while (tmp) {
        anim_warrior(tmp->warrior);
        tmp = tmp->next;
    }
}
