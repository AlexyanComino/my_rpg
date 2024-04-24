/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_all
*/

#include "rpg.h"

void update_quests(rpg_t *rpg)
{
    all_quests_t *quests = rpg->quests;
    quest_t *tmp = NULL;
    lwarrior_t *lwarrior = NULL;

    for (; quests; quests = quests->next) {
        tmp = quests->quest;
        for (; tmp; tmp = tmp->next) {
            if (tmp->is_active && !tmp->is_done && tmp->type == KILL) {
                lwarrior = rpg->lwarrior->next;
                for (; lwarrior; lwarrior = lwarrior->next) {
                    if (lwarrior->warrior->state == DEAD && strcmp(lwarrior->warrior->name, tmp->objective) == 0) {
                        tmp->is_done = true;
                        printf("Quest done: %s\n", tmp->name);
                    }
                }
            }
        }
    }
}

void update_all(rpg_t *rpg)
{
    if (rpg->gamestate != GAME &&
        rpg->gamestate != PAUSE && rpg->gamestate != END)
        update_background(rpg);
    if (rpg->gamestate == GAME) {
        update_warriors(rpg);
        update_quests(rpg);
    }
}
