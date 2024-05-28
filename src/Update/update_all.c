/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_all
*/

#include "rpg.h"

void update(rpg_t *rpg)
{
    anim_transition(rpg);
    if (rpg->gamestate == LOADING)
        return update_loading(rpg);
    if (rpg->gamestate == MAIN_MENU || rpg->gamestate == SETTINGS ||
        rpg->gamestate == SAVE_MENU || rpg->gamestate == SELECTOR)
        return update_menus(rpg);
    if (rpg->gamestate == GAME)
        return update_game(rpg);
    if (rpg->gamestate == MAP)
        return update_map(rpg);
    if (rpg->gamestate == PAUSE)
        return update_pause_menu(rpg);
    if (rpg->gamestate == END)
        return update_end_menu(rpg);
    if (rpg->gamestate == CREDITS)
        return update_credits(rpg);
    if (rpg->gamestate == INVENTORY)
        rpg->inventory->player_status->player->anim(rpg,
            rpg->inventory->player_status->player);
    principal_music(rpg);
}
