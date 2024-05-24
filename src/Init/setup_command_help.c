/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** setup_command_help
*/

#include "rpg.h"


void setup_command_help_in_game(rpg_t *rpg)
{
    interface_t *interface = rpg->interface;

    delete_command_help(&interface->command_list);
    add_command_help(&interface->command_list, "Attaquer",
        interface->player_infos->font);
    add_command_help(&interface->command_list, "Marcher",
        interface->player_infos->font);
    add_command_help(&interface->command_list, "Inventaire",
        interface->player_infos->font);
    add_command_help(&interface->command_list, "Interagir",
        interface->player_infos->font);
    add_command_help(&interface->command_list, "Carte",
        interface->player_infos->font);
    set_command_pos(interface->command_list, get_player(rpg)->common->pos, 1);
}

void setup_command_help_map(rpg_t *rpg)
{
    interface_t *interface = rpg->interface;

    delete_command_help(&interface->command_list);
    add_command_help(&interface->command_list, "Deplacement",
        interface->player_infos->font);
    add_command_help(&interface->command_list, "Zoom +",
        interface->player_infos->font);
    add_command_help(&interface->command_list, "Zoom -",
        interface->player_infos->font);
    set_command_pos(interface->command_list, get_player(rpg)->common->pos, 1);
}

void setup_command_help_pause(rpg_t *rpg)
{
    interface_t *interface = rpg->interface;

    delete_command_help(&interface->command_list);
    add_command_help(&interface->command_list, "Retour au jeu",
        interface->player_infos->font);
    add_command_help(&interface->command_list, "Selectionner",
        interface->player_infos->font);
    set_command_pos(interface->command_list, get_player(rpg)->common->pos, 1);
}
