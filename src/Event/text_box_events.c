/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** text_box_events
*/

#include "rpg.h"

static void text_is_displayed(rpg_t *rpg)
{
    rpg->text_box->is_displayed = false;
    rpg->text_box->is_fully_displayed = false;
    rpg->text_box->len = 0;
    free(rpg->text_box->displayed_str);
    rpg->text_box->displayed_str = NULL;
    rpg->lwarrior->warrior->state = IDLE;
}

void text_box_handling(rpg_t *rpg, all_quests_t *tmp)
{
    if (rpg->text_box->is_displayed == false) {
        rpg->lwarrior->warrior->state = INTERACT;
        sfText_setString(rpg->quest_header->text, tmp->quest->name);
        sfText_setString(rpg->text_box->npc_name, tmp->proprietary);
        sfText_setOrigin(rpg->text_box->npc_name, (sfVector2f){
            sfText_getGlobalBounds(rpg->text_box->npc_name).width / 2, 0});
        rpg->text_box->dialog = tmp->quest->dialog;
        rpg->text_box->str = strdup(rpg->text_box->dialog->txt);
        rpg->text_box->displayed_str =
            malloc(sizeof(char) * (strlen(rpg->text_box->str) + 1));
        rpg->text_box->displayed_str[0] = '\0';
        tmp->warrior = rpg->text_box->warrior;
        rpg->text_box->is_displayed = true;
    } else
        text_is_displayed(rpg);
}

void change_choice(rpg_t *rpg)
{
    button_state_t state = rpg->text_box->choice->state;

    rpg->text_box->choice->state = rpg->text_box->choice->next->state;
    rpg->text_box->choice->next->state = state;
}

void choice_action(rpg_t *rpg)
{
    button_t *tmp = rpg->text_box->choice;

    for (; tmp != NULL; tmp = tmp->next) {
        if (tmp->state == HOVERED)
            tmp->action(rpg);
    }
}

static void next_dialog(rpg_t *rpg)
{
    dialog_t *tmp = rpg->text_box->dialog;

    if (tmp->next != NULL) {
        rpg->text_box->dialog = tmp->next;
        rpg->text_box->str = strdup(rpg->text_box->dialog->txt);
        rpg->text_box->displayed_str =
            malloc(sizeof(char) * (strlen(rpg->text_box->str) + 1));
        rpg->text_box->displayed_str[0] = '\0';
        rpg->text_box->len = 0;
        rpg->text_box->is_fully_displayed = false;
    }
}

void dialog_handling(rpg_t *rpg)
{
    if (rpg->event.key.code == sfKeySpace &&
        rpg->text_box->is_fully_displayed == false) {
        rpg->event.key.code = sfKeyUnknown;
        rpg->text_box->is_fully_displayed = true;
    }
    if (rpg->event.key.code == sfKeySpace &&
    rpg->text_box->is_fully_displayed == true)
        next_dialog(rpg);
}
