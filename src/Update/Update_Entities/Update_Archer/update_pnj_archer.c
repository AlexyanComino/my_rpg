/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_pnj_archer
*/

#include "rpg.h"

static sfVector2f get_vector_positions(sfVector2f pos1, sfVector2f pos2)
{
    sfVector2f vector;

    vector.x = (pos1.x < pos2.x) ? 1 : -1;
    vector.y = (pos1.y < pos2.y) ? 1 : -1;
    return vector;
}

static arrow_dir_t get_arrow_dir(sfVector2f vector)
{
    if (vector.x == 1 && vector.y == 1)
        return DOWN_RIGHT_ARROW;
    if (vector.x == 1 && vector.y == -1)
        return UP_RIGHT_ARROW;
    if (vector.x == -1 && vector.y == 1)
        return DOWN_LEFT_ARROW;
    if (vector.x == -1 && vector.y == -1)
        return UP_LEFT_ARROW;
    return RIGHT_ARROW;
}

static bool check_diagonal(entity_t *entity, entity_t *enemy)
{
    sfVector2f vector = get_vector_positions(entity->common->pos,
        enemy->common->pos);
    sfVector2f current_pos = entity->common->pos;

    while (get_distance(current_pos, entity->common->pos) <
        entity->common->zones->l_radius) {
        current_pos.x += vector.x;
        current_pos.y += vector.y;
        if (sfIntRect_contains(&enemy->common->zones->hitbox,
            current_pos.x, current_pos.y)) {
            entity->spe->archer->arrow_dir = get_arrow_dir(vector);
            return true;
        }
    }
    return false;
}

static bool archer_can_attack_target(entity_t *entity, entity_t *enemy)
{
    if (!enemy)
        return false;
    if (entity->common->pos.y >= enemy->common->zones->hitbox.top &&
        entity->common->pos.y <= enemy->common->zones->hitbox.top +
        enemy->common->zones->hitbox.height) {
        entity->spe->archer->arrow_dir = (entity->common->pos.x <
            enemy->common->pos.x) ? RIGHT_ARROW : LEFT_ARROW;
        return true;
    }
    if (entity->common->pos.x >= enemy->common->zones->hitbox.left &&
        entity->common->pos.x <= enemy->common->zones->hitbox.left +
        enemy->common->zones->hitbox.width) {
        entity->spe->archer->arrow_dir = (entity->common->pos.y <
            enemy->common->pos.y) ? DOWN_ARROW : UP_ARROW;
        return true;
    }
    return check_diagonal(entity, enemy);
}

static bool archer_can_attack(entity_t *entity, entity_t *target)
{
    if (!entity->common->zones->m_detect && !entity->common->zones->s_detect)
        return false;
    update_clock_seconds(entity->common->clock_cooldown_attack);
    if (entity->common->clock_cooldown_attack->seconds >
        entity->common->attack_cooldown) {
        if ((entity->common->state == IDLE || entity->common->state == WALK ||
            entity->common->state == RUN) &&
            archer_can_attack_target(entity, target) &&
            is_alive(target) && (!entity_has_base(entity) ||
            enemy_is_in_base(entity, target))) {
            return true;
        }
    }
    return false;
}

void update_pnj_archer(rpg_t *rpg, entity_t *entity)
{
    entity_t *enemy = get_nearest_entity(rpg, entity, false);

    if (is_stunned(entity))
        return;
    if (!is_attacking(entity))
        update_archer_pos(rpg, entity, enemy);
    if (!enemy)
        return;
    update_archer_marks(entity);
    if (archer_can_attack(entity, enemy)) {
        entity->common->x = get_entity_side(entity, enemy->common->pos);
        entity->common->state = ST_ATT;
        init_entity_action(entity);
    }
}
