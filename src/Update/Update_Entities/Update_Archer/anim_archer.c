/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** anim_archer
*/

#include "rpg.h"


static void reset_attack_archer(entity_t *entity)
{
    entity->common->anim->rect.top = 0;
    entity->common->anim->rect.left = 0;
    sfClock_restart(entity->common->clock_cooldown_attack->clock);
    entity->common->state = IDLE;
}

static arrow_dir_t get_arrow_dir(entity_t *entity)
{
    sfIntRect rect = entity->common->anim->rect;
    side_x_t x = entity->common->x;

    if (rect.top == ARCHER_WIDTH * 2)
        return UP_ARROW;
    if (rect.top == ARCHER_WIDTH * 3)
        return (x == RIGHT) ? UP_RIGHT_ARROW : UP_LEFT_ARROW;
    if (rect.top == ARCHER_WIDTH * 4)
        return (x == RIGHT) ? RIGHT_ARROW : LEFT_ARROW;
    if (rect.top == ARCHER_WIDTH * 5)
        return (x == RIGHT) ? DOWN_RIGHT_ARROW : DOWN_LEFT_ARROW;
    if (rect.top == ARCHER_WIDTH * 6)
        return DOWN_ARROW;
    return RIGHT_ARROW;
}

static void animation_attack_archer2(rpg_t *rpg, entity_t *entity)
{
    if (entity->common->anim->rect.left == ARCHER_WIDTH * 6)
        shoot_arrow(rpg, entity, get_arrow_dir(entity));
    if (entity->common->anim->rect.left >= ARCHER_OFFSET_ATTACK) {
        entity->common->anim->rect.left = 0;
        reset_attack_archer(entity);
    } else
        entity->common->anim->rect.left += ARCHER_WIDTH;
}

static void animation_attack_archer(rpg_t *rpg, entity_t *entity)
{
    if (entity->common->anim->myclock->seconds > 0.1) {
        animation_attack_archer2(rpg, entity);
        sfSprite_setTextureRect(entity->common->anim->sprite,
            entity->common->anim->rect);
        sfClock_restart(entity->common->anim->myclock->clock);
    }
}

static void animation_archer(rpg_t *rpg, entity_t *entity)
{
    if (entity->common->state == IDLE || entity->common->state == INTERACT) {
        entity->common->anim->rect.top = 0;
        return anim_line(entity->common->anim, ARCHER_OFFSET,
            ARCHER_WIDTH, 0.1);
    }
    if (entity->common->state == WALK || entity->common->state == RUN) {
        entity->common->anim->rect.top = ARCHER_WIDTH;
        return anim_line(entity->common->anim, ARCHER_OFFSET,
            ARCHER_WIDTH, 0.1);
    }
    if (is_attacking(entity))
        return animation_attack_archer(rpg, entity);
}

static void anim_exclam(archer_t *archer)
{
    sfIntRect info = {EXCLAM_WIDTH, EXCLAM_HEIGHT, 11, 2};

    update_clock_seconds(archer->exclam->anim->myclock);
    if (archer->exclam->anim->myclock->seconds > 0.02) {
        anim_mark(archer->exclam, &info);
    }
}

static void anim_inter(archer_t *archer)
{
    sfIntRect info = {INTER_WIDTH, INTER_HEIGHT, 14, 2};

    update_clock_seconds(archer->inter->anim->myclock);
    if (archer->inter->anim->myclock->seconds > 0.02) {
        anim_mark(archer->inter, &info);
    }
}

void anim_archer(rpg_t *rpg, entity_t *entity)
{
    update_clock_seconds(entity->common->anim->myclock);
    if (is_dead(entity))
        animation_death(entity->common);
    else if (!is_stunned(entity))
        animation_archer(rpg, entity);
    if (entity->spe->archer->exclam->is_display == 1)
        anim_exclam(entity->spe->archer);
    if (entity->spe->archer->inter->is_display == 1)
        anim_inter(entity->spe->archer);
}
