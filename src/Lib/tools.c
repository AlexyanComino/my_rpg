/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** tools
*/

#include "rpg.h"

float get_distance_between_pos(sfVector2f center1, sfVector2f center2)
{
    return sqrt(pow(center1.x - center2.x, 2) + pow(center1.y - center2.y, 2));
}

warrior_t *get_nearest_warrior(rpg_t *rpg, warrior_t *warrior)
{
    warrior_t *nearest = NULL;
    lwarrior_t *tmp = rpg->lwarrior;
    float min_distance = 0;
    float distance = 0;

    while (tmp != NULL) {
        if (tmp->warrior == warrior || tmp->warrior->faction ==
            warrior->faction || tmp->warrior->state == DEAD ||
            !warrior_is_in_view(rpg, tmp->warrior)) {
            tmp = tmp->next;
            continue;
        }
        distance = get_distance_between_pos(warrior->pos, tmp->warrior->pos);
        if (nearest == NULL || distance < min_distance) {
            nearest = tmp->warrior;
            min_distance = distance;
        }
        tmp = tmp->next;
    }
    return nearest;
}

void update_clock_seconds(my_clock_t *myclock)
{
    myclock->time = sfClock_getElapsedTime(myclock->clock);
    myclock->seconds = myclock->time.microseconds / 1000000.0;
}

bool warrior_look_at_enemy(warrior_t *warrior, warrior_t *enemy)
{
    if (warrior->x == LEFT && enemy->pos.x < warrior->pos.x)
        return true;
    else if (warrior->x == RIGHT && enemy->pos.x > warrior->pos.x)
        return true;
    return false;
}
