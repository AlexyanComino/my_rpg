/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** displayAll
*/

#include "rpg.h"

static void display_alive_warrior(rpg_t *rpg, warrior_t *warrior)
{
    sfRenderWindow_drawSprite(rpg->win->window, warrior->sprite, NULL);
    if (rpg->debug) {
        sfRenderWindow_drawRectangleShape(rpg->win->window,
            warrior->rect_hitbox, NULL);
        sfRenderWindow_drawRectangleShape(rpg->win->window,
            warrior->rect_hitbox_attack, NULL);
    }
}

static void display_warrior(rpg_t *rpg, warrior_t *warrior)
{
    if (warrior->state == DEAD)
        sfRenderWindow_drawSprite(rpg->win->window, warrior->sprite_dead,
            NULL);
    else
        display_alive_warrior(rpg, warrior);
}

static void display_warriors(rpg_t *rpg)
{
    lwarrior_t *tmp = rpg->lwarrior;

    while (tmp) {
        if (tmp->warrior->state != RIEN)
            display_warrior(rpg, tmp->warrior);
        tmp = tmp->next;
    }
}

void display_all(rpg_t *rpg)
{
    sfRenderWindow_clear(rpg->win->window, sfBlack);
    display_warriors(rpg);
    sfRenderWindow_display(rpg->win->window);
}
