/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** damage_text
*/

#include "rpg.h"

void add_damage_text(rpg_t *rpg, warrior_t *target, int attack,
    damage_text_state_t state)
{
    damage_text_t *new = init_damage_text(rpg, target, attack, state);
    damage_text_t *tmp = target->damage_texts;

    if (tmp == NULL) {
        target->damage_texts = new;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}
