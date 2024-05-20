/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** display_entities
*/
#pragma once

// Display common
void display_round_rectangle(sfRenderWindow *window, round_rectangle_t *rect);
void display_common(rpg_t *rpg, entity_t *entity);

// Display warriors
void display_warrior(void *vrpg, entity_t *entity);

// Display pawns
void display_pawn(void *vrpg, entity_t *entity);

// Display torch
void display_torch(void *vrpg, entity_t *entity);

// Display tnt
void display_tnt(void *vrpg, entity_t *entity);

// Display archer
void display_archer(void *vrpg, entity_t *entity);

// Display entities
void display_entities(rpg_t *rpg);
