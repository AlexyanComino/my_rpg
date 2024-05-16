/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_round_rectangle
*/

#include "rpg.h"

static void init_circles_round_rectangle(round_rectangle_t *rect,
    sfColor color)
{
    sfCircleShape_setRadius(rect->circle, rect->r);
    sfCircleShape_setFillColor(rect->circle, color);
    fill_round(rect, rect->r, rect->pos, rect->size);
}

round_rectangle_t *init_round_rectangle(sfVector2f pos, float r,
    sfVector2f size, sfColor color)
{
    round_rectangle_t *rect = malloc(sizeof(round_rectangle_t));
    sfRectangleShape *rect_w = sfRectangleShape_create();
    sfRectangleShape *rect_h = sfRectangleShape_create();

    sfRectangleShape_setSize(rect_w, (sfVector2f){size.x, size.y - r * 2});
    sfRectangleShape_setSize(rect_h, (sfVector2f){size.x - r * 2, size.y});
    sfRectangleShape_setPosition(rect_w, (sfVector2f) {pos.x, pos.y + r});
    sfRectangleShape_setPosition(rect_h, (sfVector2f) {pos.x + r, pos.y});
    sfRectangleShape_setFillColor(rect_w, color);
    sfRectangleShape_setFillColor(rect_h, color);
    rect->rect_w = rect_w;
    rect->rect_h = rect_h;
    rect->r = r;
    rect->init_r = r;
    rect->pos = pos;
    rect->size = size;
    rect->init_size = size;
    rect->circle = sfCircleShape_create();
    init_circles_round_rectangle(rect, color);
    return rect;
}
