/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_pnj_tnt
*/

#include "rpg.h"

static void update_tnt_pos(rpg_t *rpg, entity_t *entity, entity_t *enemy)
{
    float min_lenght = MIN_TNT_LENGTH;
    sfVector2f target_pos;

    if (enemy && flee_entity(rpg, entity, enemy))
        return;
    if (enemy && entity->common->zones->m_detect) {
        target_pos = enemy->common->pos;
        entity->common->state = RUN;
        entity->common->x = get_entity_side(entity, enemy->common->pos);
        entity_move(rpg, entity, target_pos, min_lenght);
    } else if (get_distance(entity->common->pos,
        entity->common->init_pos) > 10) {
        min_lenght = 10;
        target_pos = entity->common->init_pos;
        entity->common->state = WALK;
        entity->common->x = get_entity_side(entity, target_pos);
        entity_move(rpg, entity, target_pos, min_lenght);
    } else {
        entity->common->state = IDLE;
    }
}

static bool tnt_can_attack_target(entity_t *entity, entity_t *enemy)
{
    if (enemy == NULL)
        return false;
    if (hitbox_in_detection(enemy->common->zones->hitbox,
        entity->spe->tnt->explo->radius,
        entity->spe->tnt->explo->boom_center))
        return true;
    return false;
}

static bool tnt_can_attack(entity_t *entity, entity_t *target)
{
    update_clock_seconds(entity->common->clock_cooldown_attack);
    if (entity->common->clock_cooldown_attack->seconds >
        entity->common->attack_cooldown) {
        if ((entity->common->state == IDLE || entity->common->state == WALK ||
            entity->common->state == RUN) &&
            tnt_can_attack_target(entity, target) &&
            is_alive(target)) {
            return true;
        }
    }
    return false;
}

static void update_tnt_side_y(entity_t *entity, entity_t *enemy)
{
    float diff_y = 0;

    if (!enemy || !entity->common->zones->m_detect)
        return;
    diff_y = enemy->common->pos.y - entity->common->pos.y;
    if (diff_y > 115)
        entity->common->y = DOWN;
    else if (diff_y < -115)
        entity->common->y = UP;
    else
        entity->common->y = NONE;
}

void update_pnj_tnt(rpg_t *rpg, entity_t *entity)
{
    entity_t *enemy = get_nearest_entity(rpg, entity, false);

    if (is_stunned(entity) || entity->spe->tnt->is_launched)
        return;
    if (!is_attacking(entity))
        update_tnt_side_y(entity, enemy);
    if (!is_attacking(entity))
        update_tnt_pos(rpg, entity, enemy);
    if (!enemy)
        return;
    if (tnt_can_attack(entity, enemy)) {
        entity->common->state = ST_ATT;
        init_entity_action(entity);
    }
}
