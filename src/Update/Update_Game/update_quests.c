/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_quests
*/

#include "rpg.h"

static void check_done_item(quest_t *tmp, char *item, rpg_t *rpg)
{
    if (tmp->type == GATHER && tmp->is_active &&
        strcmp(tmp->objective, item) == 0) {
        tmp->is_active = false;
        tmp->is_done = true;
        if (tmp->next == NULL)
            rpg->text_box->entity->common->grade_type = SOLDAT;
        if (tmp->is_last) {
            setup_end_header(rpg, tmp->name);
        } else
            tmp->next->is_active = true;
        add_xp(tmp->xp);
        printf("Quest get done: %s\n", tmp->name);
    }
}

void quest_done_item(rpg_t *rpg, char *item)
{
    all_quests_t *quests = rpg->quests;
    quest_t *tmp = NULL;

    for (; quests; quests = quests->next) {
        tmp = quests->quest;
        for (; tmp; tmp = tmp->next) {
        check_done_item(tmp, item, rpg);
        }
    }
}

void quest_done_kill(rpg_t *rpg, entity_t *entity, quest_t *tmp)
{
    if (entity->common->state == DEAD &&
        strcmp(entity->common->name, tmp->objective) == 0) {
        tmp->is_active = false;
        tmp->is_done = true;
        if (tmp->next == NULL)
            rpg->text_box->entity->common->grade_type = SOLDAT;
        if (tmp->is_last) {
            setup_end_header(rpg, tmp->name);
        } else
            tmp->next->is_active = true;
        add_xp(tmp->xp);
        printf("Quest done: %s\n", tmp->name);
    }
}

void update_quest_list(rpg_t *rpg, quest_t *tmp)
{
    if (!tmp->is_active || tmp->is_done)
        return;
    if (tmp->type == KILL)
        for (unsigned int i = 0; i < rpg->ent_size; i++) {
            quest_done_kill(rpg, rpg->ent[i], tmp);
        }
}

void update_quests(rpg_t *rpg)
{
    all_quests_t *quests = rpg->quests;
    quest_t *tmp = NULL;

    for (; quests; quests = quests->next) {
        tmp = quests->quest;
        for (; tmp && tmp->name; tmp = tmp->next) {
            update_quest_list(rpg, tmp);
        }
    }
}
