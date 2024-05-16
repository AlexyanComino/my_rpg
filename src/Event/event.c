/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** event
*/

#include "rpg.h"

void event_states(rpg_t *rpg)
{
    if (rpg->gamestate == MAIN_MENU)
        return menu_button_event(rpg, rpg->main_menu->buttons);
    if (rpg->gamestate == SETTINGS)
        return menu_button_event(rpg, rpg->settings->buttons);
    if (rpg->gamestate == SAVE_MENU)
        return menu_button_event(rpg, rpg->save_menu->buttons);
    if (rpg->gamestate == GAME)
        return event_game(rpg);
    if (rpg->gamestate == MAP)
        return event_map(rpg);
}

void event(rpg_t *rpg)
{
    sfTime elapsed_time = sfClock_getElapsedTime(rpg->win->clock);
    entity_t *player = get_player(rpg);

    rpg->win->dt = sfTime_asSeconds(elapsed_time);
    sfClock_restart(rpg->win->clock);
    while (sfRenderWindow_pollEvent(rpg->win->window, &rpg->event)) {
        if (rpg->event.type == sfEvtClosed ||
            rpg->event.key.code == sfKeyEscape)
            sfRenderWindow_close(rpg->win->window);
        if (rpg->gamestate == GAME || rpg->gamestate == INVENTORY)
            manage_evt_inv(rpg->event, rpg);
        event_states(rpg);
    }
    if (rpg->gamestate == GAME && player_is_not_in_action(rpg) &&
        player_is_alive(rpg) && !is_stunned(player) &&
        player->common->state != INTERACT)
        player_move(rpg);
}
