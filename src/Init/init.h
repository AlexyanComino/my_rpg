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

// Init menu selector
select_menu_t *init_select_menu(rpg_t *rpg);
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

// Init inventory
int init_inventory(rpg_t *rpg, int size);

// Init loading
anim_text_t *init_anim_text(sfText *text, float scale_bonus,
    float transition_speed, sfText *shadow);
loading_t *init_loading(void);

// Init transition
void launch_transition(rpg_t *rpg, void (*callback)(rpg_t *rpg));
transition_t *init_transition(void);

// Init end menu
end_menu_t *init_end_menu(rpg_t *rpg);

// Command help
void add_command_help(command_list_t **command_list, char *action_str,
    sfFont *font);
void delete_command_help(command_list_t **command_list);
void set_command_pos(command_list_t *command_list, sfVector2f pos,
    float zoom);

// Setup command help
void setup_command_help_in_game(rpg_t *rpg);
void setup_command_help_map(rpg_t *rpg);
void setup_command_help_pause(rpg_t *rpg);

// Init menu selector2
void get_entity(select_button_t *new);
void get_attributes_select(char *txt, select_button_t *new, char **tab);

// Add button menu
void add_button(button_t **buttons, sfVector2f pos, char *txt);
