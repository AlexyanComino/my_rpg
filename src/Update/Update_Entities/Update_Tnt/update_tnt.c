/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_tnt
*/

#include "rpg.h"

static void update_tnt_points_up(curve_t *curve, float scale)
{
    curve->points = get_points_parabol(4 * scale, 70, 3 * scale);
    for (int i = 20; i < curve->nb_points; i++) {
        curve->points[i] = (sfVector2f){0, 0};
    }
    curve->points = realloc(curve->points, sizeof(sfVector2f) * 20);
    curve->nb_points = 20;
}

static void update_tnt_points_down(curve_t *curve, float scale)
{
    sfVector2f diff;

    curve->points = get_points_parabol(4 * scale, 70, 3 * scale);
    curve->nb_points = 20;
    diff = (sfVector2f){curve->points[0].x - curve->points[10].x,
        curve->points[0].y - curve->points[10].y};
    for (int i = 0; i < 20; i++)
        curve->points[i] = curve->points[i + 10];
    curve->points = realloc(curve->points, sizeof(sfVector2f) * 20);
    for (int i = 0; i < 20; i++) {
        curve->points[i].x += diff.x;
        curve->points[i].y += diff.y;
    }
}

static void update_tnt_points(entity_t *entity, curve_t *curve)
{
    float scale = entity->common->scale;

    if (entity->common->y == curve->y)
        return;
    if (entity->common->y == NONE) {
        curve->points = get_points_parabol(3.9 * scale, 55, 4 * scale);
        curve->nb_points = 30;
    } else if (entity->common->y == UP)
        update_tnt_points_up(curve, scale);
    else
        update_tnt_points_down(curve, scale);
    curve->y = entity->common->y;
    curve->x = RIGHT;
    sfConvexShape_destroy(curve->curve_shape);
    curve->curve_shape = get_parabol_curve(curve->points,
        curve->nb_points);
}

static void update_tnt_curve(entity_t *entity)
{
    curve_t *curve = entity->spe->tnt->curve;

    if (entity->spe->tnt->is_launched)
        return;
    update_tnt_points(entity, curve);
    if (entity->common->x != curve->x) {
        for (int i = 0; i < curve->nb_points; i++) {
            curve->points[i].x *= -1;
        }
        curve->x = entity->common->x;
    }
    for (int i = 0; i < curve->nb_points; i++) {
        sfConvexShape_setPoint(curve->curve_shape, i,
            (sfVector2f){entity->common->pos.x + curve->points[i].x,
                entity->common->pos.y + curve->points[i].y});
    }
}

static void update_explo(entity_t *entity)
{
    if (entity->spe->tnt->is_exploded) {
        update_clock_seconds(entity->spe->tnt->explo->anim->myclock);
        if (entity->spe->tnt->explo->anim->myclock->seconds < 0.1)
            return;
        if (entity->spe->tnt->explo->anim->rect.left >= EXPLO_OFFSET) {
            entity->spe->tnt->is_exploded = false;
            entity->spe->tnt->explo->anim->rect.left = 0;
        } else
            entity->spe->tnt->explo->anim->rect.left += EXPLO_WIDTH;
        sfSprite_setTextureRect(entity->spe->tnt->explo->anim->sprite,
            entity->spe->tnt->explo->anim->rect);
        sfClock_restart(entity->spe->tnt->explo->anim->myclock->clock);
    }
}

void update_tnt(rpg_t *rpg, entity_t *entity)
{
    update_common(rpg, entity);
    if (entity->common->state == RIEN)
        return;
    if (!is_player(rpg, entity) && is_alive(entity))
        update_pnj_tnt(rpg, entity);
    update_tnt_curve(entity);
    update_dyna(rpg, entity);
    update_explo(entity);
    entity->anim(rpg, entity);
}
