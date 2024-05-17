/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** starts
*/

#include "rpg.h"

void start_warrior(rpg_t *rpg)
{
    char **tab = file_to_array(".entities.csv");
    char **infos = split_string(tab[0], ";");

    
    rpg->ent[rpg->ent_size] = init_entity(infos);
    rpg->ent[rpg->ent_size]->common->faction = BLUE_TEAM;
    rpg->ent[rpg->ent_size]->common->faction_origin = BLUE_TEAM;
    rpg->player_index = rpg->ent_size;
    update_interface_pos(rpg, rpg->ent[rpg->ent_size],
        rpg->ent[rpg->ent_size]->common->pos);
    rpg->ent_size++;
    start(rpg);
    free_array(infos);
    free_array(tab);
}

void start_pawn(rpg_t *rpg)
{
    char **tab = file_to_array(".entities.csv");
    char **infos = split_string(tab[1], ";");

    rpg->ent[rpg->ent_size] = init_entity(infos);
    rpg->ent[rpg->ent_size]->common->faction = BLUE_TEAM;
    rpg->ent[rpg->ent_size]->common->faction_origin = BLUE_TEAM;
    rpg->player_index = rpg->ent_size;
    update_interface_pos(rpg, rpg->ent[rpg->ent_size],
        rpg->ent[rpg->ent_size]->common->pos);
    rpg->ent_size++;
    start(rpg);
    free_array(infos);
    free_array(tab);
}

void start_torch(rpg_t *rpg)
{
    char **tab = file_to_array(".entities.csv");
    char **infos = split_string(tab[2], ";");

    rpg->ent[rpg->ent_size] = init_entity(infos);
    rpg->ent[rpg->ent_size]->common->faction = BLUE_TEAM;
    rpg->ent[rpg->ent_size]->common->faction_origin = BLUE_TEAM;
    rpg->player_index = rpg->ent_size;
    update_interface_pos(rpg, rpg->ent[rpg->ent_size],
        rpg->ent[rpg->ent_size]->common->pos);
    rpg->ent_size++;
    start(rpg);
    free_array(infos);
    free_array(tab);
}

void start_tnt(rpg_t *rpg)
{
    char **tab = file_to_array(".entities.csv");
    char **infos = split_string(tab[3], ";");

    rpg->ent[rpg->ent_size] = init_entity(infos);
    rpg->ent[rpg->ent_size]->common->faction = BLUE_TEAM;
    rpg->ent[rpg->ent_size]->common->faction_origin = BLUE_TEAM;
    rpg->player_index = rpg->ent_size;
    update_interface_pos(rpg, rpg->ent[rpg->ent_size],
        rpg->ent[rpg->ent_size]->common->pos);
    rpg->ent_size++;
    start(rpg);
    free_array(infos);
    free_array(tab);
}

void start_archer(rpg_t *rpg)
{
    char **tab = file_to_array(".entities.csv");
    char **infos = split_string(tab[4], ";");

    rpg->ent[rpg->ent_size] = init_entity(infos);
    rpg->ent[rpg->ent_size]->common->faction = BLUE_TEAM;
    rpg->ent[rpg->ent_size]->common->faction_origin = BLUE_TEAM;
    rpg->player_index = rpg->ent_size;
    update_interface_pos(rpg, rpg->ent[rpg->ent_size],
        rpg->ent[rpg->ent_size]->common->pos);
    rpg->ent_size++;
    start(rpg);
    free_array(infos);
    free_array(tab);
}
