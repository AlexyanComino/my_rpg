/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** actions3
*/

#include "rpg.h"

void continue_game(rpg_t *rpg)
{
    entity_t *player = get_player(rpg);

    rpg->gamestate = GAME;
    player->common->state = IDLE;
    player->common->attributes->health =
        player->common->attributes->max_health;
}

void reprendre_game(rpg_t *rpg)
{
    rpg->gamestate = GAME;
    setup_command_help_in_game(rpg);
}

void sauvegarder_game(rpg_t *rpg)
{
    printf("Sauvegarde en cours...\n");
    save(rpg, rpg->save_index + 1);
    rpg = rpg;
}

void change_volume(rpg_t *rpg)
{
    rpg = rpg;
    printf("Volume changé\n");
}
