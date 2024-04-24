/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** event
*/

#include "rpg.h"

void event_player_attack(rpg_t *rpg)
{
    warrior_t *player = rpg->lwarrior->warrior;

    if (rpg->event.type == sfEvtKeyPressed) {
        if (rpg->event.key.code == sfKeySpace &&
            is_attacking(player)) {
            player->max_line_attack = 1;
        }
        if (rpg->event.key.code == sfKeySpace &&
            not_attacking(player)) {
            player->state = ST_ATT;
            player->line_attack = 0;
            player->max_line_attack = 0;
            player->rect.left = 0;
            update_attack_rect(player);
            sfClock_restart(player->myclock->clock);
        }
    }
}

void event_states(rpg_t *rpg)
{
    if (rpg->gamestate == MAIN_MENU) {
            menu_button_event(rpg, rpg->main_menu->buttons);
    } else if (rpg->gamestate == SETTINGS)
        menu_button_event(rpg, rpg->settings->buttons);
    if (rpg->gamestate == GAME)
        event_player_attack(rpg);
}

void event(rpg_t *rpg)
{
    sfTime elapsed_time = sfClock_getElapsedTime(rpg->win->clock);

    rpg->win->dt = sfTime_asSeconds(elapsed_time);
    sfClock_restart(rpg->win->clock);
    while (sfRenderWindow_pollEvent(rpg->win->window, &rpg->event)) {
        if (rpg->event.type == sfEvtClosed ||
            rpg->event.key.code == sfKeyEscape)
            sfRenderWindow_close(rpg->win->window);
        event_states(rpg);
    }
    if (rpg->gamestate == GAME)
        if (player_is_not_attacking(rpg) && get_player_state(rpg) != DEAD)
            player_move(rpg);
}
