/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** classic_anim_warrior
*/

#include "rpg.h"

static void animation_idle_walk_run(warrior_t *warrior)
{
    float interval = warrior->state == WALK ? 0.14 : 0.1;

    if (warrior->myclock->seconds > interval) {
        if (warrior->rect.left >= WARRIOR_OFFSET)
            warrior->rect.left = 0;
        else
            warrior->rect.left += WARRIOR_WIDTH;
        sfSprite_setTextureRect(warrior->sprite, warrior->rect);
        sfClock_restart(warrior->myclock->clock);
    }
}

static void reset_attack(warrior_t *warrior)
{
    warrior->state = IDLE;
    warrior->rect.top = 0;
    warrior->rect.left = 0;
    warrior->line_attack = 0;
    sfClock_restart(warrior->clock_cooldown_attack->clock);
}

static void animation_attack2(rpg_t *rpg, warrior_t *warrior)
{
    if (warrior->rect.left == WARRIOR_WIDTH * 3)
        warrior_attack(rpg, warrior);
    if (warrior->rect.left >= WARRIOR_OFFSET && warrior->line_attack == 0) {
        if (warrior->line_attack < warrior->max_line_attack ||
            (IS_PLAYER(rpg, warrior) && sfMouse_isButtonPressed(sfMouseLeft))
            || (!IS_PLAYER(rpg, warrior) &&
            warrior_can_attack_enemy(rpg, warrior))) {
            warrior->line_attack++;
            warrior->rect.left = 0;
            warrior->rect.top += WARRIOR_WIDTH;
        } else {
            reset_attack(warrior);
        }
    } else if (warrior->rect.left >= WARRIOR_OFFSET &&
        warrior->line_attack == 1) {
        reset_attack(warrior);
    } else
        warrior->rect.left += WARRIOR_WIDTH;
}

static void animation_attack(rpg_t *rpg, warrior_t *warrior)
{
    if (warrior->myclock->seconds > 0.1) {
        animation_attack2(rpg, warrior);
        sfSprite_setTextureRect(warrior->sprite, warrior->rect);
        sfClock_restart(warrior->myclock->clock);
    }
}

void animation_alive(rpg_t *rpg, warrior_t *warrior)
{
    if (warrior->state == IDLE) {
        warrior->rect.top = 0;
        animation_idle_walk_run(warrior);
    }
    if (warrior->state == WALK || warrior->state == RUN) {
        warrior->rect.top = WARRIOR_WIDTH;
        animation_idle_walk_run(warrior);
    }
    if (warrior->state == ATTACK)
        animation_attack(rpg, warrior);
}

static void reset_warrior(warrior_t *warrior)
{
    warrior->death->rect_dead.left = 0;
    warrior->death->rect_dead.top = 0;
    warrior->death->number_dead = 0;
    warrior->attributes->health = warrior->attributes->max_health;
    warrior->state = IDLE;
}

static void animation_dead3(warrior_t *warrior, bool time_elapsed)
{
    if (warrior->death->number_dead == 1 && time_elapsed) {
        warrior->death->rect_dead.left = 0;
        warrior->death->rect_dead.top = DEAD_WIDTH;
        warrior->death->number_dead = 2;
    } else if (warrior->death->number_dead == 2 &&
        warrior->death->rect_dead.left >= DEAD_WIDTH * 6) {
        reset_warrior(warrior);
    } else {
        warrior->death->rect_dead.left += DEAD_WIDTH;
    }
}

static void animation_dead2(warrior_t *warrior)
{
    bool time_elapsed = warrior->death->clock_dead->seconds > DEAD_COOLDOWN;

    if (warrior->death->number_dead == 0 &&
        warrior->death->rect_dead.left >= DEAD_WIDTH * 6) {
        warrior->death->number_dead = 1;
        sfClock_restart(warrior->death->clock_dead->clock);
    } else if (warrior->death->number_dead == 1 && !time_elapsed) {
        warrior->death->rect_dead.left = DEAD_WIDTH * 6;
    } else
        animation_dead3(warrior, time_elapsed);
}

void animation_dead(warrior_t *warrior)
{
    update_clock_seconds(warrior->death->clock_dead);
    if (warrior->myclock->seconds > 0.1) {
        animation_dead2(warrior);
        sfSprite_setTextureRect(warrior->death->sprite_dead,
            warrior->death->rect_dead);
        sfClock_restart(warrior->myclock->clock);
    }
}
