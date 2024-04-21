/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** move_warrior
*/

#include "rpg.h"

sfVector2f get_movement(sfVector2f center_target, sfVector2f center_warrior,
    float distance, int speed)
{
    sfVector2f direction = {center_target.x - center_warrior.x, center_target.y - center_warrior.y};

    return (sfVector2f){direction.x / distance * speed, direction.y / distance * speed};
}

static unsigned int get_warrior_speed(warrior_t *warrior)
{
    if (warrior->state == WALK)
        return warrior->attributes->speed / 2;
    return warrior->attributes->speed;
}

static sfVector2f get_target_pos_and_min_lenght(rpg_t *rpg, warrior_t *warrior,
    float *min_lenght)
{
    sfVector2f target_pos;
    warrior_t *target;

    if (WARRIOR_HAS_BASE(warrior) && warrior->base->come_back) {
        target_pos = warrior->base->pattern_pos[warrior->base->pattern_pos_index];
        *min_lenght = 10;
    } else{
        target = get_nearest_warrior(rpg, warrior);
        target_pos = target->pos;
        *min_lenght = MIN_WARRIOR_LENGTH;
    }
    return target_pos;
}

static bool warrior_is_arrived(warrior_t *warrior, float distance,
    float min_lenght, sfVector2f movement)
{
    if (distance < min_lenght && WARRIOR_HAS_BASE(warrior) && warrior->base->come_back) {
        warrior->state = IDLE;
        warrior->base->in_cooldown = true;
        sfClock_restart(warrior->base->myclock->clock);
        return true;
    } else if (distance < min_lenght) {
        warrior->state = IDLE;
        update_side_x(warrior, movement);
        update_side_y(warrior, movement);
        return true;
    }
    return false;
}

static void check_warrior_is_stuck(warrior_t *warrior,
    sfVector2f oldPos)
{
    if (fabs(warrior->pos.x - oldPos.x) < 0.1 &&
        fabs(warrior->pos.y - oldPos.y) < 0.1)
        warrior->state = IDLE;
}

void warrior_move(rpg_t *rpg, warrior_t *warrior)
{
    sfVector2f movement;
    sfVector2f target_pos;
    float min_lenght;
    float distance;
    float speed = get_warrior_speed(warrior);
    sfVector2f oldPos = warrior->pos;

    if (WARRIOR_HAS_BASE(warrior) && warrior->base->in_cooldown) {
        warrior->state = IDLE;
        return;
    }
    target_pos = get_target_pos_and_min_lenght(rpg, warrior, &min_lenght);
    distance = get_distance_between_pos(warrior->pos, target_pos);
    movement = get_movement(target_pos, warrior->pos, distance, speed);
    if (warrior_is_arrived(warrior, distance, min_lenght, movement))
        return;
    update_warrior_x(rpg, warrior, movement);
    update_warrior_y(rpg, warrior, movement);
    check_warrior_is_stuck(warrior, oldPos);
}
