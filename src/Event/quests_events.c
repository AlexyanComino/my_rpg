/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** quests_events
*/

#include "rpg.h"

void interact_with_warrior(rpg_t *rpg, warrior_t *warrior)
{
    all_quests_t *tmp = rpg->quests;

    for (; tmp; tmp = tmp->next) {
        if (strcmp(tmp->proprietary, warrior->name) != 0 ||
                tmp->quest->is_active == true)
                    continue;
        if (rpg->text_box->is_displayed == false) {
            printf("Interacting with %s\n", warrior->name);
            sfText_setString(rpg->quest_header->text, tmp->quest->name);
            sfText_setString(rpg->text_box->npc_name, tmp->proprietary);
            rpg->text_box->str = strdup(tmp->quest->description);
            rpg->text_box->displayed_str = malloc(sizeof(char) * (strlen(rpg->text_box->str) + 1));
            rpg->text_box->displayed_str[0] = '\0';
            tmp->warrior = warrior;
            rpg->text_box->is_displayed = true;
        } else
            rpg->text_box->is_displayed = false;
    }
}

void accept_quest(rpg_t *rpg, warrior_t *warrior)
{
    all_quests_t *tmp = rpg->quests;

    while (tmp != NULL) {
        if (strcmp(tmp->proprietary, warrior->name) == 0 &&
                tmp->quest->is_active == false) {
            tmp->quest->is_active = true;
            rpg->text_box->is_displayed = false;
            rpg->quest_header->state = Q_START;
            printf("Quest accepted: %s\n", tmp->quest->name);
        }
        tmp = tmp->next;
    }
}

void quest_handling(rpg_t *rpg, lwarrior_t *tmp)
{
    if (warrior_is_in_view(rpg, tmp->warrior) &&
    is_player_interact_warrior(rpg, tmp->warrior)) {
        if (rpg->event.key.code == sfKeyE)
            interact_with_warrior(rpg, tmp->warrior);
        if (rpg->event.key.code == sfKeyEnter)
            accept_quest(rpg, tmp->warrior);
    }
}

void quest_event(rpg_t *rpg)
{
    lwarrior_t *tmp = rpg->lwarrior->next;

    if ((rpg->event.key.code == sfKeyE || rpg->event.key.code == sfKeyEnter)
        && rpg->event.type == sfEvtKeyReleased) {
        for (; tmp; tmp = tmp->next)
            quest_handling(rpg, tmp);
    }
}
