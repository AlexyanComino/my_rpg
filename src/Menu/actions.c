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
    sfSprite_setOrigin(rpg->inventory->player_status->s_hp,
        (sfVector2f){0, 0});
    sfSprite_setOrigin(rpg->inventory->player_status->s_attack,
        (sfVector2f){0, 0});
    sfSprite_setOrigin(rpg->inventory->player_status->s_def,
        (sfVector2f){0, 0});
    sfSprite_setOrigin(rpg->inventory->player_status->s_speed,
        (sfVector2f){0, 0});
    sfSprite_setOrigin(rpg->inventory->player_status->pp,
        (sfVector2f){0, 0});
    sfSprite_setPosition(rpg->transition->anim->sprite,
        get_player(rpg)->common->pos);
    sfSprite_setScale(rpg->transition->anim->sprite, (sfVector2f){2, 2});
}

void settings(rpg_t *rpg)
{
    rpg->win->view_pos = (sfVector2f){5331, 8353};
    sfRenderWindow_setView(rpg->win->window, rpg->win->view_menu);
    rpg->gamestate = SETTINGS;
    rpg->win->zoom = 2;
}

void quit(rpg_t *rpg)
{
    sfRenderWindow_close(rpg->win->window);
}

void back_to_menu(rpg_t *rpg)
{
    rpg->win->view_pos = (sfVector2f){5331, 8353};
    sfRenderWindow_setView(rpg->win->window, rpg->win->view_menu);
    rpg->gamestate = MAIN_MENU;
    rpg->win->zoom = 2;
}

void save_menu(rpg_t *rpg)
{
    rpg->gamestate = SAVE_MENU;
}
