/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_dyna
*/

#include "rpg.h"


static void anim_dyna(entity_t *entity)
{
    dyna_t *dyna = entity->spe->tnt->dyna;

    sfSprite_setRotation(dyna->anim->sprite, dyna->dyna_angle);
    dyna->dyna_angle += (entity->spe->tnt->dyna->side == RIGHT) ? 10 : -10;
    if (dyna->dyna_angle >= 360 || dyna->dyna_angle <= -360)
        dyna->dyna_angle = 0;
    update_clock_seconds(dyna->anim->myclock);
    if (dyna->anim->myclock->seconds > 0.1) {
        if (dyna->anim->rect.left >= DYNA_OFFSET) {
            dyna->anim->rect.left = 0;
        } else
            dyna->anim->rect.left += DYNA_WIDTH;
        sfSprite_setTextureRect(dyna->anim->sprite, dyna->anim->rect);
        sfClock_restart(dyna->anim->myclock->clock);
    }
}

static void update_dyna_pos(rpg_t *rpg, entity_t *entity, sfVector2f movement)
{
    float dt = rpg->win->dt;

    if (movement.x < 0) {
        entity->spe->tnt->dyna->pos.x += movement.x * dt;
    } else if (movement.x > 0) {
        entity->spe->tnt->dyna->pos.x += movement.x * dt;
    }
    if (movement.y < 0) {
        entity->spe->tnt->dyna->pos.y += movement.y * dt;
    } else if (movement.y > 0) {
        entity->spe->tnt->dyna->pos.y += movement.y * dt;
    }
}

static float get_dyna_speed(entity_t *entity)
{
    float speed = 700;
    curve_t *curve = entity->spe->tnt->curve;

    if (curve->y != NONE)
        speed = speed * 20 / 30;
    return speed;
}

static void move_dyna(rpg_t *rpg, entity_t *entity)
{
    sfVector2f target_pos = entity->spe->tnt->dyna->points
        [entity->spe->tnt->dyna->index];
    float distance = get_distance(entity->spe->tnt->dyna->pos,
        target_pos);
    sfVector2f movement = get_movement(target_pos, entity->spe->tnt->dyna->pos,
        distance, get_dyna_speed(entity));

    update_dyna_pos(rpg, entity, movement);
    if (get_distance(entity->spe->tnt->dyna->pos, target_pos) > 10)
        return;
    entity->spe->tnt->dyna->index++;
    if (entity->spe->tnt->dyna->index >=
        entity->spe->tnt->curve->nb_points) {
        entity->spe->tnt->dyna->index = 0;
        entity->spe->tnt->is_launched = false;
        entity->spe->tnt->is_exploded = true;
        sfSprite_setPosition(entity->spe->tnt->explo->anim->sprite,
            entity->spe->tnt->dyna->pos);
        entity_attack(rpg, entity);
    }
}

void update_dyna(rpg_t *rpg, entity_t *entity)
{
    int nb_points = entity->spe->tnt->curve->nb_points;

    if (entity->spe->tnt->is_launched) {
        anim_dyna(entity);
        move_dyna(rpg, entity);
        sfSprite_setPosition(entity->spe->tnt->dyna->anim->sprite,
            entity->spe->tnt->dyna->pos);
    } else {
        entity->spe->tnt->explo->boom_center =
            (sfVector2f){entity->common->pos.x +
            entity->spe->tnt->curve->points[nb_points - 1].x,
            entity->common->pos.y +
            entity->spe->tnt->curve->points[nb_points - 1].y};
        sfCircleShape_setPosition(entity->spe->tnt->explo->boom_circle,
            entity->spe->tnt->explo->boom_center);
        if (is_player(rpg, entity))
            sfSprite_setPosition(entity->spe->tnt->explo->cible,
                entity->spe->tnt->explo->boom_center);
    }
}
