/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** event
*/

#include "rpg.h"

void event(rpg_t *rpg)
{
    sfTime elapsed_time = sfClock_getElapsedTime(rpg->win->clock);
    float dt = sfTime_asSeconds(elapsed_time);

    sfClock_restart(rpg->win->clock);
    while (sfRenderWindow_pollEvent(rpg->win->window, &rpg->event)) {
        if (rpg->event.type == sfEvtClosed)
            sfRenderWindow_close(rpg->win->window);
        event_player_attack(rpg);
    }
    if (get_player_state(rpg) != ATTACK)
        player_move(rpg, dt);
}
