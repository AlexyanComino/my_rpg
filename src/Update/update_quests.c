/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_quests
*/

#include "rpg.h"

void check_quest_done(lwarrior_t *lwarrior, quest_t *tmp)
{
    if (lwarrior->warrior->state == DEAD &&
        strcmp(lwarrior->warrior->name, tmp->objective) == 0) {
        tmp->is_done = true;
        printf("Quest done: %s\n", tmp->name);
    }
}

void update_quest_list(rpg_t *rpg, quest_t *tmp)
{
    lwarrior_t *lwarrior = NULL;

    if (tmp->is_active && !tmp->is_done && tmp->type == KILL) {
        lwarrior = rpg->lwarrior->next;
        for (; lwarrior; lwarrior = lwarrior->next) {
            check_quest_done(lwarrior, tmp);
        }
    }
}

void update_quests(rpg_t *rpg)
{
    all_quests_t *quests = rpg->quests;
    quest_t *tmp = NULL;

    for (; quests; quests = quests->next) {
        tmp = quests->quest;
        for (; tmp; tmp = tmp->next) {
            update_quest_list(rpg, tmp);
        }
    }
}
