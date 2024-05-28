/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** display_torchs
*/

#include "rpg.h"

static void display_alive_torch(rpg_t *rpg, entity_t *entity)
{
    display_common(rpg, entity);
}

void display_torch(rpg_t *rpg, entity_t *entity)
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
        display_alive_torch(rpg, entity);
}
