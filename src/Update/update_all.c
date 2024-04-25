/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_all
*/

#include "rpg.h"

void update_all(rpg_t *rpg)
{
    if (rpg->gamestate != GAME &&
        rpg->gamestate != PAUSE && rpg->gamestate != END)
        update_background(rpg);
    if (rpg->gamestate == GAME) {
        update_warriors(rpg);
        update_quests(rpg);
    }
}
