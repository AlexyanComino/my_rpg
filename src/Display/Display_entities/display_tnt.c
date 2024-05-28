/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** display_tnt
*/

#include "rpg.h"

static void display_alive_tnt(rpg_t *rpg, entity_t *entity)
{
    display_common(rpg, entity);
    if (is_player(rpg, entity))
        sfRenderWindow_drawSprite(rpg->win->window,
            entity->spe->tnt->explo->cible, NULL);
    if (entity->spe->tnt->is_launched) {
        sfRenderWindow_drawSprite(rpg->win->window,
            entity->spe->tnt->dyna->anim->sprite, NULL);
    }
    if (entity->spe->tnt->is_exploded) {
        sfRenderWindow_drawSprite(rpg->win->window,
            entity->spe->tnt->explo->anim->sprite, NULL);
    }
    if (rpg->modes->debug) {
        sfRenderWindow_drawConvexShape(rpg->win->window,
            entity->spe->tnt->curve->curve_shape, NULL);
        sfRenderWindow_drawCircleShape(rpg->win->window,
            entity->spe->tnt->explo->boom_circle, NULL);
    }
}

void display_tnt(rpg_t *rpg, entity_t *entity)
{
    if (entity->common->state == RIEN)
        return;
    if (entity->common->state == DEAD) {
        sfRenderWindow_drawSprite(rpg->win->window,
        entity->common->death->anim->sprite, NULL);
        if (entity->common->grade_type == SOLDAT_QUEST)
            sfRenderWindow_drawSprite(rpg->win->window,
            entity->common->grade_icon->sprite, NULL);
    } else
        display_alive_tnt(rpg, entity);
}
