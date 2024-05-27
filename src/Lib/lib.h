/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** lib
*/
#pragma once

#include "rpg.h"

// Tools
float get_distance(sfVector2f center1, sfVector2f center2);
void update_clock_seconds(my_clock_t *myclock);
int tab_len(char **tab);
void set_string_to_text(sfText *text, const char *string);
void setup_end_header(rpg_t *rpg, char *string);

// My_str_to_word_array
char **split_string(char *str, char *delim);

// View tools
bool intrect_is_in_view_menu(rpg_t *rpg, sfIntRect hitbox);
bool intrect_is_in_view(rpg_t *rpg, sfIntRect hitbox);
bool intrect_is_in_real_view(rpg_t *rpg, sfIntRect hitbox);
bool entity_is_in_view(rpg_t *rpg, entity_t *entity);

// file_to_array
char **file_to_array(char *path);
void free_array(char **array);

// Item tools
item_t *get_item_from_name(rpg_t *rpg, char *name, enum item_type type);
void add_item_from_type(rpg_t *rpg, char *name, enum item_type type);

// my_strcatdup
char *my_strcatdup(char *str1, char c);
char *my_strcatdup2(char *str1, char *str2);
