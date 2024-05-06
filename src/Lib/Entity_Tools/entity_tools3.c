/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** entity_tools3
*/

#include "rpg.h"

bool entity_can_attack_target(rpg_t *rpg, entity_t *entity, entity_t *target)
{
    sfIntRect hitbox_attack = entity->common->zones->hitbox_attack;
    sfIntRect hitbox = target->common->zones->hitbox;

    if (!is_player(rpg, entity) && !entity_look_at_enemy(entity, target))
        return false;
    if (sfIntRect_intersects(&hitbox_attack, &hitbox, NULL))
        return true;
    return false;
}

bool entity_can_attack(rpg_t *rpg, entity_t *entity, entity_t *target)
{
    update_clock_seconds(entity->common->clock_cooldown_attack);
    if (entity->common->clock_cooldown_attack->seconds >
        entity->common->attack_cooldown) {
        if ((entity->common->state == IDLE || entity->common->state == WALK ||
            entity->common->state == RUN) &&
            entity_can_attack_target(rpg, entity, target) &&
            is_alive(target)) {
            return true;
        }
    }
    return false;
}

side_x_t get_entity_side(entity_t *entity, sfVector2f objectif_pos)
{
    if (entity->common->pos.x < objectif_pos.x)
        return RIGHT;
    return LEFT;
}
