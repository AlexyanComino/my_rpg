/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_warrior_marks
*/

#include "rpg.h"

static void init_circle_detection(mark_t *mark, sfColor color)
{
    mark->circle = sfCircleShape_create();
    sfCircleShape_setRadius(mark->circle, mark->radius);
    sfCircleShape_setFillColor(mark->circle, sfTransparent);
    sfCircleShape_setOutlineColor(mark->circle, color);
    sfCircleShape_setOutlineThickness(mark->circle, 1);
    sfCircleShape_setOrigin(mark->circle, (sfVector2f){mark->radius,
        mark->radius});
}

mark_t *init_exclam(warrior_t *warrior)
{
    mark_t *exclam = malloc(sizeof(mark_t));

    exclam->texture = sfTexture_createFromFile("assets/exclam_red.png", NULL);
    exclam->sprite = sfSprite_create();
    sfSprite_setTexture(exclam->sprite, exclam->texture, sfTrue);
    sfSprite_setOrigin(exclam->sprite, (sfVector2f){EXCLAM_WIDTH / 2,
        EXCLAM_HEIGHT / 2});
    exclam->pos = (sfVector2f){warrior->pos.x, warrior->pos.y};
    exclam->myclock = init_my_clock();
    exclam->rect = (sfIntRect){0, 0, EXCLAM_WIDTH, EXCLAM_HEIGHT};
    sfSprite_setTextureRect(exclam->sprite, exclam->rect);
    exclam->is_display = 0;
    exclam->is_detecting = false;
    exclam->radius = 200;
    init_circle_detection(exclam, sfRed);
    return exclam;
}

mark_t *init_inter(warrior_t *warrior)
{
    mark_t *inter = malloc(sizeof(mark_t));

    inter->texture = sfTexture_createFromFile("assets/inter_color.png", NULL);
    inter->sprite = sfSprite_create();
    sfSprite_setTexture(inter->sprite, inter->texture, sfTrue);
    inter->pos = (sfVector2f){warrior->pos.x, warrior->pos.y};
    sfSprite_setOrigin(inter->sprite, (sfVector2f){INTER_WIDTH / 2,
        INTER_HEIGHT / 2});
    inter->myclock = init_my_clock();
    inter->rect = (sfIntRect){0, 0, INTER_WIDTH, INTER_HEIGHT};
    sfSprite_setTextureRect(inter->sprite, inter->rect);
    inter->is_display = 0;
    inter->is_detecting = false;
    inter->radius = 350;
    inter->circle = sfCircleShape_create();
    init_circle_detection(inter, sfYellow);
    return inter;
}
