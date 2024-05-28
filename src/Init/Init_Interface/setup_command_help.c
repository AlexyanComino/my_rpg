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
    add_command_help(&interface->command_list, "Arbre de Compétences",
        interface->player_infos->font, 1);
    add_command_help(&interface->command_list, "Plus d'informations",
        interface->player_infos->font, 1);
    add_command_help(&interface->command_list, "Attaquer",
        interface->player_infos->font, 1);
    add_command_help(&interface->command_list, "Marcher",
        interface->player_infos->font, 1);
    add_command_help(&interface->command_list, "Inventaire",
        interface->player_infos->font, 1);
    add_command_help(&interface->command_list, "Interagir",
        interface->player_infos->font, 1);
    if (get_player(rpg)->type == PAWN) {
        add_command_help(&interface->command_list, "Étourdir",
            interface->player_infos->font, 1);
        add_command_help(&interface->command_list, "Émote",
            interface->player_infos->font, 1);
    }
    add_command_help(&interface->command_list, "Carte",
        interface->player_infos->font, 1);
    set_command_pos(interface->command_list, get_player(rpg)->common->pos, 1);
}

void setup_command_help_map(rpg_t *rpg)
{
    interface_t *interface = rpg->interface;

    delete_command_help(&interface->command_list);
    add_command_help(&interface->command_list, "Déplacement",
        interface->player_infos->font, 1);
    add_command_help(&interface->command_list, "Zoom +",
        interface->player_infos->font, 1);
    add_command_help(&interface->command_list, "Zoom -",
        interface->player_infos->font, 1);
    add_command_help(&interface->command_list, "Zoom",
        interface->player_infos->font, 1);
    set_command_pos(interface->command_list, get_player(rpg)->common->pos, 1);
    sfRenderWindow_setMouseCursorVisible(rpg->win->window, sfTrue);
}

void setup_command_help_pause(rpg_t *rpg)
{
    interface_t *interface = rpg->interface;

    delete_command_help(&interface->command_list);
    add_command_help(&interface->command_list, "Retour au jeu",
        interface->player_infos->font, 1);
    add_command_help(&interface->command_list, "Sélectionner",
        interface->player_infos->font, 1);
    set_command_pos(interface->command_list, get_player(rpg)->common->pos, 1);
    sfRenderWindow_setMouseCursorVisible(rpg->win->window, sfTrue);
}

void setup_command_help_menu(rpg_t *rpg)
{
    interface_t *interface = rpg->interface;

    delete_command_help(&interface->command_list);
    add_command_help(&interface->command_list, "Sélectionner",
        interface->player_infos->font, 2);
    set_command_pos(interface->command_list, rpg->win->view_pos, 2);
    sfRenderWindow_setMouseCursorVisible(rpg->win->window, sfTrue);
}

void setup_command_help_inventory(rpg_t *rpg)
{
    interface_t *interface = rpg->interface;

    delete_command_help(&interface->command_list);
    add_command_help(&interface->command_list, "Revenir au jeu",
        interface->player_infos->font, 1);
    add_command_help(&interface->command_list, "Supprimer",
        interface->player_infos->font, 1);
    add_command_help(&interface->command_list, "Sélectionner",
        interface->player_infos->font, 1);
    add_command_help(&interface->command_list, "Déplacer",
        interface->player_infos->font, 1);
    set_command_pos(interface->command_list, get_player(rpg)->common->pos, 1);
    sfRenderWindow_setMouseCursorVisible(rpg->win->window, sfTrue);
}
