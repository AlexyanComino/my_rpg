/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** menu
*/

#pragma once

#include "rpg.h"

// button
bool is_button_clicked(struct button_s *button, rpg_t *rpg);
bool is_button_hovered(struct button_s *button, rpg_t *rpg);
bool is_button_released(struct button_s *button, rpg_t *rpg);

// save_button
bool is_s_button_clicked(struct save_button_s *button, rpg_t *rpg);
bool is_s_button_hovered(struct save_button_s *button, rpg_t *rpg);
bool is_s_button_released(struct save_button_s *button, rpg_t *rpg);

// select_button
bool is_select_button_clicked(struct select_button_s *button, rpg_t *rpg);
bool is_select_button_hovered(struct select_button_s *button, rpg_t *rpg);
bool is_select_button_released(struct select_button_s *button, rpg_t *rpg);

// actions
void *get_action(char *txt);
void start(rpg_t *rpg);
void settings(rpg_t *rpg);
void quit(rpg_t *rpg);
void save_menu(rpg_t *rpg);
void back_to_menu(rpg_t *rpg);

// actions2
void selector(rpg_t *rpg);
void load_save1(rpg_t *rpg);
void load_save2(rpg_t *rpg);
void load_save3(rpg_t *rpg);
void change_fps(rpg_t *rpg);

// get_actions
void *get_action(char *txt);

// starts
void start_warrior(rpg_t *rpg);
void start_pawn(rpg_t *rpg);
void start_archer(rpg_t *rpg);
void start_torch(rpg_t *rpg);
void start_tnt(rpg_t *rpg);

// Actions3
void continue_game(rpg_t *rpg);
void reprendre_game(rpg_t *rpg);
void sauvegarder_game(rpg_t *rpg);
void change_volume(rpg_t *rpg);
