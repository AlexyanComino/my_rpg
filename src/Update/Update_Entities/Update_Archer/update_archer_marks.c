/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_archer_marks
*/

#include "rpg.h"

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
        return (sfVector2f){entity->common->pos.x + ARCHER_WIDTH / 4 *
            entity->common->scale,
            entity->common->pos.y - ARCHER_WIDTH / 3 * entity->common->scale};
    } else {
        return (sfVector2f){entity->common->pos.x - ARCHER_WIDTH / 4 *
            entity->common->scale,
            entity->common->pos.y - ARCHER_WIDTH / 3 * entity->common->scale};
    }
}

static void update_exclam_pos(entity_t *entity)
{
    entity->spe->archer->exclam->pos = get_mark_pos(entity);
    sfSprite_setPosition(entity->spe->archer->exclam->anim->sprite,
        entity->spe->archer->exclam->pos);
}

static void update_inter_pos(entity_t *entity)
{
    entity->spe->archer->inter->pos = get_mark_pos(entity);
    sfSprite_setPosition(entity->spe->archer->inter->anim->sprite,
        entity->spe->archer->inter->pos);
}

static void update_exclam_mark(entity_t *entity)
{
    if (entity->common->zones->s_detect) {
        if (entity->spe->archer->exclam->is_display == 0) {
            entity->spe->archer->exclam->is_display = 1;
            entity->spe->archer->exclam->anim->rect.left = 0;
            entity->spe->archer->exclam->anim->rect.top = 0;
            update_exclam_pos(entity);
        }
    } else {
        update_clock_seconds(entity->spe->archer->exclam->anim->myclock);
        if (entity->spe->archer->exclam->is_display == 2 &&
            cooldown_is_over(entity->spe->archer->exclam, EXCLAM_COOLDOWN))
            entity->spe->archer->exclam->is_display = 0;
    }
}

static void update_inter_mark(entity_t *entity)
{
    update_clock_seconds(entity->spe->archer->inter->anim->myclock);
    if (entity->common->zones->m_detect) {
        if (entity->spe->archer->inter->is_display == 0 ||
            (entity->spe->archer->inter->is_display == 2 &&
            cooldown_is_over(entity->spe->archer->inter, INTER_INTERVAL))) {
            entity->spe->archer->inter->is_display = 1;
            entity->spe->archer->inter->anim->rect.left = 0;
            entity->spe->archer->inter->anim->rect.top = 0;
            update_inter_pos(entity);
        }
    } else {
        if (entity->spe->archer->inter->is_display == 2 &&
            cooldown_is_over(entity->spe->archer->inter, INTER_COOLDOWN))
            entity->spe->archer->inter->is_display = 0;
    }
}

void update_archer_marks(entity_t *entity)
{
    update_exclam_mark(entity);
    update_inter_mark(entity);
}
