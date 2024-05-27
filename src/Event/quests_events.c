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
        entity->common->x =
            get_entity_side(entity, get_player(rpg)->common->pos);
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

static int check_stuff_for_quest(rpg_t *rpg, quest_t *quest)
{
    slot_t *tmp = rpg->inventory->player_status->stuff;
    char *name = NULL;

    for (; tmp; tmp = tmp->next) {
        if (tmp->item == NULL)
            continue;
        name = (tmp->type == WEAPON) ? ((weapon_t *)tmp->item)->name :
            ((armor_t *)tmp->item)->name;
        if (strcmp(name, quest->objective) == 0) {
            quest->is_active = false;
            quest->is_done = true;
            rpg->text_box->is_displayed = false;
            setup_end_header(rpg, quest->name);
            get_player(rpg)->common->state = IDLE;
            add_xp(quest->xp);
            printf("Quest done: %s\n", quest->name);
            return 0;
        }
    }
    return 1;
}

static int check_quest_already_done(rpg_t *rpg, quest_t *quest)
{
    slot_t *tmp = rpg->inventory->slot;
    entity_t *player = get_player(rpg);

    for (; tmp && quest->type == GATHER; tmp = tmp->next) {
        if (tmp->item == NULL)
            continue;
        if (strcmp(tmp->name, quest->objective) == 0) {
            quest->is_active = false;
            quest->is_done = true;
            rpg->text_box->is_displayed = false;
            setup_end_header(rpg, quest->name);
            player->common->state = IDLE;
            add_xp(quest->xp);
            printf("Quest already done: %s\n", quest->name);
            return 0;
        }
    }
    if (check_stuff_for_quest(rpg, quest) == 0)
        return 0;
    return 1;
}

static int accept_one_quest(rpg_t *rpg, all_quests_t *tmp, entity_t *player)
{
    for (quest_t *tmp_quest = tmp->quest; tmp_quest;
        tmp_quest = tmp_quest->next) {
        if (tmp_quest->is_done == true)
            continue;
        if (strcmp(tmp->proprietary, rpg->text_box->entity->common->name) != 0
            || tmp_quest->is_active != false)
            continue;
        if (check_quest_already_done(rpg, tmp_quest) == 0)
            return 1;
        tmp_quest->is_active = true;
        rpg->text_box->is_displayed = false;
        set_string_to_text(rpg->quest_header->text, tmp_quest->name);
        rpg->quest_header->state = Q_START;
        player->common->state = IDLE;
        printf("Quest accepted: %s\n", tmp_quest->name);
        return 1;
    }
    return 0;
}

void accept_quest(rpg_t *rpg)
{
    all_quests_t *tmp = rpg->quests;
    entity_t *player = get_player(rpg);

    while (tmp != NULL) {
        if (accept_one_quest(rpg, tmp, player) == 1)
            return;
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
    if (!tmp->in_view || is_player(rpg, tmp))
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
            rpg->event.key.code == sfKeyDown) &&
            rpg->text_box->is_fully_displayed == true &&
            rpg->text_box->dialog->next == NULL && rpg->text_box->has_choice) {
            change_choice(rpg);
        }
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
