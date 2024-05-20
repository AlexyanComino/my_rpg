/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** display_decors
*/

#include "rpg.h"


void display_decors_ground(rpg_t *rpg)
{
    if (sfKeyboard_isKeyPressed(sfKeyV))
        return;
    for (unsigned int i = 0; i < rpg->decors_size; i++) {
        if (!intrect_is_in_view_menu(rpg, rpg->decors[i]->rect) ||
            rpg->decors[i]->type != GROUND)
            continue;
        sfRenderWindow_drawSprite(rpg->win->window,
            rpg->decors[i]->anim->sprite, NULL);
        if (rpg->debug)
            sfRenderWindow_drawRectangleShape(rpg->win->window,
                rpg->decors[i]->shape, NULL);
    }
}

void display_decors_high(rpg_t *rpg)
{
    if (sfKeyboard_isKeyPressed(sfKeyV))
        return;
    for (unsigned int i = 0; i < rpg->decors_size; i++) {
        if (!intrect_is_in_view_menu(rpg, rpg->decors[i]->rect) ||
            rpg->decors[i]->type != HIGH)
            continue;
        sfRenderWindow_drawSprite(rpg->win->window,
            rpg->decors[i]->anim->sprite, NULL);
        if (rpg->debug)
            sfRenderWindow_drawRectangleShape(rpg->win->window,
                rpg->decors[i]->shape, NULL);
    }
}
