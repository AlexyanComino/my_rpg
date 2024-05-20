/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** quests_events
*/

#include "rpg.h"

static int interact_quest(
    rpg_t *rpg, entity_t *entity, all_quests_t *tmp, quest_t *tmp_quest)
{
    for (; tmp_quest; tmp_quest = tmp_quest->next) {
        if (tmp_quest->is_done == true)
            continue;
        if (tmp_quest->is_active == true && tmp_quest->type != TALK)
            return 1;
        printf("Interacting with %s\n", entity->common->name);
        rpg->text_box->has_choice = (tmp_quest->type == TALK) ? false : true;
        text_box_handling(rpg, tmp, tmp_quest);
        if (tmp_quest->is_done == false)
            return 1;
    }
    return 0;
}

void interact_with_entity(rpg_t *rpg, entity_t *entity)
{
    all_quests_t *tmp = rpg->quests;
    quest_t *tmp_quest = NULL;

    for (; tmp; tmp = tmp->next) {
        if (strcmp(tmp->proprietary, entity->common->name) != 0)
            continue;
        tmp_quest = tmp->quest;
        if (interact_quest(rpg, entity, tmp, tmp_quest) == 1)
            continue;
    }
}

int check_quest_already_done(rpg_t *rpg, quest_t *quest)
{
    slot_t *tmp = rpg->inventory->slot;
    entity_t *player = get_player(rpg);

    if (quest->type == GATHER) {
        for (; tmp; tmp = tmp->next) {
            if (tmp->item == NULL)
                continue;
            if (strcmp(tmp->name, quest->objective) == 0) {
                quest->is_done = true;
                rpg->text_box->is_displayed = false;
                rpg->quest_header->state = Q_END;
                player->common->state = IDLE;
                printf("Quest already done: %s\n", quest->name);
                return 0;
            }
        }
    }
    return 1;
}

void accept_quest(rpg_t *rpg)
{
    all_quests_t *tmp = rpg->quests;
    quest_t *tmp_quest = NULL;
    entity_t *player = get_player(rpg);

    while (tmp != NULL) {
        for (tmp_quest = tmp->quest; tmp_quest; tmp_quest = tmp_quest->next) {
            if (tmp_quest->is_done == true)
                continue;
            if (!strcmp(tmp->proprietary, rpg->text_box->entity->common->name) &&
                    tmp_quest->is_active == false) {
                if (check_quest_already_done(rpg, tmp_quest) == 0)
                    return;
                tmp_quest->is_active = true;
                rpg->text_box->is_displayed = false;
                rpg->quest_header->state = Q_START;
                player->common->state = IDLE;
                printf("Quest accepted: %s\n", tmp_quest->name);
                return;
            }
        }
        tmp = tmp->next;
    }
}

void refuse_quest(rpg_t *rpg)
{
    all_quests_t *tmp = rpg->quests;
    entity_t *player = get_player(rpg);

    while (tmp != NULL) {
        if (strcmp(tmp->proprietary, rpg->text_box->entity->common->name) == 0
            && tmp->quest->is_active == false) {
            rpg->text_box->is_displayed = false;
            rpg->text_box->is_fully_displayed = false;
            rpg->text_box->len = 0;
            free(rpg->text_box->displayed_str);
            player->common->state = IDLE;
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
        rpg->text_box->is_fully_displayed == true
        && rpg->text_box->has_choice)
            choice_action(rpg);
        dialog_handling(rpg);
        if ((rpg->event.key.code == sfKeyUp ||
            rpg->event.key.code == sfKeyDown)
            && rpg->text_box->is_fully_displayed == true &&
                rpg->text_box->dialog->next == NULL
                && rpg->text_box->has_choice)
            change_choice(rpg);
    }
}

void quest_event(rpg_t *rpg)
{
    if ((rpg->event.key.code == sfKeyE ||
        rpg->event.key.code == sfKeyEnter ||
        get_player(rpg)->common->state == INTERACT)
        && rpg->event.type == sfEvtKeyReleased) {
        for (unsigned int i = 0; i < rpg->ent_size; i++) {
            quest_handling(rpg, rpg->ent[i]);
        }
    }
}
