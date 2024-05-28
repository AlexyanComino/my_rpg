/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** display_archer
*/

#include "rpg.h"

static void display_pattern_pos_shapes(rpg_t *rpg, entity_t *entity)
{
    int i = 0;

    while (entity->spe->archer->base->pattern_pos[i].x != -1 &&
        entity->spe->archer->base->pattern_pos[i].y != -1) {
        sfRenderWindow_drawCircleShape(rpg->win->window,
            entity->spe->archer->base->pattern_pos_shapes[i], NULL);
        i++;
    }
}

static void display_debug_archer(rpg_t *rpg, entity_t *entity)
{
    if (entity_has_base(entity)) {
        sfRenderWindow_drawRectangleShape(rpg->win->window,
        entity->spe->archer->base->shape, NULL);
        display_pattern_pos_shapes(rpg, entity);
    }
}

static void display_arrows(rpg_t *rpg, entity_t *entity)
{
    arrows_t *tmp = entity->spe->archer->arrows;

    while (tmp) {
        sfRenderWindow_drawSprite(rpg->win->window,
        tmp->anim->sprite, NULL);
        if (rpg->modes->debug)
            sfRenderWindow_drawPrimitives(rpg->win->window,
            tmp->vertices, 2, sfLines, NULL);
        tmp = tmp->next;
    }
}

static void display_alive_archer(rpg_t *rpg, entity_t *entity)
{
    display_common(rpg, entity);
    display_arrows(rpg, entity);
    if (entity->spe->archer->exclam->is_display == 1)
        sfRenderWindow_drawSprite(rpg->win->window,
            entity->spe->archer->exclam->anim->sprite, NULL);
    if (entity->spe->archer->inter->is_display == 1)
        sfRenderWindow_drawSprite(rpg->win->window,
            entity->spe->archer->inter->anim->sprite, NULL);
    if (rpg->modes->debug)
        display_debug_archer(rpg, entity);
}

void display_archer(rpg_t *rpg, entity_t *entity)
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
        display_alive_archer(rpg, entity);
}
