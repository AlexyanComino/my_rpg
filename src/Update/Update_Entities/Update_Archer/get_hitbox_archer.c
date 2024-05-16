/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** get_hitbox_archer
*/

#include "rpg.h"

sfIntRect get_hitbox_archer(sfVector2f pos)
{
    return (sfIntRect){pos.x - ARCHER_WIDTH / 7, pos.y - ARCHER_WIDTH / 7,
        ARCHER_WIDTH / 3.5, ARCHER_WIDTH / 3.5};
}

static sfIntRect get_archer_hitbox_attack_left(sfVector2f pos, side_y_t y,
    int hitbox_x, int hitbox_y)
{
    if (y == UP)
        return (sfIntRect){pos.x - hitbox_x / 2,
            pos.y - ARCHER_WIDTH / 7 - hitbox_y, hitbox_x, hitbox_y};
    else if (y == DOWN)
        return (sfIntRect){pos.x - hitbox_x / 2, pos.y + ARCHER_WIDTH / 7,
            hitbox_x, hitbox_y};
    else
        return (sfIntRect){pos.x - ARCHER_WIDTH / 7 - ARCHER_WIDTH / 3.5,
            pos.y - hitbox_y / 2,
            hitbox_x, hitbox_y};
}

static sfIntRect get_archer_hitbox_attack_right(sfVector2f pos, side_y_t y,
    int hitbox_x, int hitbox_y)
{
    if (y == UP)
        return (sfIntRect){pos.x - hitbox_x / 2,
            pos.y - ARCHER_WIDTH / 7 - hitbox_y, hitbox_x, hitbox_y};
    else if (y == DOWN)
        return (sfIntRect){pos.x - hitbox_x / 2, pos.y + ARCHER_WIDTH / 7,
            hitbox_x, hitbox_y};
    else
        return (sfIntRect){pos.x + ARCHER_WIDTH / 7, pos.y - hitbox_y / 2,
            hitbox_x, hitbox_y};
}

sfIntRect get_hitbox_attack_archer(sfVector2f pos, side_x_t x, side_y_t y)
{
    int hitbox_x = (y == NONE) ? ARCHER_WIDTH / 3.5 : ARCHER_WIDTH / 2;
    int hitbox_y = (y == NONE) ? ARCHER_WIDTH / 2 : ARCHER_WIDTH / 5;

    if (x == RIGHT)
        return get_archer_hitbox_attack_right(pos, y, hitbox_x, hitbox_y);
    else
        return get_archer_hitbox_attack_left(pos, y, hitbox_x, hitbox_y);
}

sfIntRect get_hitbox_archer_foot(sfVector2f pos)
{
    return (sfIntRect){pos.x - ARCHER_WIDTH / 7,
        (pos.y + ARCHER_WIDTH / 7) - (2 * (ARCHER_WIDTH / 3.5) / 5) / 2,
        ARCHER_WIDTH / 3.5,
        2 * (ARCHER_WIDTH / 3.5) / 5};
}
