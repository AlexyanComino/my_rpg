/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** lib
*/
#pragma once

#include "rpg.h"

// Tools
float get_distance_between_pos(sfVector2f center1, sfVector2f center2);
void update_clock_seconds(my_clock_t *myclock);

// My_str_to_word_array
char **split_string(char *str, char *delim);

// View tools
bool intrect_is_in_view(rpg_t *rpg, sfIntRect hitbox);
bool entity_is_in_view(rpg_t *rpg, entity_t *entity);

// file_to_array
char **file_to_array(char *path);
void free_array(char **array);
