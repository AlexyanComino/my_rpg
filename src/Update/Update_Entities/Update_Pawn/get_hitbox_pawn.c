/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** get_hitbox_pawn
*/

#include "rpg.h"

sfIntRect get_hitbox_pawn(sfVector2f pos)
{
    return (sfIntRect){pos.x - PAWN_WIDTH / 8, pos.y - PAWN_WIDTH / 8,
        PAWN_WIDTH / 4, PAWN_WIDTH / 4};
}

sfIntRect get_hitbox_attack_pawn(sfVector2f pos, side_x_t x, side_y_t y)
{
    int hitbox_x = PAWN_WIDTH / 4;
    int hitbox_y = PAWN_WIDTH / 6;

    (void)y;
    if (x == RIGHT)
        return (sfIntRect){pos.x + PAWN_WIDTH / 8, pos.y,
            hitbox_x, hitbox_y};
    else
        return (sfIntRect){pos.x - PAWN_WIDTH / 8 - PAWN_WIDTH / 4,
        pos.y, hitbox_x, hitbox_y};
}

sfIntRect get_hitbox_pawn_foot(sfVector2f pos)
{
    return (sfIntRect){pos.x - PAWN_WIDTH / 8,
        (pos.y + PAWN_WIDTH / 8) - (2 * (PAWN_WIDTH / 4) / 5) / 2,
        PAWN_WIDTH / 4, 2 * (PAWN_WIDTH / 4) / 5};
}
