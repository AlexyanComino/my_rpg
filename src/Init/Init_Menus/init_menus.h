/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_menus
*/

#pragma once

#include "rpg.h"


// InitMenu
menu_t *init_menu(rpg_t *rpg);
menu_t *init_settings(rpg_t *rpg);

// Init menu save
save_menu_t *init_save_menu(rpg_t *rpg);

// Init save menu 2
void get_entity_save(save_button_t *new, int type);
char **get_infos_save(int type);

// Init menu selector
select_menu_t *init_select_menu(rpg_t *rpg);
sfText *create_text(sfFont *font, char *str, int size, sfVector2f pos);

// Init end menu
end_menu_t *init_end_menu(rpg_t *rpg);

// Init menu selector2
void get_entity(select_button_t *new);
void get_attributes_select(char *txt, select_button_t *new);

// Add button menu
void add_button(button_t **buttons, sfVector2f pos, char *txt);

// Init loading
anim_text_t *init_anim_text(sfText *text, float scale_bonus,
    float transition_speed, sfText *shadow);
loading_t *init_loading(void);
