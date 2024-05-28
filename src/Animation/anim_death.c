/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** anim_death
*/

#include "rpg.h"

static void remove_entity(common_entity_t *common)
{
    common->death->anim->rect.left = 0;
    common->death->anim->rect.top = 0;
    common->death->number_dead = 0;
    common->pos = common->init_pos;
    common->attributes->health = common->attributes->max_health;
    common->state = RIEN;
    common->health_bar->front->size = common->health_bar->front->init_size;
    common->health_bar->front->r = common->health_bar->front->init_r;
    sfClock_restart(common->death->anim->myclock->clock);
}

static void animation_dead3(common_entity_t *common, bool time_elapsed)
{
    if (common->death->number_dead == 1 && time_elapsed) {
        common->death->anim->rect.left = 0;
        common->death->anim->rect.top = DEAD_WIDTH;
        common->death->number_dead = 2;
    } else if (common->death->number_dead == 2 &&
        common->death->anim->rect.left >= DEAD_WIDTH * 6) {
        remove_entity(common);
    } else {
        common->death->anim->rect.left += DEAD_WIDTH;
    }
    sfClock_restart(common->death->anim->myclock->clock);
}

static void animation_dead2(common_entity_t *common)
{
    bool time_elapsed = common->death->anim->myclock->seconds > DEAD_COOLDOWN;

    if (common->death->number_dead == 1 && common->grade_type == SOLDAT_QUEST)
        return;
    if (common->death->number_dead == 0 &&
        common->death->anim->rect.left >= DEAD_WIDTH * 6) {
        common->death->number_dead = 1;
        sfClock_restart(common->death->anim->myclock->clock);
    } else if (common->death->number_dead == 1 && !time_elapsed) {
        common->death->anim->rect.left = DEAD_WIDTH * 6;
    } else
        animation_dead3(common, time_elapsed);
}

void animation_death(common_entity_t *common)
{
    update_clock_seconds(common->death->anim->myclock);
    if (common->death->anim->myclock->seconds > 0.1) {
        animation_dead2(common);
        sfSprite_setTextureRect(common->death->anim->sprite,
            common->death->anim->rect);
    }
}
