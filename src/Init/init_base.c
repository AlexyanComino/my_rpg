/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_base
*/

#include "rpg.h"

static bool warrior_has_base(warrior_t *warrior)
{
    if (!strcmp(warrior->name, "Enemy"))
        return true;
    if (!strcmp(warrior->name, "Ally"))
        return true;
    return false;
}

static sfIntRect get_base_rect(warrior_t *warrior)
{
    if (!strcmp(warrior->name, "Enemy"))
        return (sfIntRect){1100, 500, 800, 500};
    if (!strcmp(warrior->name, "Ally"))
        return (sfIntRect){100, 200, 500, 500};
    return (sfIntRect){0, 0, 0, 0};
}

static sfRectangleShape *init_base_shape(base_t *base, sfColor color)
{
    sfRectangleShape *shape = sfRectangleShape_create();

    sfRectangleShape_setSize(shape, (sfVector2f){base->rect.width, base->rect.height});
    sfRectangleShape_setFillColor(shape, sfTransparent);
    sfRectangleShape_setPosition(shape, (sfVector2f){base->rect.left,
        base->rect.top});
    sfRectangleShape_setOutlineColor(shape, color);
    sfRectangleShape_setOutlineThickness(shape, 1);
    return shape;
}

static sfCircleShape **get_pattern_pos_shapes(warrior_t *warrior, base_t *base)
{
    sfCircleShape **pattern_pos_shape;
    sfColor color = get_color_from_faction(warrior);
    int i = base->max_pos_index;

    pattern_pos_shape = malloc(sizeof(sfCircleShape *) * base->max_pos_index);
    for (int j = 0; j < i; j++) {
        pattern_pos_shape[j] = sfCircleShape_create();
        sfCircleShape_setRadius(pattern_pos_shape[j], 5);
        sfCircleShape_setFillColor(pattern_pos_shape[j], color);
        sfCircleShape_setOrigin(pattern_pos_shape[j], (sfVector2f){5, 5});
        sfCircleShape_setPosition(pattern_pos_shape[j], base->pattern_pos[j]);
    }
    return pattern_pos_shape;
}

static unsigned int get_max_pos_index(sfVector2f *pattern_pos)
{
    unsigned int i = 0;

    while (pattern_pos[i].x != -1 && pattern_pos[i].y != -1)
        i++;
    return i;
}

static float get_come_back_cooldown(void)
{
    return (float)(rand() % 200 + 300) / 100;
}

base_t *init_base(warrior_t *warrior)
{
    base_t *base = malloc(sizeof(base_t));

    if (!warrior_has_base(warrior)) {
        free(base);
        return NULL;
    }
    base->rect = get_base_rect(warrior);
    base->shape = init_base_shape(base, BASE_COLOR);
    base->pattern_pos = get_pattern_pos(warrior, base);
    base->come_back = false;
    base->pattern_pos_index = 0;
    base->max_pos_index = get_max_pos_index(base->pattern_pos);
    base->pattern_pos_shapes = get_pattern_pos_shapes(warrior, base);
    base->cooldown = get_come_back_cooldown();
    base->in_cooldown = false;
    base->myclock = init_my_clock();
    return base;
}
