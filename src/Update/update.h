/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update
*/
#pragma once

// Update_all
void update(rpg_t *rpg);

// Update loading
void update_loading(rpg_t *rpg);

// Update menus
void update_shadow_buttons(button_t *buttons);
void update_end_menu(rpg_t *rpg);
void update_menus(rpg_t *rpg);

// Update pause menu
void update_pause_menu(rpg_t *rpg);

// Move view menu
void move_view_menu(rpg_t *rpg);

// Update credits
void update_credits(rpg_t *rpg);

// Update victory
void update_victory(rpg_t *rpg);
