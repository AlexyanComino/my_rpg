/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** hitbox_warrior
*/

#include "rpg.h"


// Récupère la hitbox d'un guerrier en fonction de sa position
// et de son orientation
sfIntRect get_hitbox_warrior(sfVector2f pos)
{
    return (sfIntRect){pos.x - WARRIOR_WIDTH / 6, pos.y - WARRIOR_WIDTH / 6,
        WARRIOR_WIDTH / 3, WARRIOR_WIDTH / 3};
}

static sfIntRect get_warrior_hitbox_attack_left(sfVector2f pos, side_y_t y,
    int hitbox_x, int hitbox_y)
{
    if (y == UP)
        return (sfIntRect){pos.x - WARRIOR_WIDTH / 6 - WARRIOR_WIDTH / 3 +
            (WARRIOR_WIDTH - hitbox_x) / 2, pos.y - WARRIOR_WIDTH / 3,
        hitbox_x, hitbox_y};
    else if (y == DOWN)
        return (sfIntRect){pos.x - WARRIOR_WIDTH / 6 - WARRIOR_WIDTH / 3 +
            (WARRIOR_WIDTH - hitbox_x) / 2, pos.y + WARRIOR_WIDTH / 6,
        hitbox_x, hitbox_y};
    else
        return (sfIntRect){pos.x - WARRIOR_WIDTH / 6 - WARRIOR_WIDTH / 3,
        pos.y - WARRIOR_WIDTH / 6 - WARRIOR_WIDTH / 3 +
        (WARRIOR_WIDTH - hitbox_y) / 2, hitbox_x, hitbox_y};
}

static sfIntRect get_warrior_hitbox_attack_right(sfVector2f pos, side_y_t y,
    int hitbox_x, int hitbox_y)
{
    if (y == UP)
        return (sfIntRect){pos.x - WARRIOR_WIDTH / 6 - WARRIOR_WIDTH / 3 +
            (WARRIOR_WIDTH - hitbox_x) / 2, pos.y - WARRIOR_WIDTH / 3,
        hitbox_x, hitbox_y};
    else if (y == DOWN)
        return (sfIntRect){pos.x - WARRIOR_WIDTH / 6 - WARRIOR_WIDTH / 3 +
            (WARRIOR_WIDTH - hitbox_x) / 2, pos.y + WARRIOR_WIDTH / 6,
        hitbox_x, hitbox_y};
    else
        return (sfIntRect){pos.x + WARRIOR_WIDTH / 6, pos.y - WARRIOR_WIDTH
            / 6 - WARRIOR_WIDTH / 3 + (WARRIOR_WIDTH - hitbox_y) / 2,
        hitbox_x, hitbox_y};
}

// Récupère la hitbox d'attaque d'un guerrier en fonction de sa position
// et de son orientation
sfIntRect get_warrior_hitbox_attack(sfVector2f pos, side_x_t x, side_y_t y)
{
    int hitbox_x = (y == NONE) ? WARRIOR_WIDTH / 3 : 3 * WARRIOR_WIDTH / 4;
    int hitbox_y = (y == NONE) ? 3 * WARRIOR_WIDTH / 4 : WARRIOR_WIDTH / 4;

    if (x == RIGHT)
        return get_warrior_hitbox_attack_right(pos, y, hitbox_x, hitbox_y);
    else
        return get_warrior_hitbox_attack_left(pos, y, hitbox_x, hitbox_y);
}

sfIntRect get_hitbox_warrior_foot(sfVector2f pos)
{
    return (sfIntRect){pos.x - WARRIOR_WIDTH / 6,
        (pos.y + WARRIOR_WIDTH / 6) - (2 * (WARRIOR_WIDTH / 3) / 4) / 2,
        WARRIOR_WIDTH / 3, 2 * (WARRIOR_WIDTH / 3) / 4};
}
