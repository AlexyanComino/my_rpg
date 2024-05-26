/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_health_bar
*/

#include "rpg.h"

void fill_round(round_rectangle_t *rect, float r, sfVector2f pos,
    sfVector2f size)
{
    rect->circle_pos[0] = (sfVector2f) {pos.x, pos.y};
    rect->circle_pos[1] = (sfVector2f) {pos.x + size.x - r * 2, pos.y};
    rect->circle_pos[2] = (sfVector2f) {pos.x + size.x - r * 2,
        pos.y + size.y - r * 2};
    rect->circle_pos[3] = (sfVector2f) {pos.x, pos.y + size.y - r * 2};
}

static void update_front_bar(entity_t *entity, sfVector2f siz, sfColor color)
{
    round_rectangle_t *frt = entity->common->health_bar->front;
    float r = frt->r;

    sfRectangleShape_setSize(frt->rect_w, (sfVector2f){siz.x, siz.y - r * 2});
    sfRectangleShape_setSize(frt->rect_h, (sfVector2f){siz.x - r * 2, siz.y});
    sfRectangleShape_setPosition(frt->rect_w,
        (sfVector2f) {frt->pos.x, frt->pos.y + r});
    sfRectangleShape_setPosition(frt->rect_h,
        (sfVector2f) {frt->pos.x + r, frt->pos.y});
    sfRectangleShape_setFillColor(frt->rect_w, color);
    sfRectangleShape_setFillColor(frt->rect_h, color);
    sfCircleShape_setFillColor(frt->circle, color);
    if (sfCircleShape_getRadius(frt->circle) != r)
        sfCircleShape_setRadius(frt->circle, r);
    fill_round(frt, r, frt->pos, siz);
}

static void update_back_bar(entity_t *entity)
{
    round_rectangle_t *back = entity->common->health_bar->back;
    float r = back->r;

    sfRectangleShape_setPosition(back->rect_w, (sfVector2f)
        {back->pos.x, back->pos.y + r});
    sfRectangleShape_setPosition(back->rect_h, (sfVector2f)
        {back->pos.x + r, back->pos.y});
    fill_round(back, r, back->pos, back->size);
}

void update_health_bar(entity_t *entity)
{
    float ratio = (float)entity->common->attributes->health /
        (float)entity->common->attributes->max_health;
    sfVector2f size = {entity->common->health_bar->front->size.x * ratio,
        entity->common->health_bar->front->size.y};
    sfColor color = sfColor_fromRGB(255 * (1 - ratio), 255 * ratio, 0);

    if (size.x < entity->common->health_bar->front->r * 2)
        entity->common->health_bar->front->r = size.x / 2;
    entity->common->health_bar->front->pos = (sfVector2f)
        {entity->common->pos.x - entity->common->health_bar->front->size.x / 2,
        entity->common->pos.y + entity->common->health_bar->diff_y +
        (entity->common->health_bar->back->size.y -
        entity->common->health_bar->front->size.y) / 2};
    update_front_bar(entity, size, color);
    entity->common->health_bar->back->pos = (sfVector2f)
        {entity->common->pos.x - entity->common->health_bar->back->size.x / 2,
        entity->common->pos.y + entity->common->health_bar->diff_y};
    update_back_bar(entity);
}

void update_health_bar_boss(rpg_t *rpg, entity_t *entity)
{
    float ratio = (float)entity->common->attributes->health /
        (float)entity->common->attributes->max_health;
    sfVector2f size = {entity->common->health_bar->front->size.x * ratio,
        entity->common->health_bar->front->size.y};
    sfVector2f pos = get_player(rpg)->common->pos;

    if (size.x < entity->common->health_bar->front->r * 2)
        entity->common->health_bar->front->r = size.x / 2;
    entity->common->health_bar->front->pos = (sfVector2f)
        {pos.x - entity->common->health_bar->front->size.x / 2,
        pos.y - HEIGHT / 2 + 60 + (entity->common->health_bar->back->size.y -
        entity->common->health_bar->front->size.y) / 2};
    update_front_bar(entity, size, sfColor_fromRGB(198, 52, 40));
    entity->common->health_bar->back->pos = (sfVector2f)
        {pos.x - entity->common->health_bar->back->size.x / 2,
        pos.y - HEIGHT / 2 + 60};
    update_back_bar(entity);
}
