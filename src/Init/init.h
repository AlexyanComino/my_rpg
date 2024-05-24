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

// InitMenu
menu_t *init_menu(rpg_t *rpg);
menu_t *init_settings(rpg_t *rpg);
save_menu_t *init_save_menu(rpg_t *rpg);
char **get_infos_save(int type);
void get_entity_save(save_button_t *new, int type);
select_menu_t *init_select_menu(rpg_t *rpg);
select_button_t *add_select_button(
    select_button_t *buttons, sfVector2f pos, char *txt, char **tab);
void create_buttons_select(rpg_t *rpg, select_menu_t *menu);
char **get_infos(char *txt);
sfText *create_text(sfFont *font, char *str, int size, sfVector2f pos);

// Init interface
interface_t *init_interface(void);

// Init items pawn
item_pawn_t *init_item_pawn(item_pawn_type_t item_type);

// Init damage texts
damage_text_t *init_damage_text(rpg_t *rpg, entity_t *entity,
    int attack, damage_text_state_t state);

// Init text box
text_box_t *init_text_box(void);

// Init threads
void *load_data(void *arg);
void *load_entities(void *arg);

// Init quests
void init_all_quests(rpg_t *rpg);

// Init dialog
dialog_t *init_dialog(char *dialog);

// Init minimap
minimap_t *init_minimap(unsigned int width, unsigned int height);

// Init decors
decor_anim_t **init_decors(unsigned int *size);

// Init chests
chest_t **init_chests(unsigned int *size);

// Init items tab
item_t **init_items_tab(unsigned int *size);

// Init sounds
sounds_t *init_sounds(void);
=======
void init_inventory(rpg_t *rpg, int size);

// save
void save(rpg_t *rpg, int nb);

// load
save_t *load(int nb);
