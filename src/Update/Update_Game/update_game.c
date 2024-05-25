/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_game
*/

#include "rpg.h"

void update_game(rpg_t *rpg)
{
    update_game_interface(rpg);
    update_chests(rpg);
    update_entities(rpg);
    update_quest_header(rpg);
    update_quests(rpg);
    update_decors_anim(rpg, intrect_is_in_view);
}
