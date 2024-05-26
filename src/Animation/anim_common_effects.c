/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** anim_common_effects
*/

#include "rpg.h"

static void anim_fire(entity_t *entity)
{
    if (entity->common->fire->is_on_eff) {
        update_clock_seconds(entity->common->fire->eff_mark->anim->myclock);
        if (entity->common->fire->eff_mark->anim->myclock->seconds > 0.1)
            anim_fire_mark(entity->common->fire->eff_mark, FIRE_WIDTH, 6);
        entity->common->fire->eff_mark->is_display = 1;
        entity->common->fire->eff_mark->pos = (sfVector2f){
            entity->common->pos.x, entity->common->pos.y - 5};
        sfSprite_setPosition(entity->common->fire->eff_mark->anim->sprite,
            entity->common->fire->eff_mark->pos);
    } else {
        entity->common->fire->eff_mark->is_display = 0;
    }
}

static void anim_stun(entity_t *entity)
{
    sfIntRect info;

    if (entity->common->stun->is_stunned) {
        update_clock_seconds(entity->common->stun->stun_mark->anim->myclock);
        if (entity->common->stun->stun_mark->anim->myclock->seconds > 0.05) {
            info = (sfIntRect){STUN_WIDTH, STUN_HEIGHT, 2, 41};
            anim_mark(entity->common->stun->stun_mark, &info);
        }
        entity->common->stun->stun_mark->is_display = 1;
        entity->common->stun->stun_mark->pos = (sfVector2f){
            entity->common->pos.x, entity->common->pos.y - 50};
        sfSprite_setPosition(entity->common->stun->stun_mark->anim->sprite,
            entity->common->stun->stun_mark->pos);
    } else {
        entity->common->stun->stun_mark->is_display = 0;
    }
}

static void anim_poison(entity_t *entity)
{
    if (entity->common->poison->is_on_eff) {
        update_clock_seconds(entity->common->poison->eff_mark->anim->myclock);
        if (entity->common->poison->eff_mark->anim->myclock->seconds > 0.1) {
            anim_poison_mark(entity->common->poison->eff_mark);
        }
        entity->common->poison->eff_mark->is_display = 1;
        entity->common->poison->eff_mark->pos = entity->common->pos;
        sfSprite_setPosition(entity->common->poison->eff_mark->anim->sprite,
            entity->common->poison->eff_mark->pos);
    } else {
        entity->common->poison->eff_mark->is_display = 0;
    }
}

void anim_common_effects(entity_t *entity)
{
    anim_stun(entity);
    anim_fire(entity);
    anim_poison(entity);
}
