/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** music
*/

#include "rpg.h"

void play_music(sfMusic *music, int volume)
{
    sfMusic_stop(music);
    sfMusic_play(music);
    sfMusic_setVolume(music, volume);
    sfMusic_setLoop(music, sfFalse);
}

void touch(entity_t *entity, rpg_t *rpg)
{
    if (entity->type == WARRIOR)
        play_music(rpg->sounds->attack_sword, 30 * rpg->volume);
    if (entity->type == PAWN)
        play_music(rpg->sounds->attack_sword, 30 * rpg->volume);
    if (entity->type == TORCH)
        play_music(rpg->sounds->attack_fire, 85 * rpg->volume);
    if (entity->type == TNT)
        play_music(rpg->sounds->explosion, 100 * rpg->volume);
}

void which_entities(rpg_t *rpg, entity_t *entity)
{
    if (entity->type == WARRIOR)
        play_music(rpg->sounds->sword, 65 * rpg->volume);
    if (entity->type == PAWN)
        play_music(rpg->sounds->sword, 65 * rpg->volume);
    if (entity->type == TORCH)
        play_music(rpg->sounds->attack_fire, 85 * rpg->volume);
    if (entity->type == TNT)
        play_music(rpg->sounds->explosion, 100 * rpg->volume);
    if (entity->type == ARCHER)
        play_music(rpg->sounds->arrow, 100 * rpg->volume);
}

void play_music_loop(sfMusic *music, int volume)
{
    sfMusic_stop(music);
    sfMusic_play(music);
    sfMusic_setVolume(music, volume);
    sfMusic_setLoop(music, sfTrue);
}
