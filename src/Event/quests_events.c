/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** quests_events
*/

#include "rpg.h"

void interact_with_entity(rpg_t *rpg, entity_t *entity)
{
    all_quests_t *tmp = rpg->quests;

    for (; tmp; tmp = tmp->next) {
        if (strcmp(tmp->proprietary, entity->common->name) != 0 ||
                tmp->quest->is_active == true)
                    continue;
        if (tmp->quest->is_displayed == false) {
            sfText_setString(rpg->quest_text, tmp->quest->name);
            sfText_setString(rpg->quest_desc, tmp->quest->description);
            tmp->entity = entity;
            tmp->quest->is_displayed = true;
        } else
            tmp->quest->is_displayed = false;
    }
}

void accept_quest(rpg_t *rpg, entity_t *entity)
{
    all_quests_t *tmp = rpg->quests;

    while (tmp != NULL) {
        if (strcmp(tmp->proprietary, entity->common->name) == 0 &&
                tmp->quest->is_active == false) {
            tmp->quest->is_active = true;
            tmp->quest->is_displayed = false;
            printf("Quest accepted: %s\n", tmp->quest->name);
        }
        tmp = tmp->next;
    }
}

void quest_handling(rpg_t *rpg, entity_t *tmp)
{
    if (!tmp->in_view)
        return;
    if (is_player_interact_entity(rpg, tmp)) {
        if (rpg->event.key.code == sfKeyE)
            interact_with_entity(rpg, tmp);
        if (rpg->event.key.code == sfKeyEnter)
            accept_quest(rpg, tmp);
    }
}

void quest_event(rpg_t *rpg)
{
    if ((rpg->event.key.code == sfKeyE || rpg->event.key.code == sfKeyEnter)
        && rpg->event.type == sfEvtKeyReleased) {
        for (unsigned int i = 0; i < rpg->ent_size; i++) {
            quest_handling(rpg, rpg->ent[i]);
        }
    }
}
