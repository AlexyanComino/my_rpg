/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_torch
*/

#include "rpg.h"

static void update_torch_pos(rpg_t *rpg, entity_t *entity, entity_t *enemy)
{
    float min_lenght = MIN_TORCH_LENGTH;
    sfVector2f target_pos;

    if (enemy && entity_see_enemy(rpg, entity, enemy)) {
        target_pos = enemy->common->pos;
        entity->common->state = RUN;
        entity->common->x = get_entity_side(entity, enemy->common->pos);
        entity_move(rpg, entity, target_pos, min_lenght);
    } else if (get_distance(entity->common->pos,
        entity->common->init_pos) > 10) {
        entity->common->state = WALK;
        min_lenght = 10;
        target_pos = entity->common->init_pos;
        entity_move(rpg, entity, entity->common->init_pos, min_lenght);
    } else {
        entity->common->state = IDLE;
    }
}

static void update_gob_exclam_pos(entity_t *entity)
{
    entity->spe->torch->exclam->pos = entity->common->pos;
    sfSprite_setPosition(entity->spe->torch->exclam->anim->sprite,
        entity->spe->torch->exclam->pos);
}

static void update_gob_exclam_mark(entity_t *entity)
{
    if (entity->common->zones->m_detect || entity->common->zones->s_detect) {
        if (entity->spe->torch->exclam->is_display == 0) {
            entity->spe->torch->exclam->is_display = 1;
            entity->spe->torch->exclam->anim->rect.left = 0;
            entity->spe->torch->exclam->anim->rect.top = 0;
            update_gob_exclam_pos(entity);
        }
    } else {
        update_clock_seconds(entity->spe->torch->exclam->anim->myclock);
        if (entity->spe->torch->exclam->is_display == 2 &&
            cooldown_is_over(entity->spe->torch->exclam, EXCLAM_COOLDOWN))
            entity->spe->torch->exclam->is_display = 0;
    }
}

static void update_pnj_torch(rpg_t *rpg, entity_t *entity)
{
    entity_t *enemy = get_nearest_entity(rpg, entity, false);

    if (is_stunned(entity))
        return;
    if (!is_attacking(entity))
        update_torch_pos(rpg, entity, enemy);
    update_gob_exclam_mark(entity);
    if (enemy == NULL)
        return;
    if (entity_can_attack(rpg, entity, enemy)) {
        entity->common->state = ST_ATT;
        init_entity_action(entity);
    }
}

void update_torch(rpg_t *rpg, entity_t *entity)
{
    update_common(rpg, entity);
    if (entity->common->state == RIEN)
        return;
    entity->anim(rpg, entity);
    if (!is_player(rpg, entity) && is_alive(entity))
        update_pnj_torch(rpg, entity);
}
