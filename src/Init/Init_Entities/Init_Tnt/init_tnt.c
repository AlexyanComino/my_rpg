/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_tnt
*/

#include "rpg.h"

sfVector2f* get_points_parabol(float velocity, float angle, float gravity)
{
    sfVector2f *points = malloc(sizeof(sfVector2f) * NUM_POINTS);
    float radianAngle = angle * (M_PI / 180);
    float initialVelocityX = velocity * cos(radianAngle);
    float initialVelocityY = velocity * sin(radianAngle);
    float timeIncrement = (2 * initialVelocityY) / (gravity * NUM_POINTS);
    float time = 0;
    float x = 0;
    float y = 0;

    for (int i = 0; i < NUM_POINTS; ++i) {
        time = timeIncrement * i;
        x = initialVelocityX * time;
        y = initialVelocityY * time - (0.5 * gravity * time * time);
        points[i] = (sfVector2f){x, -y};
    }
    for (int i = 0; i < NUM_POINTS; i++) {
        points[i].x *= 100;
        points[i].y *= 100;
    }
    return points;
}

sfConvexShape *get_parabol_curve(sfVector2f *points, int nb_points)
{
    sfConvexShape *curve = sfConvexShape_create();

    sfConvexShape_setPointCount(curve, nb_points);
    sfConvexShape_setFillColor(curve, sfTransparent);
    sfConvexShape_setOutlineThickness(curve, 2);
    sfConvexShape_setOutlineColor(curve, sfRed);
    for (int i = 0; i < nb_points; ++i) {
        sfConvexShape_setPoint(curve, i, points[i]);
    }
    sfConvexShape_setOrigin(curve, points[0]);
    return curve;
}

static curve_t *init_curve_tnt(entity_t *entity)
{
    curve_t *curve = malloc(sizeof(curve_t));
    float scale = entity->common->scale;

    curve->points = get_points_parabol(3.9 * scale, 55, 4 * scale);
    if (entity->common->x == LEFT) {
        for (int i = 0; i < NUM_POINTS; i++) {
            curve->points[i].x *= -1;
        }
    }
    curve->x = entity->common->x;
    curve->y = entity->common->y;
    curve->nb_points = NUM_POINTS;
    curve->curve_shape = get_parabol_curve(curve->points, curve->nb_points);
    return curve;
}

static void init_cible(explo_t *explo, float scale)
{
    explo->cible = sfSprite_create();
    explo->cible_texture = sfTexture_createFromFile(
        "assets/Entities/Tnt/cible.png", NULL);
    sfSprite_setTexture(explo->cible, explo->cible_texture, sfTrue);
    sfSprite_setScale(explo->cible, (sfVector2f){0.25 * scale, 0.25 * scale});
    sfSprite_setColor(explo->cible, sfColor_fromRGBA(255, 255, 255, 140));
    sfSprite_setOrigin(explo->cible, (sfVector2f){CIBLE_WIDTH / 2,
        CIBLE_WIDTH / 2});
}

static explo_t *init_explo(float scale)
{
    explo_t *explo = malloc(sizeof(explo_t));

    explo->anim = init_anim("assets/Entities/Tnt/Explosions.png", EXPLO_WIDTH,
        EXPLO_WIDTH);
    sfSprite_setScale(explo->anim->sprite, (sfVector2f){scale, scale});
    explo->radius = 50 * scale;
    explo->boom_circle = sfCircleShape_create();
    explo->boom_center = (sfVector2f){0, 0};
    sfCircleShape_setRadius(explo->boom_circle, explo->radius);
    sfCircleShape_setFillColor(explo->boom_circle, sfTransparent);
    sfCircleShape_setOutlineThickness(explo->boom_circle, 2);
    sfCircleShape_setOutlineColor(explo->boom_circle, sfRed);
    sfCircleShape_setOrigin(explo->boom_circle, (sfVector2f){explo->radius,
        explo->radius});
    init_cible(explo, scale);
    return explo;
}

static dyna_t *init_dyna(float scale)
{
    dyna_t *dyna = malloc(sizeof(dyna_t));

    dyna->anim = init_anim("assets/Entities/Tnt/Dynamite.png", DYNA_WIDTH,
        DYNA_WIDTH);
    sfSprite_setScale(dyna->anim->sprite, (sfVector2f){scale, scale});
    dyna->pos = (sfVector2f){0, 0};
    dyna->dyna_angle = 0;
    dyna->points = malloc(sizeof(sfVector2f) * NUM_POINTS);
    dyna->index = 0;
    return dyna;
}

static tnt_t *init_tnt(entity_t *entity, char **infos)
{
    tnt_t *tnt = malloc(sizeof(tnt_t));
    float scale = entity->common->scale;

    tnt->dyna = init_dyna(scale);
    tnt->curve = init_curve_tnt(entity);
    tnt->is_launched = false;
    tnt->explo = init_explo(scale);
    tnt->is_exploded = false;
    infos = infos;
    return tnt;
}

static spe_t *init_spe_tnt(entity_t *entity, char **infos)
{
    spe_t *spe = malloc(sizeof(spe_t));

    spe->tnt = init_tnt(entity, infos);
    return spe;
}

entity_t *init_entity_tnt(char **infos)
{
    entity_t *entity = malloc(sizeof(entity_t));

    entity->type = TNT;
    entity->common = init_common(infos, TNT);
    entity->spe = init_spe_tnt(entity, infos);
    entity->in_view = false;
    entity->updt = &update_tnt;
    entity->disp = &display_tnt;
    entity->anim = &anim_tnt;
    entity->destroy = &destroy_entity_tnt;
    entity->get_hitbox = &get_hitbox_tnt;
    entity->get_hitbox_attack = &get_hitbox_attack_tnt;
    entity->get_hitbox_foot = &get_hitbox_tnt_foot;
    return entity;
}
