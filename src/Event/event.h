/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** event
*/
#pragma once

#include "rpg.h"

// Event
void event(rpg_t *rpg);

// Player move
void player_move(rpg_t *rpg);

// Player attack
void player_attack(rpg_t *rpg);
void event_player_attack(rpg_t *rpg);

// Quest event
void quest_event(rpg_t *rpg);
void accept_quest(rpg_t *rpg);
void refuse_quest(rpg_t *rpg);
void interact_with_entity(rpg_t *rpg, entity_t *entity);

// Text box event
void text_box_handling(rpg_t *rpg, all_quests_t *tmp, quest_t *quest);
void change_choice(rpg_t *rpg);
void choice_action(rpg_t *rpg);
void dialog_handling(rpg_t *rpg);

// Menu event
void menu_button_event(rpg_t *rpg, button_t *buttons);
void save_button_event(rpg_t *rpg, save_button_t *buttons);
void slct_button_event(rpg_t *rpg, select_button_t *buttons);

// Event map
void event_map(rpg_t *rpg);

// Event game
void event_game(rpg_t *rpg);
