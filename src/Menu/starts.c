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
    rpg->inventory->player_status =
        init_player_status(infos, rpg->ent[rpg->ent_size]->common->attributes);
    create_slot_inventory(rpg, rpg->inventory->size);
    set_string_to_text(rpg->interface->player_infos->player_text,
        rpg->ent[rpg->ent_size]->common->name);
    update_interface_pos(rpg, rpg->ent[rpg->ent_size],
        rpg->ent[rpg->ent_size]->common->pos);
    rpg->ent_size++;
}

static void check_if_entity_has_quest(rpg_t *rpg, int i,
    char **quests_names, int len)
{
    for (int j = 0; j < len; j++) {
        if (rpg->ent[i]->common->grade_type == SOLDAT &&
            !strcmp(rpg->ent[i]->common->name, quests_names[j])) {
            rpg->ent[i]->common->grade_type = SOLDAT_QUEST;
            rpg->ent[i]->common->grade_icon =
                init_anim_sprite("assets/Entities/quest_icon.png",
                    0.07, 0.002, 0.25);
            return;
        }
    }
}

static void add_ent_quest_icons(rpg_t *rpg)
{
    char **tab = file_to_array(".quests.csv");
    char **infos = NULL;
    int len = tab_len(tab);
    char **quests_names = malloc(sizeof(char *) * (len + 1));

    for (int i = 0; tab[i]; i++) {
        infos = split_string(tab[i], ";");
        quests_names[i] = strdup(infos[0]);
        free_array(infos);
    }
    quests_names[len] = NULL;
    for (unsigned int i = 0; i < rpg->ent_size; i++) {
        check_if_entity_has_quest(rpg, i, quests_names, len);
    }
    free_array(quests_names);
    free_array(tab);
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
    add_ent_quest_icons(rpg);
    add_player(rpg, infos);
    launch_transition(rpg, &start);
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
    add_ent_quest_icons(rpg);
    add_player(rpg, infos);
    launch_transition(rpg, &start);
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
    add_ent_quest_icons(rpg);
    add_player(rpg, infos);
    launch_transition(rpg, &start);
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
    add_ent_quest_icons(rpg);
    add_player(rpg, infos);
    launch_transition(rpg, &start);
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
    add_ent_quest_icons(rpg);
    add_player(rpg, infos);
    launch_transition(rpg, &start);
    free_array(infos);
    free_array(tab);
}
