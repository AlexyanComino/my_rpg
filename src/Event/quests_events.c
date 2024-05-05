/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** quests_events
*/

#include "rpg.h"

void interact_with_warrior(rpg_t *rpg)
{
    all_quests_t *tmp = rpg->quests;

    for (; tmp; tmp = tmp->next) {
        if (strcmp(tmp->proprietary, rpg->text_box->warrior->name) != 0 ||
                tmp->quest->is_active == true)
                    continue;
        text_box_handling(rpg, tmp);
    }
}

void accept_quest(rpg_t *rpg)
{
    all_quests_t *tmp = rpg->quests;

    while (tmp != NULL) {
        if (strcmp(tmp->proprietary, rpg->text_box->warrior->name) == 0 &&
                tmp->quest->is_active == false) {
            tmp->quest->is_active = true;
            rpg->text_box->is_displayed = false;
            rpg->quest_header->state = Q_START;
            rpg->lwarrior->warrior->state = IDLE;
            printf("Quest accepted: %s\n", tmp->quest->name);
        }
        tmp = tmp->next;
    }
}

void refuse_quest(rpg_t *rpg)
{
    all_quests_t *tmp = rpg->quests;

    while (tmp != NULL) {
        if (strcmp(tmp->proprietary, rpg->text_box->warrior->name) == 0 &&
                tmp->quest->is_active == false) {
            rpg->text_box->is_displayed = false;
            rpg->text_box->is_fully_displayed = false;
            rpg->text_box->len = 0;
            free(rpg->text_box->displayed_str);
            rpg->lwarrior->warrior->state = IDLE;
        }
        tmp = tmp->next;
    }
}

void quest_handling(rpg_t *rpg, lwarrior_t *tmp)
{
    if (warrior_is_in_view(rpg, tmp->warrior) &&
    is_player_interact_warrior(rpg, tmp->warrior)) {
        rpg->text_box->warrior = tmp->warrior;
        if (rpg->event.key.code == sfKeyE)
            interact_with_warrior(rpg);
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
    lwarrior_t *tmp = rpg->lwarrior->next;

    if ((rpg->event.key.code == sfKeyE ||
        rpg->event.key.code == sfKeyEnter ||
        rpg->lwarrior->warrior->state == INTERACT)
        && rpg->event.type == sfEvtKeyReleased) {
        for (; tmp; tmp = tmp->next)
            quest_handling(rpg, tmp);
    }
}
