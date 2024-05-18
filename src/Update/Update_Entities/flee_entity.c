/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** flee_entity
*/

#include "rpg.h"

static sfVector2f get_flee_pos(entity_t *entity, entity_t *enemy)
{
    sfVector2f diff = {enemy->common->pos.x - entity->common->pos.x,
        enemy->common->pos.y - entity->common->pos.y};

    return (sfVector2f){entity->common->pos.x - diff.x,
        entity->common->pos.y - diff.y};
}

static void update_is_fleeing(entity_t *entity, entity_t *enemy)
{
    if (entity->common->zones->s_detect && !entity->common->is_fleeing)
        entity->common->is_fleeing = true;
    else if (entity->common->is_fleeing &&
        !hitbox_in_detection(enemy->common->zones->hitbox,
        entity->common->zones->s_radius, entity->common->pos)) {
        entity->common->is_fleeing = false;
        entity->common->x = get_entity_side(entity, enemy->common->pos);
    }
}

bool flee_entity(rpg_t *rpg, entity_t *entity, entity_t *enemy)
{
    float min_lenght;
    sfVector2f target_pos;
    sfVector2f old = entity->common->pos;

    update_is_fleeing(entity, enemy);
    if (entity->common->is_fleeing) {
        min_lenght = 10;
        target_pos = get_flee_pos(entity, enemy);
        entity->common->state = RUN;
        entity_move(rpg, entity, target_pos, min_lenght);
        if (old.x == entity->common->pos.x && old.y == entity->common->pos.y)
            entity->common->x = get_entity_side(entity, enemy->common->pos);
        return true;
    }
    return false;
}
