/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_warrior_pos
*/

#include "rpg.h"

static bool entity_can_move(entity_t *entity)
{
    if ((entity->common->state == IDLE || entity->common->state == WALK ||
        entity->common->state == RUN))
        return true;
    return false;
}

static void update_base_cooldown(entity_t *entity)
{
    update_clock_seconds(entity->spe->warrior->base->myclock);
    if (entity->spe->warrior->base->in_cooldown &&
        entity->spe->warrior->base->myclock->seconds >
        entity->spe->warrior->base->cooldown) {
        entity->spe->warrior->base->in_cooldown = false;
        entity->spe->warrior->base->pattern_pos_index =
        (entity->spe->warrior->base->pattern_pos_index + 1) %
        entity->spe->warrior->base->max_pos_index;
    }
}

static void come_back_to_next_point(rpg_t *rpg, entity_t *tmp,
    entity_t *enemy)
{
    if (!enemy) {
        tmp->spe->warrior->base->come_back = true;
        return;
    }
    if (!entity_see_enemy(rpg, tmp, enemy))
        tmp->spe->warrior->base->come_back = true;
    else
        tmp->spe->warrior->base->come_back = false;
}

static void update_warrior_side(rpg_t *rpg, entity_t *tmp, entity_t *enemy)
{
    if (entity_see_enemy(rpg, tmp, enemy) && tmp->common->state != ATTACK &&
        !is_discreet(enemy))
        tmp->common->x = get_entity_side(tmp, enemy->common->pos);
}

static void defend_base(rpg_t *rpg, entity_t *tmp, entity_t *enemy)
{
    sfVector2f target_pos = enemy->common->pos;
    float min_lenght = MIN_WARRIOR_LENGTH;

    if (tmp->common->zones->s_detect)
        tmp->common->state = RUN;
    else
        tmp->common->state = WALK;
    entity_move(rpg, tmp, target_pos, min_lenght);
}

static void warrior_come_back(rpg_t *rpg, entity_t *tmp)
{
    float min_lenght = 10;
    sfVector2f target_pos = tmp->spe->warrior->base->pattern_pos[tmp->spe->
        warrior->base->pattern_pos_index];

    tmp->common->state = WALK;
    entity_move(rpg, tmp, target_pos, min_lenght);
}

static void move_warrior_base(rpg_t *rpg, entity_t *tmp, entity_t *enemy)
{
    come_back_to_next_point(rpg, tmp, enemy);
    update_base_cooldown(tmp);
    if ((!enemy_is_in_base(tmp, enemy) && entity_see_enemy(rpg, tmp, enemy))
        || (enemy_is_in_base(tmp, enemy) && !entity_see_enemy(rpg, tmp, enemy)
        && !tmp->spe->warrior->base->come_back)) {
        tmp->common->state = IDLE;
        return;
    }
    if ((entity_see_enemy(rpg, tmp, enemy) &&
        enemy_is_in_base(tmp, enemy)))
        return defend_base(rpg, tmp, enemy);
    update_warrior_side(rpg, tmp, enemy);
    if (tmp->spe->warrior->base->in_cooldown) {
        tmp->common->state = IDLE;
        return;
    }
    if (entity_can_move(tmp))
        warrior_come_back(rpg, tmp);
}

static void move_warrior_no_base(rpg_t *rpg, entity_t *tmp, entity_t *enemy)
{
    float min_lenght = 0;
    sfVector2f target_pos;

    if (!enemy || !entity_see_enemy(rpg, tmp, enemy)) {
        tmp->common->state = IDLE;
        return;
    }
    update_warrior_side(rpg, tmp, enemy);
    if (tmp->common->zones->s_detect)
        tmp->common->state = RUN;
    else
        tmp->common->state = WALK;
    target_pos = enemy->common->pos;
    min_lenght = MIN_WARRIOR_LENGTH;
    entity_move(rpg, tmp, target_pos, min_lenght);
}

void update_warrior_pos(rpg_t *rpg, entity_t *tmp, entity_t *enemy)
{
    if (entity_has_base(tmp))
        move_warrior_base(rpg, tmp, enemy);
    else
        move_warrior_no_base(rpg, tmp, enemy);
}
