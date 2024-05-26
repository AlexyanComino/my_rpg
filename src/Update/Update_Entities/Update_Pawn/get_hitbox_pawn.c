/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** get_hitbox_pawn
*/

#include "rpg.h"

sfIntRect get_hitbox_pawn(sfVector2f pos, float scale)
{
    return (sfIntRect){pos.x - PAWN_WIDTH / 8 * scale, pos.y -
        PAWN_WIDTH / 8 * scale,
        PAWN_WIDTH / 4 * scale, PAWN_WIDTH / 4 * scale};
}

sfIntRect get_hitbox_attack_pawn(sfVector2f pos, side_x_t x, side_y_t y,
    float scale)
{
    int hitbox_x = PAWN_WIDTH / 4 * scale;
    int hitbox_y = PAWN_WIDTH / 6 * scale;

    (void)y;
    if (x == RIGHT)
        return (sfIntRect){pos.x + PAWN_WIDTH / 8 * scale, pos.y,
            hitbox_x, hitbox_y};
    else
        return (sfIntRect){pos.x - PAWN_WIDTH / 8 * scale -
            PAWN_WIDTH / 4 * scale,
        pos.y, hitbox_x, hitbox_y};
}

sfIntRect get_hitbox_pawn_foot(sfVector2f pos, float scale)
{
    return (sfIntRect){pos.x - PAWN_WIDTH / 8 * scale,
        (pos.y + PAWN_WIDTH / 8 * scale) -
            (2 * (PAWN_WIDTH / 4 * scale) / 5) / 2,
        PAWN_WIDTH / 4 * scale, 2 * (PAWN_WIDTH / 4 * scale) / 5};
}
