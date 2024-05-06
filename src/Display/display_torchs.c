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

void display_torch(void *vrpg, entity_t *entity)
{
    rpg_t *rpg = (rpg_t *)vrpg;

    if (entity->common->state == RIEN)
        return;
    if (entity->common->state == DEAD)
        sfRenderWindow_drawSprite(rpg->win->window,
        entity->common->death->anim->sprite, NULL);
    else
        display_alive_torch(rpg, entity);
}
