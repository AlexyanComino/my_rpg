/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** anim_tnt
*/

#include "rpg.h"

/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** anim_torch
*/

#include "rpg.h"

static void reset_attack_torch(entity_t *entity)
{
    entity->common->anim->rect.top = 0;
    entity->common->anim->rect.left = 0;
    sfClock_restart(entity->common->clock_cooldown_attack->clock);
    entity->common->state = IDLE;
}

static void animation_attack_tnt2(entity_t *entity)
{
    if (entity->common->anim->rect.left == TNT_WIDTH * 2)
        launch_dyna(entity);
    if (entity->common->anim->rect.left >= TNT_OFFSET_ATTACK) {
        entity->common->anim->rect.left = 0;
        reset_attack_torch(entity);
    } else
        entity->common->anim->rect.left += TNT_WIDTH;
}

static void animation_attack_tnt(entity_t *entity)
{
    if (entity->common->anim->myclock->seconds > 0.1) {
        animation_attack_tnt2(entity);
        sfSprite_setTextureRect(entity->common->anim->sprite,
            entity->common->anim->rect);
        sfClock_restart(entity->common->anim->myclock->clock);
    }
}

static void animation_tnt(entity_t *entity)
{
    if (entity->common->state == IDLE || entity->common->state == INTERACT) {
        entity->common->anim->rect.top = 0;
        return anim_line(entity->common->anim, TNT_OFFSET, TNT_WIDTH, 0.1);
    }
    if (entity->common->state == WALK || entity->common->state == RUN) {
        entity->common->anim->rect.top = TORCH_WIDTH;
        return anim_line(entity->common->anim, TNT_OFFSET, TNT_WIDTH, 0.1);
    }
    if (is_attacking(entity))
        return animation_attack_tnt(entity);
}

void anim_tnt(rpg_t *rpg, entity_t *entity)
{
    (void)rpg;
    update_clock_seconds(entity->common->anim->myclock);
    if (is_dead(entity))
        animation_death(entity->common);
    else if (!is_stunned(entity))
        animation_tnt(entity);
}
