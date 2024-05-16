/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_all
*/

#include "rpg.h"


void update_all(rpg_t *rpg)
{
    if (rpg->gamestate == MAIN_MENU || rpg->gamestate == PAUSE ||
        rpg->gamestate == SETTINGS || rpg->gamestate == SAVE_MENU)
        update_background(rpg);
    if (rpg->gamestate == GAME) {
        update_game_interface(rpg);
        update_entities(rpg);
        update_quest_header(rpg);
        update_quests(rpg);
    }
    if (rpg->gamestate == INVENTORY)
        anim_warrior(rpg, (*inventory())->player_status->player);
}
