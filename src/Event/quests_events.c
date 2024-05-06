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
        if (strcmp(tmp->proprietary, entity->common->name) != 0
            || tmp->quest->is_active == true)
            continue;
        text_box_handling(rpg, tmp);
    }
}

void accept_quest(rpg_t *rpg)
{
    all_quests_t *tmp = rpg->quests;

    while (tmp != NULL) {
        if (!strcmp(tmp->proprietary, rpg->text_box->entity->common->name) &&
                tmp->quest->is_active == false) {
            tmp->quest->is_active = true;
            rpg->text_box->is_displayed = false;
            rpg->quest_header->state = Q_START;
            rpg->ent[0]->common->state = IDLE;
            printf("Quest accepted: %s\n", tmp->quest->name);
        }
        tmp = tmp->next;
    }
}

void refuse_quest(rpg_t *rpg)
{
    all_quests_t *tmp = rpg->quests;

    while (tmp != NULL) {
        if (strcmp(tmp->proprietary, rpg->text_box->entity->common->name) == 0
            && tmp->quest->is_active == false) {
            rpg->text_box->is_displayed = false;
            rpg->text_box->is_fully_displayed = false;
            rpg->text_box->len = 0;
            free(rpg->text_box->displayed_str);
            rpg->ent[0]->common->state = IDLE;
        }
        tmp = tmp->next;
    }
}

void quest_handling(rpg_t *rpg, entity_t *tmp)
{
    if (!tmp->in_view)
        return;
    if (is_player_interact_entity(rpg, tmp)) {
        rpg->text_box->entity = tmp;
        if (rpg->event.key.code == sfKeyE)
            interact_with_entity(rpg, tmp);
        if (rpg->event.key.code == sfKeyEnter &&
        rpg->text_box->is_fully_displayed == true)
            choice_action(rpg);
        dialog_handling(rpg);
        if ((rpg->event.key.code == sfKeyUp ||
            rpg->event.key.code == sfKeyDown)
            && rpg->text_box->is_fully_displayed == true &&
                rpg->text_box->dialog->next == NULL)
            change_choice(rpg);
    }
}

void quest_event(rpg_t *rpg)
{
    if ((rpg->event.key.code == sfKeyE ||
        rpg->event.key.code == sfKeyEnter ||
        rpg->ent[0]->common->state == INTERACT)
        && rpg->event.type == sfEvtKeyReleased) {
        for (unsigned int i = 0; i < rpg->ent_size; i++) {
            quest_handling(rpg, rpg->ent[i]);
        }
    }
}
