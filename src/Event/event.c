/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** event
*/

#include "rpg.h"

void event_player_attack(rpg_t *rpg)
{
    entity_t *player = rpg->ent[0];

    if (rpg->event.type == sfEvtKeyPressed) {
        if (rpg->event.key.code == sfKeySpace &&
            is_attacking(player) && player->type == WARRIOR) {
            player->spe->warrior->max_line_attack = 1;
        }
        if (rpg->event.key.code == sfKeySpace &&
            not_attacking(player) && player->type == WARRIOR) {
            player->common->state = ST_ATT;
            player->spe->warrior->line_attack = 0;
            player->spe->warrior->max_line_attack = 0;
            player->common->anim->rect.left = 0;
            update_warrior_attack_rect(player);
            sfClock_restart(player->common->anim->myclock->clock);
        }
        if (rpg->event.key.code == sfKeyP)
            printf("Player pos: %f, %f\n", player->common->pos.x,
                player->common->pos.y);
    }
}

void event_states(rpg_t *rpg)
{
    if (rpg->gamestate == MAIN_MENU)
        menu_button_event(rpg, rpg->main_menu->buttons);
    if (rpg->gamestate == SETTINGS)
        menu_button_event(rpg, rpg->settings->buttons);
    if (rpg->gamestate == SAVE_MENU)
        menu_button_event(rpg, rpg->save_menu->buttons);
    if (rpg->gamestate == GAME) {
        event_player_attack(rpg);
        quest_event(rpg);
    }
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
        if (rpg->gamestate == GAME || rpg->gamestate == INVENTORY)
            manage_evt_inv(rpg->event, rpg);
        event_states(rpg);
    }
    if (rpg->gamestate == GAME)
        if (player_is_not_attacking(rpg) && player_is_alive(rpg))
            player_move(rpg);
}
