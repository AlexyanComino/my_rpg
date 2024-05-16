/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** event
*/

#include "rpg.h"

static void event_player_warrior(rpg_t *rpg, entity_t *player)
{
    if (rpg->event.key.code == sfKeySpace &&
        is_attacking(player)) {
        player->spe->warrior->max_line_attack = 1;
    }
}

static void event_player_pawn(rpg_t *rpg, entity_t *player)
{
    if (rpg->event.key.code == sfKeyA) {
        player->common->state = ST_WORK;
        init_entity_action(player);
    }
    if (rpg->event.key.code == sfKeyR) {
        player->common->state = IDLE_CARRY;
        init_entity_action(player);
    }
}

void event_player_action(rpg_t *rpg)
{
    entity_t *player = rpg->ent[0];

    if (rpg->event.type == sfEvtKeyPressed) {
        if (player->type == WARRIOR)
            event_player_warrior(rpg, player);
        if (player->type == PAWN && !in_action(player))
            event_player_pawn(rpg, player);
        if (rpg->event.key.code == sfKeySpace && !in_action(player) &&
            player->common->state != INTERACT) {
            player->common->state = ST_ATT;
            init_entity_action(player);
        }
        if (rpg->event.key.code == sfKeyP)
            printf("Player pos: %f, %f\n", player->common->pos.x,
                player->common->pos.y);
    }
}

void event_states(rpg_t *rpg)
{
    if (rpg->gamestate == SELECTOR)
        slct_button_event(rpg, rpg->selector->buttons);
    if (rpg->gamestate == SAVE_MENU)
        save_button_event(rpg, rpg->save_menu->buttons);
    if (rpg->gamestate == SETTINGS)
        menu_button_event(rpg, rpg->settings->buttons);
    if (rpg->gamestate == MAIN_MENU)
        menu_button_event(rpg, rpg->main_menu->buttons);
    if (rpg->gamestate == GAME) {
        event_player_action(rpg);
        quest_event(rpg);
    }
}

void update_mouse_pos(rpg_t *rpg)
{
    sfVector2f old_mouse_pos = {(float)rpg->event.mouseMove.x,
        (float)rpg->event.mouseMove.y};
    sfVector2u window_size = sfRenderWindow_getSize(rpg->win->window);

    rpg->win->mouse_pos = (sfVector2f){
        (float)old_mouse_pos.x / ((float)window_size.x / (float)WIDTH),
        (float)old_mouse_pos.y / ((float)window_size.y / (float)HEIGHT)};
}

void event(rpg_t *rpg)
{
    sfTime elapsed_time = sfClock_getElapsedTime(rpg->win->clock);

    rpg->win->dt = sfTime_asSeconds(elapsed_time);
    sfClock_restart(rpg->win->clock);
    while (sfRenderWindow_pollEvent(rpg->win->window, &rpg->event)) {
        if (rpg->event.type == sfEvtMouseMoved)
            update_mouse_pos(rpg);
        if (rpg->event.type == sfEvtClosed ||
            rpg->event.key.code == sfKeyEscape)
            sfRenderWindow_close(rpg->win->window);
        if (rpg->gamestate == GAME || rpg->gamestate == INVENTORY)
            manage_evt_inv(rpg->event, rpg);
        event_states(rpg);
    }
    if (rpg->gamestate == GAME)
        if (player_is_not_in_action(rpg) && player_is_alive(rpg) &&
            !is_stunned(rpg->ent[0]) && rpg->ent[0]->common->state != INTERACT)
            player_move(rpg);
}
