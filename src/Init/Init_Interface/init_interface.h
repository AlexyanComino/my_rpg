/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_interface
*/

#pragma once

#include "rpg.h"

// Init interface
interface_t *init_interface(void);

// Init minimap
minimap_t *init_minimap(unsigned int width, unsigned int height);

// Init transition
void launch_transition(rpg_t *rpg, void (*callback)(rpg_t *rpg));
transition_t *init_transition(void);

// Command help
void add_command_help(command_list_t **command_list, char *action_str,
    sfFont *font, float zoom);
void delete_command_help(command_list_t **command_list);
void set_command_pos(command_list_t *command_list, sfVector2f pos,
    float zoom);

// Setup command help
void setup_command_help_in_game(rpg_t *rpg);
void setup_command_help_map(rpg_t *rpg);
void setup_command_help_pause(rpg_t *rpg);
void setup_command_help_menu(rpg_t *rpg);
void setup_command_help_inventory(rpg_t *rpg);
