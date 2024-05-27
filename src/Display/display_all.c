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

static void display_credits(rpg_t *rpg)
{
    text_list_t *tmp = rpg->credits->texts;

    if (sfRenderWindow_getView(rpg->win->window) != rpg->win->view)
        sfRenderWindow_setView(rpg->win->window, rpg->win->view);
    while (tmp) {
        sfRenderWindow_drawText(rpg->win->window, tmp->text, NULL);
        tmp = tmp->next;
    }
}

static void display2(rpg_t *rpg)
{
    if (rpg->gamestate == CREDITS)
        display_credits(rpg);
    draw_skill_tree(rpg);
    if (rpg->gamestate == END)
        display_end_menu(rpg);
    display_transition(rpg);
}

void display(rpg_t *rpg)
{
    sfRenderWindow_clear(rpg->win->window, (rpg->gamestate == CREDITS) ?
        sfWhite : sfBlack);
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
    display2(rpg);
    sfRenderWindow_display(rpg->win->window);
}
