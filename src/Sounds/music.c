/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** music
*/

#include "rpg.h"

void principal_music(rpg_t *rpg)
{
    static int i = 0;

    update_clock_seconds(rpg->sounds->myclock);
    if (rpg->sounds->myclock->seconds > 10.5 && i == 0) {
        sfMusic_stop(rpg->sounds->intro);
        sfMusic_play(rpg->sounds->loop);
        sfMusic_setVolume(rpg->sounds->loop, 50);
        sfMusic_setLoop(rpg->sounds->loop, sfTrue);
        i++;
    }
}

void attack_music(rpg_t *rpg)
{
    static int prev_in_base = 0;

    if (rpg->interface->restricted->in_base && !prev_in_base) {
        prev_in_base = 1;
        sfMusic_stop(rpg->sounds->loop);
        play_music(rpg->sounds->attack, 65 * rpg->volume);
    } else if (!rpg->interface->restricted->in_base && prev_in_base) {
        prev_in_base = 0;
        sfMusic_stop(rpg->sounds->attack);
        play_music_loop(rpg->sounds->loop, 50 * rpg->volume);
    }
}
