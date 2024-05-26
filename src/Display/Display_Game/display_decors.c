/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** display_decors
*/

#include "rpg.h"


void display_decors_ground(rpg_t *rpg, bool(*in_view)(rpg_t *, sfIntRect))
{
    if (sfKeyboard_isKeyPressed(sfKeyV))
        return;
    for (unsigned int i = 0; i < rpg->decors_size; i++) {
        if (!in_view(rpg, rpg->decors[i]->rect) ||
            rpg->decors[i]->type != GROUND)
            continue;
        sfRenderWindow_drawSprite(rpg->win->window,
            rpg->decors[i]->anim->sprite, NULL);
        if (rpg->modes->debug)
            sfRenderWindow_drawRectangleShape(rpg->win->window,
                rpg->decors[i]->shape, NULL);
    }
}

void display_decors_high(rpg_t *rpg, bool(*in_view)(rpg_t *, sfIntRect))
{
    if (sfKeyboard_isKeyPressed(sfKeyV))
        return;
    for (unsigned int i = 0; i < rpg->decors_size; i++) {
        if (!in_view(rpg, rpg->decors[i]->rect) ||
            rpg->decors[i]->type != HIGH)
            continue;
        sfRenderWindow_drawSprite(rpg->win->window,
            rpg->decors[i]->anim->sprite, NULL);
        if (rpg->modes->debug)
            sfRenderWindow_drawRectangleShape(rpg->win->window,
                rpg->decors[i]->shape, NULL);
    }
}
