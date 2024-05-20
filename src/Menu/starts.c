/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** starts
*/

#include "rpg.h"

static void add_player(rpg_t *rpg, char **infos)
{
    rpg->ent[rpg->ent_size] = init_entity(infos);
    rpg->ent[rpg->ent_size]->common->faction = BLUE_TEAM;
    rpg->ent[rpg->ent_size]->common->faction_origin = BLUE_TEAM;
    rpg->player_index = rpg->ent_size;
    rpg->inventory->player_status->player = init_entity(infos);
    if (rpg->inventory->player_status->player->common->x == LEFT)
        rpg->inventory->player_status->player->common->x = RIGHT;
    sfSprite_setScale(rpg->inventory->player_status->player->common->
        anim->sprite, (sfVector2f){1.7, 1.7});
    update_interface_pos(rpg, rpg->ent[rpg->ent_size],
        rpg->ent[rpg->ent_size]->common->pos);
    rpg->ent_size++;
}

void start_warrior(rpg_t *rpg)
{
    char **tab = file_to_array(".entities.csv");
    char **infos = split_string(tab[0], ";");

    pthread_join(rpg->thread2, NULL);
    if (rpg->shared_data2->loaded) {
        rpg->ent = rpg->shared_data2->entities;
        rpg->ent_size = rpg->shared_data2->nb_entities;
    }
    add_player(rpg, infos);
    start(rpg);
    free_array(infos);
    free_array(tab);
}

void start_pawn(rpg_t *rpg)
{
    char **tab = file_to_array(".entities.csv");
    char **infos = split_string(tab[1], ";");

    pthread_join(rpg->thread2, NULL);
    if (rpg->shared_data2->loaded) {
        rpg->ent = rpg->shared_data2->entities;
        rpg->ent_size = rpg->shared_data2->nb_entities;
    }
    add_player(rpg, infos);
    start(rpg);
    free_array(infos);
    free_array(tab);
}

void start_torch(rpg_t *rpg)
{
    char **tab = file_to_array(".entities.csv");
    char **infos = split_string(tab[2], ";");

    pthread_join(rpg->thread2, NULL);
    if (rpg->shared_data2->loaded) {
        rpg->ent = rpg->shared_data2->entities;
        rpg->ent_size = rpg->shared_data2->nb_entities;
    }
    add_player(rpg, infos);
    start(rpg);
    free_array(infos);
    free_array(tab);
}

void start_tnt(rpg_t *rpg)
{
    char **tab = file_to_array(".entities.csv");
    char **infos = split_string(tab[3], ";");

    pthread_join(rpg->thread2, NULL);
    if (rpg->shared_data2->loaded) {
        rpg->ent = rpg->shared_data2->entities;
        rpg->ent_size = rpg->shared_data2->nb_entities;
    }
    add_player(rpg, infos);
    start(rpg);
    free_array(infos);
    free_array(tab);
}

void start_archer(rpg_t *rpg)
{
    char **tab = file_to_array(".entities.csv");
    char **infos = split_string(tab[4], ";");

    pthread_join(rpg->thread2, NULL);
    if (rpg->shared_data2->loaded) {
        rpg->ent = rpg->shared_data2->entities;
        rpg->ent_size = rpg->shared_data2->nb_entities;
    }
    add_player(rpg, infos);
    start(rpg);
    free_array(infos);
    free_array(tab);
}
