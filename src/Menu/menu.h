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
void quit(rpg_t *rpg);
