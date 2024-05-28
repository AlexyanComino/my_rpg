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
    if (entity->type != TORCH)
        sfRenderWindow_drawCircleShape(rpg->win->window,
            entity->common->zones->s_circle, NULL);
}

static void display_debug_common(rpg_t *rpg, entity_t *entity)
{
    entity_t *player = get_player(rpg);

    sfRenderWindow_drawRectangleShape(rpg->win->window,
        entity->common->zones->rect_hitbox, NULL);
    sfRenderWindow_drawRectangleShape(rpg->win->window,
        entity->common->zones->rect_hitbox_attack, NULL);
    sfRenderWindow_drawRectangleShape(rpg->win->window,
        entity->common->zones->rect_hitbox_foot, NULL);
    if (entity != player && entity->type != PAWN)
        draw_circles_zones(rpg, entity);
}

void display_round_rectangle(sfRenderWindow *window, round_rectangle_t *rect)
{
    sfRenderWindow_drawRectangleShape(window, rect->rect_w, NULL);
    sfRenderWindow_drawRectangleShape(window, rect->rect_h, NULL);
    for (int i = 0; i < 4; i++) {
        sfCircleShape_setPosition(rect->circle, rect->circle_pos[i]);
        sfRenderWindow_drawCircleShape(window, rect->circle, NULL);
    }
}

static void display_health_bar(rpg_t *rpg, entity_t *entity)
{
    if (entity->common->grade_type == BOSS)
        return;
    display_round_rectangle(rpg->win->window,
        entity->common->health_bar->back);
    display_round_rectangle(rpg->win->window,
        entity->common->health_bar->front);
}

static void display_arrows_hit(rpg_t *rpg, entity_t *entity)
{
    arrows_t *tmp = entity->common->arrows_hit;

    while (tmp) {
        sfRenderWindow_drawSprite(rpg->win->window, tmp->anim->sprite,
            NULL);
        tmp = tmp->next;
    }
}

static void display_effects(rpg_t *rpg, entity_t *entity)
{
    if (entity->common->fire->is_on_eff)
        sfRenderWindow_drawSprite(rpg->win->window,
            entity->common->fire->eff_mark->anim->sprite, NULL);
    if (entity->common->poison->is_on_eff)
        sfRenderWindow_drawSprite(rpg->win->window,
            entity->common->poison->eff_mark->anim->sprite, NULL);
}

static void display_common2(rpg_t *rpg, entity_t *entity)
{
    if (!is_player(rpg, entity) && rpg->modes->plus &&
        entity->common->grade_type != BOSS) {
        display_health_bar(rpg, entity);
        sfRenderWindow_drawText(rpg->win->window, entity->common->name_text,
        NULL);
    }
    if (rpg->modes->debug)
        display_debug_common(rpg, entity);
}

void display_common(rpg_t *rpg, entity_t *entity)
{
    if (entity->common->stun->is_stunned)
        sfRenderWindow_drawSprite(rpg->win->window,
            entity->common->stun->stun_mark->anim->sprite, NULL);
    display_effects(rpg, entity);
    sfRenderWindow_drawSprite(rpg->win->window, entity->common->anim->sprite,
        NULL);
    display_arrows_hit(rpg, entity);
    display_common2(rpg, entity);
}
