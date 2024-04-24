/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** event
*/

#include "rpg.h"

void interact_with_warrior(rpg_t *rpg, warrior_t *warrior)
{
    all_quests_t *tmp = rpg->quests;

    while (tmp != NULL) {
        if (strcmp(tmp->proprietary, warrior->name) == 0 && tmp->quest->is_active == false) {
            if (tmp->quest->is_displayed == false) {
                sfText_setString(rpg->quest_text, tmp->quest->name);
                sfText_setString(rpg->quest_desc, tmp->quest->description);
                tmp->warrior = warrior;
                tmp->quest->is_displayed = true;
            } else
                tmp->quest->is_displayed = false;
        }
        tmp = tmp->next;
    }
}

void accept_quest(rpg_t *rpg, warrior_t *warrior)
{
    all_quests_t *tmp = rpg->quests;

    while (tmp != NULL) {
        if (strcmp(tmp->proprietary, warrior->name) == 0 && tmp->quest->is_active == false) {
            tmp->quest->is_active = true;
            tmp->quest->is_displayed = false;
            printf("Quest accepted: %s\n", tmp->quest->name);
        }
        tmp = tmp->next;
    }
}

void event_states(rpg_t *rpg)
{
    lwarrior_t *tmp = NULL;

    if (rpg->gamestate == MAIN_MENU)
        menu_button_event(rpg, rpg->main_menu->buttons);
    if (rpg->gamestate == SETTINGS)
        menu_button_event(rpg, rpg->settings->buttons);
    if (rpg->gamestate == SAVE_MENU)
        menu_button_event(rpg, rpg->save_menu->buttons);
    if (rpg->gamestate == GAME) {
        event_player_attack(rpg);
        if ((rpg->event.key.code == sfKeyE || rpg->event.key.code == sfKeyEnter) && rpg->event.type == sfEvtKeyReleased) {
            tmp = rpg->lwarrior->next;
            while (tmp != NULL) {
                if (is_warrior_in_view(rpg, tmp->warrior) && is_player_interact_warrior(rpg, tmp->warrior)) {
                    if (rpg->event.key.code == sfKeyE)
                        interact_with_warrior(rpg, tmp->warrior);
                    if (rpg->event.key.code == sfKeyEnter)
                        accept_quest(rpg, tmp->warrior);
                }
                tmp = tmp->next;
            }
        }
    }
}

void event(rpg_t *rpg)
{
    sfTime elapsed_time = sfClock_getElapsedTime(rpg->win->clock);
    float dt = sfTime_asSeconds(elapsed_time);

    sfClock_restart(rpg->win->clock);
    while (sfRenderWindow_pollEvent(rpg->win->window, &rpg->event)) {
        if (rpg->event.type == sfEvtClosed ||
            rpg->event.key.code == sfKeyEscape)
            sfRenderWindow_close(rpg->win->window);
        event_states(rpg);
    }
    if (rpg->gamestate == GAME) {
        if (get_player_state(rpg) != ATTACK)
            player_move(rpg, dt);
    }
}
