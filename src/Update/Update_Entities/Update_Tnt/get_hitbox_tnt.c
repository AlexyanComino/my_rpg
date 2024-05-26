/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** get_hitbox_tnt
*/

#include "rpg.h"

sfIntRect get_hitbox_tnt(sfVector2f pos, float scale)
{
    return (sfIntRect){pos.x - TNT_WIDTH / 7 * scale, pos.y -
        TNT_WIDTH / 7 * scale,
        TNT_WIDTH / 3.5 * scale, TNT_WIDTH / 3.5 * scale};
}

static sfIntRect get_tnt_hitbox_attack_left(sfVector2f pos, side_y_t y,
    box_t *info)
{
    if (y == UP)
        return (sfIntRect){pos.x - info->hitbox_x / 2,
            pos.y - TNT_WIDTH / 7 * info->scale - info->hitbox_y,
                info->hitbox_x, info->hitbox_y};
    else if (y == DOWN)
        return (sfIntRect){pos.x - info->hitbox_x / 2, pos.y +
            TNT_WIDTH / 7 * info->scale,
            info->hitbox_x, info->hitbox_y};
    else
        return (sfIntRect){pos.x - TNT_WIDTH / 7 * info->scale -
            TNT_WIDTH / 3.5 * info->scale,
            pos.y - info->hitbox_y / 2,
            info->hitbox_x, info->hitbox_y};
}

static sfIntRect get_tnt_hitbox_attack_right(sfVector2f pos, side_y_t y,
    box_t *info)
{
    if (y == UP)
        return (sfIntRect){pos.x - info->hitbox_x / 2,
            pos.y - TNT_WIDTH / 7 * info->scale - info->hitbox_y,
                info->hitbox_x, info->hitbox_y};
    else if (y == DOWN)
        return (sfIntRect){pos.x - info->hitbox_x / 2, pos.y +
            TNT_WIDTH / 7 * info->scale,
            info->hitbox_x, info->hitbox_y};
    else
        return (sfIntRect){pos.x + TNT_WIDTH / 7 * info->scale,
            pos.y - info->hitbox_y / 2,
            info->hitbox_x, info->hitbox_y};
}

sfIntRect get_hitbox_attack_tnt(sfVector2f pos, side_x_t x, side_y_t y,
    float scale)
{
    box_t info = {0};

    info.scale = scale;
    info.hitbox_x = (y == NONE) ? TNT_WIDTH / 3.5 * scale :
        TNT_WIDTH / 2 * scale;
    info.hitbox_y = (y == NONE) ? TNT_WIDTH / 2 * scale :
        TNT_WIDTH / 5 * scale;
    if (x == RIGHT)
        return get_tnt_hitbox_attack_right(pos, y, &info);
    else
        return get_tnt_hitbox_attack_left(pos, y, &info);
}

sfIntRect get_hitbox_tnt_foot(sfVector2f pos, float scale)
{
    return (sfIntRect){pos.x - TNT_WIDTH / 7 * scale,
        (pos.y + TNT_WIDTH / 7 * scale) -
            (2 * (TNT_WIDTH / 3.5 * scale) / 5) / 2,
        TNT_WIDTH / 3.5 * scale,
        2 * (TNT_WIDTH / 3.5 * scale) / 5};
}
