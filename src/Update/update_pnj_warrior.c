/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_pnj_warrior
*/

#include "rpg.h"

x_warrior_t get_warrior_side(warrior_t *warrior, warrior_t *enemy)
{
    if (warrior->pos.x < enemy->pos.x)
        return LEFT;
    return RIGHT;
}

static sfVector2f get_exclam_pos(warrior_t *warrior)
{
    if (warrior->x == RIGHT) {
        return (sfVector2f){warrior->pos.x + WARRIOR_WIDTH / 4, warrior->pos.y - WARRIOR_WIDTH / 3};
    } else {
        return (sfVector2f){warrior->pos.x - WARRIOR_WIDTH / 4, warrior->pos.y - WARRIOR_WIDTH / 3};
    }
}

static sfVector2f get_inter_pos(warrior_t *warrior)
{
    if (warrior->x == RIGHT)
        return (sfVector2f){warrior->pos.x + WARRIOR_WIDTH / 4, warrior->pos.y - WARRIOR_WIDTH / 3};
    else
        return (sfVector2f){warrior->pos.x - WARRIOR_WIDTH / 4, warrior->pos.y - WARRIOR_WIDTH / 3};
}

static void update_exclam_pos(warrior_t *warrior)
{
    warrior->exclam->pos = get_exclam_pos(warrior);
    sfSprite_setPosition(warrior->exclam->sprite, warrior->exclam->pos);
}

static void update_inter_pos(warrior_t *warrior)
{
    warrior->inter->pos = get_inter_pos(warrior);
    sfSprite_setPosition(warrior->inter->sprite, warrior->inter->pos);
}

static bool enemy_is_in_exclamation_range(warrior_t *warrior, warrior_t *enemy)
{
    if (enemy == NULL)
        return false;
    if (!warrior_look_at_enemy(warrior, enemy) && IS_DISCREET(enemy))
        return false;
    if (hitbox_in_detection(enemy->zones->hitbox, warrior->exclam->radius,
        warrior->pos))
        return true;
    return false;
}

static bool cooldown_is_over(mark_t *mark, float cooldown)
{
    return mark->myclock->seconds > cooldown;
}

static void update_warrior_detection(warrior_t *warrior, warrior_t *enemy)
{
    bool in_base = WARRIOR_HAS_BASE(warrior) && sfIntRect_intersects(&warrior->base->rect, &enemy->zones->hitbox, NULL);

    if (!in_base && !WARRIOR_HAS_BASE(warrior))
        in_base = true;
    if (enemy_is_in_exclamation_range(warrior, enemy) && in_base) {
        warrior->exclam->is_detecting = true;
        if (warrior->exclam->is_display == 0) {
            warrior->exclam->is_display = 1;
            warrior->exclam->rect.left = 0;
            warrior->exclam->rect.top = 0;
            update_exclam_pos(warrior);
        }
    } else {
        update_clock_seconds(warrior->exclam->myclock);
        warrior->exclam->is_detecting = false;
        if (warrior->exclam->is_display == 2 && cooldown_is_over(warrior->exclam, EXCLAM_COOLDOWN))
            warrior->exclam->is_display = 0;
    }
    update_clock_seconds(warrior->inter->myclock);
    if (warrior_see_enemy(warrior, enemy)) {
        warrior->inter->is_detecting = true;
        if (warrior->inter->is_display == 0 || (warrior->inter->is_display == 2 && cooldown_is_over(warrior->inter, INTER_INTERVAL) && (!enemy_is_in_exclamation_range(warrior, enemy) || !in_base))) {
            warrior->inter->is_display = 1;
            warrior->inter->rect.left = 0;
            warrior->inter->rect.top = 0;
            update_inter_pos(warrior);
        }
    } else {
        warrior->inter->is_detecting = false;
        if (warrior->inter->is_display == 2 && cooldown_is_over(warrior->inter, INTER_COOLDOWN))
            warrior->inter->is_display = 0;
    }
}

static bool warrior_can_move(warrior_t *warrior)
{
    if ((warrior->state == IDLE || warrior->state == WALK || warrior->state == RUN))
        return true;
    return false;
        
}

static bool warrior_can_attack(warrior_t *warrior, warrior_t *target)
{
    update_clock_seconds(warrior->clock_cooldown_attack);
    if (warrior->clock_cooldown_attack->seconds > warrior->attack_cooldown) {
        if ((warrior->state == IDLE || warrior->state == WALK) &&
            warrior_can_attack_target(warrior, target) &&
            IS_ALIVE(target)) {
            return true;
        }
    }
    return false;
}

static bool enemy_is_in_base(warrior_t *warrior, warrior_t *enemy)
{
    if (WARRIOR_HAS_BASE(warrior) && sfIntRect_intersects(&enemy->zones->hitbox, &warrior->base->rect, NULL))
        return true;
    return false;
}

static void update_base_cooldown(warrior_t *warrior)
{
    if (!WARRIOR_HAS_BASE(warrior))
        return;
    update_clock_seconds(warrior->base->myclock);
    if (warrior->base->in_cooldown && warrior->base->myclock->seconds > warrior->base->cooldown) {
        warrior->base->in_cooldown = false;
        warrior->base->pattern_pos_index = (warrior->base->pattern_pos_index + 1) % warrior->base->max_pos_index;
    }
}

static void come_back_to_next_point(warrior_t *warrior, warrior_t *enemy)
{
    if (!WARRIOR_HAS_BASE(warrior))
        return;
    if (!enemy) {
        warrior->base->come_back = true;
        return;
    }
    if (!warrior_see_enemy(warrior, enemy))
        warrior->base->come_back = true;
    else
        warrior->base->come_back = false;
}

static void update_warrior_side(warrior_t *warrior, warrior_t *enemy)
{
    if (warrior_see_enemy(warrior, enemy) && warrior->state != ATTACK && enemy->state != WALK)
        warrior->x = get_warrior_side(enemy, warrior);
}

static void update_warrior_pos(rpg_t *rpg, warrior_t *tmp, warrior_t *enemy)
{
    come_back_to_next_point(tmp, enemy);
    update_base_cooldown(tmp);
    if (!enemy && WARRIOR_HAS_BASE(tmp) && tmp->base->come_back) {
        tmp->state = WALK;
        warrior_move(rpg, tmp);
        return;
    }
    update_warrior_side(tmp, enemy);
    if ((!enemy_is_in_base(tmp, enemy) && warrior_see_enemy(tmp, enemy)) || (enemy_is_in_base(tmp, enemy) && !warrior_see_enemy(tmp, enemy) && !tmp->base->come_back)) {
        tmp->state = IDLE;
        return;
    }
    if (!warrior_can_move(tmp))
        return;
    if (tmp->exclam->is_detecting)
        tmp->state = RUN;
    else if ((warrior_see_enemy(tmp, enemy) && enemy_is_in_base(tmp, enemy)) || ((WARRIOR_HAS_BASE(tmp) && tmp->base->come_back)))
        tmp->state = WALK;
    warrior_move(rpg, tmp);
}

void update_pnj_warrior(rpg_t *rpg, warrior_t *tmp)
{
    warrior_t *enemy = get_nearest_warrior(rpg, tmp);

    if (tmp->state != ATTACK)
        update_warrior_pos(rpg, tmp, enemy);
    if (enemy == NULL)
        return;
    update_warrior_detection(tmp, enemy);
    if (warrior_can_attack(tmp, enemy)) {
        tmp->state = ATTACK;
        tmp->rect.left = 0;
        update_attack_rect(tmp);
    } else if (!IS_ALIVE(enemy)) {
        tmp->state = IDLE;
    }
}
