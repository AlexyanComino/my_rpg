/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** anim_warrior
*/

#include "rpg.h"

static void animation_idle_walk(warrior_t *warrior)
{
    if (warrior->myclock->seconds > 0.1) {
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
}

static void animation_attack2(warrior_t *warrior)
{
    if (warrior->rect.left >= WARRIOR_OFFSET && warrior->line_attack == 0) {
        if (warrior->line_attack < warrior->max_line_attack ||
            sfMouse_isButtonPressed(sfMouseLeft)) {
            warrior->line_attack++;
            warrior->rect.left = 0;
            warrior->rect.top += WARRIOR_WIDTH;
        } else
            reset_attack(warrior);
    } else if (warrior->rect.left >= WARRIOR_OFFSET &&
        warrior->line_attack == 1) {
        reset_attack(warrior);
    } else
        warrior->rect.left += WARRIOR_WIDTH;
}

static void animation_attack(warrior_t *warrior)
{
    if (warrior->myclock->seconds > 0.1) {
        animation_attack2(warrior);
        sfSprite_setTextureRect(warrior->sprite, warrior->rect);
        sfClock_restart(warrior->myclock->clock);
    }
}

static void animation_alive(warrior_t *warrior)
{
    warrior->myclock->time = sfClock_getElapsedTime(warrior->myclock->clock);
    warrior->myclock->seconds =
        warrior->myclock->time.microseconds / 1000000.0;
    if (warrior->state == IDLE) {
        warrior->rect.top = 0;
        animation_idle_walk(warrior);
    }
    if (warrior->state == WALK) {
        warrior->rect.top = WARRIOR_WIDTH;
        animation_idle_walk(warrior);
    }
    if (warrior->state == ATTACK)
        animation_attack(warrior);
}

static void reset_warrior(warrior_t *warrior)
{
    warrior->rect_dead.left = 0;
    warrior->rect_dead.top = 0;
    warrior->number_dead = 0;
    warrior->state = IDLE;
}

static void animation_dead3(warrior_t *warrior, bool time_elapsed)
{
    if (warrior->number_dead == 1 && time_elapsed) {
        warrior->rect_dead.left = 0;
        warrior->rect_dead.top = DEAD_WIDTH;
        warrior->number_dead = 2;
    } else if (warrior->number_dead == 2 &&
        warrior->rect_dead.left >= DEAD_WIDTH * 6) {
        reset_warrior(warrior);
    } else {
        warrior->rect_dead.left += DEAD_WIDTH;
    }
}

static void animation_dead2(warrior_t *warrior)
{
    bool time_elapsed = warrior->clock_dead->seconds > 10.0;

    if (warrior->number_dead == 0 &&
        warrior->rect_dead.left >= DEAD_WIDTH * 6) {
        warrior->number_dead = 1;
        sfClock_restart(warrior->clock_dead->clock);
    } else if (warrior->number_dead == 1 && !time_elapsed) {
        printf("Time elapsed = %f\n", warrior->clock_dead->seconds);
        warrior->rect_dead.left = DEAD_WIDTH * 6;
    } else
        animation_dead3(warrior, time_elapsed);
}

static void animation_dead(warrior_t *warrior)
{
    warrior->myclock->time = sfClock_getElapsedTime(warrior->myclock->clock);
    warrior->myclock->seconds =
        warrior->myclock->time.microseconds / 1000000.0;
    warrior->clock_dead->time =
        sfClock_getElapsedTime(warrior->clock_dead->clock);
    warrior->clock_dead->seconds =
        warrior->clock_dead->time.microseconds / 1000000.0;
    if (warrior->myclock->seconds > 0.1) {
        animation_dead2(warrior);
        sfSprite_setTextureRect(warrior->sprite_dead, warrior->rect_dead);
        sfClock_restart(warrior->myclock->clock);
    }
}

void anim_warrior(warrior_t *warrior)
{
    if (warrior->state == RIEN)
        return;
    if (warrior->state == DEAD) {
        animation_dead(warrior);
    } else
        animation_alive(warrior);
}
