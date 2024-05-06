/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init
*/
#pragma once

#include "rpg.h"

// InitRpg
rpg_t *init_rpg(void);

// InitMenu
menu_t *init_menu(void);
menu_t *init_settings(void);
menu_t *init_save_menu(void);
sfText *create_text(sfFont *font, char *str, int size, sfVector2f pos);

// Init interface
interface_t *init_interface(void);

// Init items
item_t *init_item(item_type_t item_type);
