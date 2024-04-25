/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** menu
*/

#pragma once

#include "rpg.h"

// button
bool is_button_clicked(struct button_s *button, sfMouseButtonEvent *event);
bool is_button_hovered(struct button_s *button, sfMouseMoveEvent *event);
bool is_button_released(struct button_s *button, sfMouseButtonEvent *event);

// action
void start(rpg_t *rpg);
void settings(rpg_t *rpg);
void quit(rpg_t *rpg);
void save_menu(rpg_t *rpg);
void back_to_menu(rpg_t *rpg);

// menu_event
void menu_button_event(rpg_t *rpg, button_t *buttons);
