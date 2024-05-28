/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** *
*/

#include "rpg.h"

static sfVector2f get_mark_pos(entity_t *entity)
{
    if (entity->common->x == RIGHT) {
        return (sfVector2f){entity->common->pos.x + WARRIOR_WIDTH / 4 *
            entity->common->scale,
            entity->common->pos.y - WARRIOR_WIDTH / 3 * entity->common->scale};
    } else {
        return (sfVector2f){entity->common->pos.x - WARRIOR_WIDTH / 4 *
            entity->common->scale,
            entity->common->pos.y - WARRIOR_WIDTH / 3 * entity->common->scale};
    }
}

static void update_exclam_pos(entity_t *entity)
{
    entity->spe->warrior->exclam->pos = get_mark_pos(entity);
    sfSprite_setPosition(entity->spe->warrior->exclam->anim->sprite,
        entity->spe->warrior->exclam->pos);
}

static void update_inter_pos(entity_t *entity)
{
    entity->spe->warrior->inter->pos = get_mark_pos(entity);
    sfSprite_setPosition(entity->spe->warrior->inter->anim->sprite,
        entity->spe->warrior->inter->pos);
}

static void update_exclam_mark(entity_t *entity)
{
    if (entity->common->zones->s_detect) {
        if (entity->spe->warrior->exclam->is_display == 0) {
            entity->spe->warrior->exclam->is_display = 1;
            entity->spe->warrior->exclam->anim->rect.left = 0;
            entity->spe->warrior->exclam->anim->rect.top = 0;
            update_exclam_pos(entity);
        }
    } else {
        update_clock_seconds(entity->spe->warrior->exclam->anim->myclock);
        if (entity->spe->warrior->exclam->is_display == 2 &&
            cooldown_is_over(entity->spe->warrior->exclam, EXCLAM_COOLDOWN))
            entity->spe->warrior->exclam->is_display = 0;
    }
}

static void update_inter_mark(entity_t *entity)
{
    update_clock_seconds(entity->spe->warrior->inter->anim->myclock);
    if (entity->common->zones->m_detect) {
        if (entity->spe->warrior->inter->is_display == 0 ||
            (entity->spe->warrior->inter->is_display == 2 &&
            cooldown_is_over(entity->spe->warrior->inter, INTER_INTERVAL))) {
            entity->spe->warrior->inter->is_display = 1;
            entity->spe->warrior->inter->anim->rect.left = 0;
            entity->spe->warrior->inter->anim->rect.top = 0;
            update_inter_pos(entity);
        }
    } else {
        if (entity->spe->warrior->inter->is_display == 2 &&
            cooldown_is_over(entity->spe->warrior->inter, INTER_COOLDOWN))
            entity->spe->warrior->inter->is_display = 0;
    }
}

void update_warrior_marks(entity_t *entity)
{
    update_exclam_mark(entity);
    update_inter_mark(entity);
}
