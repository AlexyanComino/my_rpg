/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_quests
*/

#include "rpg.h"


void check_quest_done(rpg_t *rpg, entity_t *entity, quest_t *tmp)
{
    if (entity->common->state == DEAD &&
        strcmp(entity->common->name, tmp->objective) == 0) {
        tmp->is_done = true;
        rpg->quest_header->state = Q_END;
        printf("Quest done: %s\n", tmp->name);
    }
}

void update_quest_list(rpg_t *rpg, quest_t *tmp)
{
    if (tmp->is_active && !tmp->is_done && tmp->type == KILL) {
        for (unsigned int i = 0; i < rpg->ent_size; i++) {
            check_quest_done(rpg, rpg->ent[i], tmp);
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
