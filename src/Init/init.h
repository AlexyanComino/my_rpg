/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init
*/
#pragma once

#include "rpg.h"

// InitRpg
sfVector2f *get_file_pos(unsigned int *size, char *filepath);
rpg_t *init_rpg(void);

// Init text box
text_box_t *init_text_box(void);

// Init threads
void *load_data(void *arg);
void *load_entities(void *arg);

// Init quests
void init_all_quests(rpg_t *rpg);

// Init dialog
dialog_t *init_dialog(char *dialog);

// Init decors
decor_anim_t **init_decors(unsigned int *size);

// Init chests
chest_t **init_chests(unsigned int *size);

// Init items tab
item_t **init_items_tab(unsigned int *size);

// Init sounds
sounds_t *init_sounds(void);

// Init inventory
void create_slot_inventory(rpg_t *rpg, int size);
void init_inventory(rpg_t *rpg, int size);

// save
void save(rpg_t *rpg, int nb);

// load
save_t *load(int nb);

// Init collisions
collision_t *init_collision(void);

// Init victory
vict_t *init_victory(void);

// Init credits
credits_t *init_credits(void);
