/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_warrior_pos
*/

#include "rpg.h"

x_warrior_t get_warrior_side(warrior_t *warrior, warrior_t *enemy)
{
    if (warrior->pos.x < enemy->pos.x)
        return LEFT;
    return RIGHT;
}

static bool warrior_can_move(warrior_t *warrior)
{
    if ((warrior->state == IDLE || warrior->state == WALK ||
        warrior->state == RUN))
        return true;
    return false;
}

static bool enemy_is_in_base(warrior_t *warrior, warrior_t *enemy)
{
    if (WARRIOR_HAS_BASE(warrior) &&
        sfIntRect_intersects(&enemy->zones->hitbox, &warrior->base->rect,
        NULL))
        return true;
    return false;
}

static void update_base_cooldown(warrior_t *warrior)
{
    if (!WARRIOR_HAS_BASE(warrior))
        return;
    update_clock_seconds(warrior->base->myclock);
    if (warrior->base->in_cooldown && warrior->base->myclock->seconds >
        warrior->base->cooldown) {
        warrior->base->in_cooldown = false;
        warrior->base->pattern_pos_index =
        (warrior->base->pattern_pos_index + 1) % warrior->base->max_pos_index;
    }
}

static void come_back_to_next_point(rpg_t *rpg, warrior_t *warrior,
    warrior_t *enemy)
{
    if (!WARRIOR_HAS_BASE(warrior))
        return;
    if (!enemy) {
        warrior->base->come_back = true;
        return;
    }
    if (!warrior_see_enemy(rpg, warrior, enemy))
        warrior->base->come_back = true;
    else
        warrior->base->come_back = false;
}

static void update_warrior_side(rpg_t *rpg, warrior_t *warrior,
    warrior_t *enemy)
{
    if (warrior_see_enemy(rpg, warrior, enemy) && warrior->state != ATTACK &&
        !is_discreet(enemy))
        warrior->x = get_warrior_side(enemy, warrior);
}

static void normal_move(rpg_t *rpg, warrior_t *tmp, warrior_t *enemy)
{
    if (tmp->exclam->is_detecting)
        tmp->state = RUN;
    else if ((warrior_see_enemy(rpg, tmp, enemy) &&
        enemy_is_in_base(tmp, enemy)) ||
        ((WARRIOR_HAS_BASE(tmp) && tmp->base->come_back)))
        tmp->state = WALK;
    warrior_move(rpg, tmp);
}

void update_warrior_pos(rpg_t *rpg, warrior_t *tmp, warrior_t *enemy)
{
    come_back_to_next_point(rpg, tmp, enemy);
    update_base_cooldown(tmp);
    if (!enemy && WARRIOR_HAS_BASE(tmp) && tmp->base->come_back) {
        tmp->state = WALK;
        warrior_move(rpg, tmp);
        return;
    }
    if ((!enemy_is_in_base(tmp, enemy) && warrior_see_enemy(rpg, tmp, enemy))
        || (enemy_is_in_base(tmp, enemy) && !warrior_see_enemy(rpg, tmp, enemy)
        && !tmp->base->come_back)) {
        tmp->state = IDLE;
        return;
    }
    update_warrior_side(rpg, tmp, enemy);
    if (warrior_can_move(tmp))
        normal_move(rpg, tmp, enemy);
}
