/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** actions
*/

#include "rpg.h"

void start(rpg_t *rpg)
{
    rpg->gamestate = GAME;
    sfRenderWindow_setView(rpg->win->window, rpg->win->view);
    rpg->win->zoom = 1;
    sfSprite_setPosition(rpg->transition->anim->sprite,
        get_player(rpg)->common->pos);
    sfSprite_setScale(rpg->transition->anim->sprite, (sfVector2f){2, 2});
    setup_command_help_in_game(rpg);
}

void settings(rpg_t *rpg)
{
    sfRenderWindow_setView(rpg->win->window, rpg->win->view_menu);
    rpg->gamestate = SETTINGS;
    rpg->win->zoom = 2;
    setup_command_help_menu(rpg);
}

void quit(rpg_t *rpg)
{
    sfRenderWindow_close(rpg->win->window);
}

void back_to_menu(rpg_t *rpg)
{
    sfView_setCenter(rpg->win->view_menu, rpg->win->view_pos);
    sfRenderWindow_setView(rpg->win->window, rpg->win->view_menu);
    rpg->gamestate = MAIN_MENU;
    rpg->win->zoom = 2;
}

void save_menu(rpg_t *rpg)
{
    rpg->gamestate = SAVE_MENU;
    setup_command_help_menu(rpg);
}
