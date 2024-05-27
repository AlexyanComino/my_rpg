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
void player_move_event(rpg_t *rpg);

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
void update_text_cities_size(rpg_t *rpg, float zoom);
void event_map(rpg_t *rpg);

// Event game
void event_game(rpg_t *rpg);

// Event chests
anim_sprite_t *init_anim_sprite(char *texture_path, float scale_bonus,
    float transition_speed, float init_scale);
void event_chests(rpg_t *rpg, sfKeyCode key);

// Description handling
char *description_handling(char *description);

// Event loading
void event_loading(rpg_t *rpg);

// Init menu pause
pause_menu_t *init_pause_menu(void);
void set_pos_buttons_pause_menu(rpg_t *rpg);
