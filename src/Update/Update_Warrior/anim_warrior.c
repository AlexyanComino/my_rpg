/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** anim_warrior
*/

#include "rpg.h"

static void animation_idle_walk_run(common_entity_t *common)
{
    if (common->anim->myclock->seconds > 0.1) {
        if (common->anim->rect.left >= WARRIOR_OFFSET)
            common->anim->rect.left = 0;
        else
            common->anim->rect.left += WARRIOR_WIDTH;
        sfSprite_setTextureRect(common->anim->sprite, common->anim->rect);
        sfClock_restart(common->anim->myclock->clock);
    }
}

static void reset_attack_warrior(entity_t *entity)
{
    entity->common->state = IDLE;
    entity->common->anim->rect.top = 0;
    entity->common->anim->rect.left = 0;
    entity->spe->warrior->line_attack = 0;
    sfClock_restart(entity->common->clock_cooldown_attack->clock);
}

static void animation_attack2(rpg_t *rpg, entity_t *entity)
{
    if (entity->common->anim->rect.left == WARRIOR_WIDTH * 3)
        entity_attack(rpg, entity);
    if (entity->common->anim->rect.left >= WARRIOR_OFFSET &&
        entity->spe->warrior->line_attack == 0) {
        if (entity->spe->warrior->line_attack <
            entity->spe->warrior->max_line_attack ||
            (is_player(rpg, entity) && sfKeyboard_isKeyPressed(sfKeySpace))
            || (!is_player(rpg, entity) &&
            entity_can_attack_enemy(rpg, entity))) {
            entity->spe->warrior->line_attack++;
            entity->common->anim->rect.left = 0;
            entity->common->anim->rect.top += WARRIOR_WIDTH;
        } else {
            reset_attack_warrior(entity);
        }
    } else if (entity->common->anim->rect.left >= WARRIOR_OFFSET &&
        entity->spe->warrior->line_attack == 1) {
        reset_attack_warrior(entity);
    } else
        entity->common->anim->rect.left += WARRIOR_WIDTH;
}

static void animation_attack(rpg_t *rpg, entity_t *entity)
{
    if (entity->common->anim->myclock->seconds > 0.1) {
        animation_attack2(rpg, entity);
        sfSprite_setTextureRect(entity->common->anim->sprite,
            entity->common->anim->rect);
        sfClock_restart(entity->common->anim->myclock->clock);
    }
}

static void animation_warrior(rpg_t *rpg, entity_t *entity)
{
    if (entity->common->state == IDLE) {
        entity->common->anim->rect.top = 0;
        animation_idle_walk_run(entity->common);
    }
    if (entity->common->state == WALK || entity->common->state == RUN) {
        entity->common->anim->rect.top = WARRIOR_WIDTH;
        animation_idle_walk_run(entity->common);
    }
    if (is_attacking(entity))
        animation_attack(rpg, entity);
}

static void anim_mark(mark_t *mark, int width, int height, int max_width)
{
    if (mark->anim->rect.top >= height * 2) {
        mark->anim->rect.top = 0;
        mark->anim->rect.left += width;
    } else if (mark->anim->rect.left >= width * max_width) {
        mark->is_display = 2;
    } else
        mark->anim->rect.top += height;
    sfSprite_setTextureRect(mark->anim->sprite, mark->anim->rect);
    sfClock_restart(mark->anim->myclock->clock);
}

static void anim_exclam(warrior_t *warrior)
{
    update_clock_seconds(warrior->exclam->anim->myclock);
    if (warrior->exclam->anim->myclock->seconds > 0.02) {
        anim_mark(warrior->exclam, EXCLAM_WIDTH, EXCLAM_HEIGHT, 11);
    }
}

static void anim_inter(warrior_t *warrior)
{
    update_clock_seconds(warrior->inter->anim->myclock);
    if (warrior->inter->anim->myclock->seconds > 0.02) {
        anim_mark(warrior->inter, INTER_WIDTH, INTER_HEIGHT, 14);
    }
}

void anim_warrior(rpg_t *rpg, entity_t *entity)
{
    if (entity->common->state == RIEN)
        return;
    update_clock_seconds(entity->common->anim->myclock);
    if (entity->common->state == DEAD)
        animation_death(entity->common);
    else
        animation_warrior(rpg, entity);
    if (entity->spe->warrior->exclam->is_display == 1)
        anim_exclam(entity->spe->warrior);
    if (entity->spe->warrior->inter->is_display == 1)
        anim_inter(entity->spe->warrior);
}
