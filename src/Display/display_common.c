/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** display_common
*/

#include "rpg.h"

static void draw_circles_zones(rpg_t *rpg, entity_t *entity)
{
    sfRenderWindow_drawCircleShape(rpg->win->window,
        entity->common->zones->l_circle, NULL);
    sfRenderWindow_drawCircleShape(rpg->win->window,
        entity->common->zones->m_circle, NULL);
    sfRenderWindow_drawCircleShape(rpg->win->window,
        entity->common->zones->s_circle, NULL);
}

static void display_debug_common(rpg_t *rpg, entity_t *entity)
{
    entity_t *player = rpg->ent[0];

    sfRenderWindow_drawRectangleShape(rpg->win->window,
        entity->common->zones->rect_hitbox, NULL);
    sfRenderWindow_drawRectangleShape(rpg->win->window,
        entity->common->zones->rect_hitbox_attack, NULL);
    if (entity != player && entity->type != PAWN)
        draw_circles_zones(rpg, entity);
}

void display_common(rpg_t *rpg, entity_t *entity)
{
    if (entity->common->state == DEAD)
        return;
    sfRenderWindow_drawSprite(rpg->win->window, entity->common->anim->sprite,
        NULL);
    if (entity->common->stun->is_stunned)
        sfRenderWindow_drawSprite(rpg->win->window,
            entity->common->stun->stun_mark->anim->sprite, NULL);
    if (rpg->debug)
        display_debug_common(rpg, entity);
}
