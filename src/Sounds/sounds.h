/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** sounds.h
*/

#pragma once

#include "rpg.h"

void play_music(sfMusic *music, int volume);
void which_entities(rpg_t *rpg, entity_t *entity);
void touch(entity_t *entity, rpg_t *rpg);
void play_music_loop(sfMusic *music, int volume);
void principal_music(rpg_t *rpg);
void attack_music(rpg_t *rpg);
