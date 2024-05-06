/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** get_hitbox_torch
*/

#include "rpg.h"

sfIntRect get_hitbox_torch(sfVector2f pos)
{
    return (sfIntRect){pos.x - TORCH_WIDTH / 8, pos.y - TORCH_WIDTH / 8,
        TORCH_WIDTH / 4, TORCH_WIDTH / 4};
}

static sfIntRect get_torch_hitbox_attack_left(sfVector2f pos, side_y_t y,
    int hitbox_x, int hitbox_y)
{
    if (y == UP)
        return (sfIntRect){pos.x - TORCH_WIDTH / 8 - (TORCH_WIDTH - hitbox_x)
            / 4, pos.y - TORCH_WIDTH / 8 - TORCH_WIDTH / 4,
            hitbox_x, hitbox_y};
    else if (y == DOWN)
        return (sfIntRect){pos.x - TORCH_WIDTH / 8 - (TORCH_WIDTH - hitbox_x)
            / 4, pos.y + TORCH_WIDTH / 8,
            hitbox_x, hitbox_y};
    else
        return (sfIntRect){pos.x - TORCH_WIDTH / 8 - TORCH_WIDTH / 4,
            pos.y - TORCH_WIDTH / 8 - (TORCH_WIDTH - hitbox_y) / 4,
            hitbox_x, hitbox_y};
}

static sfIntRect get_torch_hitbox_attack_right(sfVector2f pos, side_y_t y,
    int hitbox_x, int hitbox_y)
{
    if (y == UP)
        return (sfIntRect){pos.x - TORCH_WIDTH / 8 - (TORCH_WIDTH - hitbox_x)
            / 4, pos.y - TORCH_WIDTH / 8 - TORCH_WIDTH / 4,
            hitbox_x, hitbox_y};
    else if (y == DOWN)
        return (sfIntRect){pos.x - TORCH_WIDTH / 8 - (TORCH_WIDTH - hitbox_x)
            / 4, pos.y + TORCH_WIDTH / 8,
            hitbox_x, hitbox_y};
    else
        return (sfIntRect){pos.x + TORCH_WIDTH / 8, pos.y - TORCH_WIDTH
            / 8 - (TORCH_WIDTH - hitbox_y) / 4,
            hitbox_x, hitbox_y};
}

sfIntRect get_hitbox_attack_torch(sfVector2f pos, side_x_t x, side_y_t y)
{
    int hitbox_x = (y == NONE) ? TORCH_WIDTH / 4 : TORCH_WIDTH / 2;
    int hitbox_y = (y == NONE) ? TORCH_WIDTH / 2 : TORCH_WIDTH / 4;

    if (x == RIGHT)
        return get_torch_hitbox_attack_right(pos, y, hitbox_x, hitbox_y);
    else
        return get_torch_hitbox_attack_left(pos, y, hitbox_x, hitbox_y);
}
