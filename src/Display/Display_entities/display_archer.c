/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** display_archer
*/

#include "rpg.h"

static void display_arrows(rpg_t *rpg, entity_t *entity)
{
    arrows_t *tmp = entity->spe->archer->arrows;

    while (tmp) {
        sfRenderWindow_drawSprite(rpg->win->window,
        tmp->anim->sprite, NULL);
        if (rpg->debug)
            sfRenderWindow_drawPrimitives(rpg->win->window,
            tmp->vertices, 2, sfLines, NULL);
        tmp = tmp->next;
    }
}

static void display_alive_archer(rpg_t *rpg, entity_t *entity)
{
    display_common(rpg, entity);
    display_arrows(rpg, entity);
}

void display_archer(void *vrpg, entity_t *entity)
{
    rpg_t *rpg = (rpg_t *)vrpg;

    if (entity->common->state == RIEN)
        return;
    if (entity->common->state == DEAD)
        sfRenderWindow_drawSprite(rpg->win->window,
        entity->common->death->anim->sprite, NULL);
    else
        display_alive_archer(rpg, entity);
}
