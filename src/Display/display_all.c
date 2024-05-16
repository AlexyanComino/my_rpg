/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** displayAll
*/

#include "rpg.h"
#include "singleton.h"

void display_all(rpg_t *rpg)
{
    sfRenderWindow_clear(rpg->win->window, sfBlack);
    if (rpg->gamestate == MAIN_MENU)
        display_main_menu(rpg);
    if (rpg->gamestate == SAVE_MENU)
        display_save_menu(rpg);
    if (rpg->gamestate == SETTINGS)
        display_settings(rpg);
    if (rpg->gamestate == GAME || rpg->gamestate == INVENTORY ||
        rpg->gamestate == MAP)
        display_game(rpg);
    sfRenderWindow_display(rpg->win->window);
}
