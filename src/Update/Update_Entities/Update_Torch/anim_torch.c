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

static void animation_attack_torch2(rpg_t *rpg, entity_t *entity)
{
    if (entity->common->anim->rect.left == TORCH_WIDTH * 3)
        entity_attack(rpg, entity);
    if (entity->common->anim->rect.left >= TORCH_OFFSET) {
        entity->common->anim->rect.left = 0;
        reset_attack_torch(entity);
    } else
        entity->common->anim->rect.left += TORCH_WIDTH;
}

static void animation_attack_torch(rpg_t *rpg, entity_t *entity)
{
    if (entity->common->anim->myclock->seconds > 0.1) {
        animation_attack_torch2(rpg, entity);
        sfSprite_setTextureRect(entity->common->anim->sprite,
            entity->common->anim->rect);
        sfClock_restart(entity->common->anim->myclock->clock);
    }
}

static void animation_torch(rpg_t *rpg, entity_t *entity)
{
    if (entity->common->state == IDLE || entity->common->state == INTERACT) {
        entity->common->anim->rect.top = 0;
        return anim_line(entity->common->anim, TORCH_IDLE_OFFSET,
            TORCH_WIDTH, 0.1);
    }
    if (entity->common->state == WALK || entity->common->state == RUN) {
        entity->common->anim->rect.top = TORCH_WIDTH;
        return anim_line(entity->common->anim, TORCH_OFFSET, TORCH_WIDTH, 0.1);
    }
    if (is_attacking(entity))
        return animation_attack_torch(rpg, entity);
}

//
static void anim_gob_exclam(entity_t *entity)
{
    sfIntRect info = {GOB_EXCLAM_WIDTH, GOB_EXCLAM_HEIGHT, 11, 3};

    update_clock_seconds(entity->spe->torch->exclam->anim->myclock);
    if (entity->spe->torch->exclam->anim->myclock->seconds > 0.06) {
        anim_mark(entity->spe->torch->exclam, &info);
    }
}

void anim_torch(rpg_t *rpg, entity_t *entity)
{
    update_clock_seconds(entity->common->anim->myclock);
    if (is_dead(entity))
        animation_death(entity->common);
    else if (!is_stunned(entity))
        animation_torch(rpg, entity);
    if (entity->spe->torch->exclam->is_display == 1)
        anim_gob_exclam(entity);
}
