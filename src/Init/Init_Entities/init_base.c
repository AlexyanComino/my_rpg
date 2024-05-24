/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_warrior_base
*/

#include "rpg.h"

static sfIntRect get_base_rect(char **infos)
{
    return (sfIntRect){atoi(infos[16]), atoi(infos[17]), atoi(infos[18]),
        atoi(infos[19])};
}

static sfRectangleShape *init_base_shape(base_t *base, sfColor color)
{
    sfRectangleShape *shape = sfRectangleShape_create();

    sfRectangleShape_setSize(shape, (sfVector2f){base->rect.width,
        base->rect.height});
    sfRectangleShape_setFillColor(shape, sfTransparent);
    sfRectangleShape_setPosition(shape, (sfVector2f){base->rect.left,
        base->rect.top});
    sfRectangleShape_setOutlineColor(shape, color);
    sfRectangleShape_setOutlineThickness(shape, 1);
    return shape;
}

static sfVector2f *get_pattern_pos(char **infos, unsigned int *max_pattern_pos)
{
    sfVector2f *pattern_pos = malloc(sizeof(sfVector2f) * 1);
    int i = 20;

    while (infos[i] != NULL) {
        pattern_pos = realloc(pattern_pos, sizeof(sfVector2f) *
            (*max_pattern_pos + 1));
        pattern_pos[*max_pattern_pos].x = atoi(infos[i]);
        pattern_pos[*max_pattern_pos].y = atoi(infos[i + 1]);
        (*max_pattern_pos)++;
        if (infos[i + 1] == NULL) {
            fprintf(stderr, "Error: missing y value for pattern_pos\n");
            break;
        }
        i += 2;
    }
    pattern_pos = realloc(pattern_pos, sizeof(sfVector2f) *
        (*max_pattern_pos + 1));
    pattern_pos[*max_pattern_pos].x = -1;
    pattern_pos[*max_pattern_pos].y = -1;
    return pattern_pos;
}

static sfCircleShape **get_pattern_pos_shapes(base_t *base)
{
    sfCircleShape **pattern_pos_shape;
    sfColor color = BASE_COLOR;
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

static float get_come_back_cooldown(void)
{
    return (float)(rand() % 200 + 300) / 100;
}

base_t *init_base(char **infos)
{
    base_t *base = malloc(sizeof(base_t));

    if (atoi(infos[15]) == 0) {
        free(base);
        return NULL;
    }
    base->rect = get_base_rect(infos);
    base->shape = init_base_shape(base, BASE_COLOR);
    base->max_pos_index = 0;
    base->pattern_pos = get_pattern_pos(infos, &base->max_pos_index);
    base->pattern_pos_index = 0;
    base->pattern_pos_shapes = get_pattern_pos_shapes(base);
    base->come_back = false;
    base->cooldown = get_come_back_cooldown();
    base->in_cooldown = false;
    base->myclock = init_my_clock();
    return base;
}
