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
}

void settings(rpg_t *rpg)
{
    rpg->gamestate = SETTINGS;
}

void quit(rpg_t *rpg)
{
    sfRenderWindow_close(rpg->win->window);
}

void back_to_menu(rpg_t *rpg)
{
    rpg->gamestate = MAIN_MENU;
}

void save_menu(rpg_t *rpg)
{
    rpg->gamestate = SAVE_MENU;
}
