/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** displayAll
*/

#include "rpg.h"
#include "singleton.h"

static void display_transition(rpg_t *rpg)
{
    if (!rpg->transition->displayed)
        return;
    sfRenderWindow_drawSprite(rpg->win->window,
        rpg->transition->anim->sprite, NULL);
}

void display(rpg_t *rpg)
{
    sfRenderWindow_clear(rpg->win->window, sfBlack);
    if (rpg->gamestate == LOADING)
        display_loading(rpg);
    if (rpg->gamestate == MAIN_MENU)
        display_main_menu(rpg);
    if (rpg->gamestate == SAVE_MENU)
        display_save_menu(rpg);
    if (rpg->gamestate == SETTINGS)
        display_settings(rpg);
    if (rpg->gamestate == SELECTOR)
        display_selector(rpg);
    if (rpg->gamestate == GAME || rpg->gamestate == INVENTORY ||
        rpg->gamestate == MAP || rpg->gamestate == PAUSE)
        display_game(rpg);
    if (rpg->gamestate == END)
        display_end_menu(rpg);
    display_transition(rpg);
    sfRenderWindow_display(rpg->win->window);
}
