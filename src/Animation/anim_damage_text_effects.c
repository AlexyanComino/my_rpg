/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** anim_damage_text_effects
*/

#include "rpg.h"

static void remove_effect(damage_text_t *damage_text)
{
    sfSprite_destroy(damage_text->effect->sprite);
    sfTexture_destroy(damage_text->effect->texture);
    sfClock_destroy(damage_text->effect->myclock->clock);
    free(damage_text->effect->myclock);
    free(damage_text->effect);
    damage_text->effect = NULL;
}

static void update_critical_effect2(damage_text_t *damage_text)
{
    if (damage_text->effect->rect.left >= CRIT_WIDTH * 6 &&
        damage_text->effect->rect.top > CRIT_WIDTH * 2) {
        remove_effect(damage_text);
    } else if (damage_text->effect->rect.left >= CRIT_WIDTH * 6) {
        damage_text->effect->rect.left = 0;
        damage_text->effect->rect.top += CRIT_WIDTH;
    } else {
        damage_text->effect->rect.left += CRIT_WIDTH;
    }
}

static void update_critical_effect(damage_text_t *damage_text)
{
    update_clock_seconds(damage_text->effect->myclock);
    if (damage_text->effect->myclock->seconds > 0.05) {
        update_critical_effect2(damage_text);
        sfSprite_setTextureRect(damage_text->effect->sprite,
            damage_text->effect->rect);
        sfClock_restart(damage_text->effect->myclock->clock);
    }
}

static void update_bam_effect(damage_text_t *damage_text)
{
    update_clock_seconds(damage_text->effect->myclock);
    if (damage_text->effect->myclock->seconds > 0.05) {
        if (damage_text->effect->rect.left >= BAM_WIDTH * 6) {
            remove_effect(damage_text);
            return;
        } else {
            damage_text->effect->rect.left += BAM_WIDTH;
        }
        sfSprite_setTextureRect(damage_text->effect->sprite,
            damage_text->effect->rect);
        sfClock_restart(damage_text->effect->myclock->clock);
    }
}

void update_damage_text_effects(damage_text_t **damage_texts)
{
    damage_text_t *tmp = *damage_texts;

    while (tmp != NULL) {
        if (tmp->effect == NULL) {
            tmp = tmp->next;
            continue;
        }
        if (tmp->state == CRITICAL) {
            update_critical_effect(tmp);
            tmp = tmp->next;
            continue;
        }
        if (tmp->state == BAM)
            update_bam_effect(tmp);
        tmp = tmp->next;
    }
}
