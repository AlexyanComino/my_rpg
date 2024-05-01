/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_pnj_warrior
*/

#include "rpg.h"

static bool entity_can_attack(entity_t *entity, entity_t *target)
{
    update_clock_seconds(entity->common->clock_cooldown_attack);
    if (entity->common->clock_cooldown_attack->seconds >
        entity->common->attack_cooldown) {
        if ((entity->common->state == IDLE || entity->common->state == WALK ||
            entity->common->state == RUN) &&
            entity_can_attack_target(entity, target) &&
            is_alive(target)) {
            return true;
        }
    }
    return false;
}

void update_warrior_attack_rect(entity_t *entity)
{
    if (entity->common->y == NONE)
        entity->common->anim->rect.top = WARRIOR_WIDTH * 2;
    if (entity->common->y == DOWN)
        entity->common->anim->rect.top = WARRIOR_WIDTH * 4;
    if (entity->common->y == UP)
        entity->common->anim->rect.top = WARRIOR_WIDTH * 6;
}

void update_pnj_warrior(rpg_t *rpg, entity_t *tmp)
{
    entity_t *enemy = get_nearest_entity(rpg, tmp, false);

    if (not_attacking(tmp))
        update_warrior_pos(rpg, tmp, enemy);
    if (enemy == NULL)
        return;
    update_warrior_marks(tmp);
    if (entity_can_attack(tmp, enemy)) {
        tmp->common->state = ST_ATT;
        tmp->common->anim->rect.left = 0;
        update_warrior_attack_rect(tmp);
    } else if (!is_alive(enemy)) {
        tmp->common->state = IDLE;
    }
}
