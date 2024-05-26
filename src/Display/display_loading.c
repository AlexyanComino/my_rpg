/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** display_loading
*/

#include "rpg.h"

void display_anim_text(rpg_t *rpg, anim_text_t *anim_text)
{
    if (anim_text->has_shadow)
        sfRenderWindow_drawText(rpg->win->window, anim_text->shadow, NULL);
    sfRenderWindow_drawText(rpg->win->window, anim_text->text, NULL);
}

void display_loading(rpg_t *rpg)
{
    if (rpg->loading->is_loaded != 0)
        sfRenderWindow_drawText(rpg->win->window,
            rpg->loading->cont->anim_text->text, NULL);
    if (rpg->loading->is_loaded != 2)
        sfRenderWindow_drawSprite(rpg->win->window, rpg->loading->load->sprite,
        NULL);
    display_anim_text(rpg, rpg->loading->title1);
    display_anim_text(rpg, rpg->loading->title2);
}
