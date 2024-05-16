/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** display_warriors
*/

#include "rpg.h"

static void display_pattern_pos_shapes(rpg_t *rpg, entity_t *entity)
{
    int i = 0;

    while (entity->spe->warrior->base->pattern_pos[i].x != -1 &&
        entity->spe->warrior->base->pattern_pos[i].y != -1) {
        sfRenderWindow_drawCircleShape(rpg->win->window,
            entity->spe->warrior->base->pattern_pos_shapes[i], NULL);
        i++;
    }
}

static void display_debug_warrior(rpg_t *rpg, entity_t *entity)
{
    if (entity_has_base(entity)) {
        sfRenderWindow_drawRectangleShape(rpg->win->window,
        entity->spe->warrior->base->shape, NULL);
        display_pattern_pos_shapes(rpg, entity);
    }
}

static void display_alive_warrior(rpg_t *rpg, entity_t *entity)
{
    display_common(rpg, entity);
    if (entity->spe->warrior->exclam->is_display == 1)
        sfRenderWindow_drawSprite(rpg->win->window,
            entity->spe->warrior->exclam->anim->sprite, NULL);
    if (entity->spe->warrior->inter->is_display == 1)
        sfRenderWindow_drawSprite(rpg->win->window,
            entity->spe->warrior->inter->anim->sprite, NULL);
    if (rpg->debug)
        display_debug_warrior(rpg, entity);
}

void display_warrior(void *vrpg, entity_t *entity)
{
    rpg_t *rpg = (rpg_t *)vrpg;

    if (entity->common->state == RIEN)
        return;
    if (entity->common->state == DEAD)
        sfRenderWindow_drawSprite(rpg->win->window,
        entity->common->death->anim->sprite, NULL);
    else
        display_alive_warrior(rpg, entity);
}
