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
void accept_quest(rpg_t *rpg, entity_t *entity);
void refuse_quest(rpg_t *rpg);

// Text box event
void text_box_handling(rpg_t *rpg, all_quests_t *tmp);
void change_choice(rpg_t *rpg);
void choice_action(rpg_t *rpg);
void dialog_handling(rpg_t *rpg);

// Menu event
void menu_button_event(rpg_t *rpg, button_t *buttons);
