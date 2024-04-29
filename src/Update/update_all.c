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
        //update_game_interface(rpg);
        sfView_setCenter(rpg->win->view, rpg->lwarrior->warrior->pos);
        (*view_pos()) = sfView_getCenter(rpg->win->view);
        sfRenderWindow_setView(rpg->win->window, rpg->win->view);
        update_warriors(rpg);
        update_quest_header(rpg);
        update_quests(rpg);
    }
    if (rpg->gamestate == INVENTORY)
        anim_warrior(rpg, (*inventory())->player_status->player);
}
