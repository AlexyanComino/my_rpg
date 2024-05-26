/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** hitbox_warrior
*/

#include "rpg.h"


// Récupère la hitbox d'un guerrier en fonction de sa position
// et de son orientation
sfIntRect get_hitbox_warrior(sfVector2f pos, float scale)
{
    return (sfIntRect){pos.x - WARRIOR_WIDTH / 6 * scale, pos.y -
        WARRIOR_WIDTH / 6 * scale,
        WARRIOR_WIDTH / 3 * scale, WARRIOR_WIDTH / 3 * scale};
}

static sfIntRect get_warrior_hitbox_attack_left(sfVector2f pos, side_y_t y,
    box_t *info)
{
    if (y == UP)
        return (sfIntRect){pos.x - WARRIOR_WIDTH / 6 * info->scale -
            WARRIOR_WIDTH / 3 * info->scale +
            (WARRIOR_WIDTH * info->scale- info->hitbox_x) / 2, pos.y -
                WARRIOR_WIDTH / 3* info->scale,
        info->hitbox_x, info->hitbox_y};
    else if (y == DOWN)
        return (sfIntRect){pos.x - WARRIOR_WIDTH / 6 * info->scale -
            WARRIOR_WIDTH / 3 * info->scale +
            (WARRIOR_WIDTH * info->scale- info->hitbox_x) / 2, pos.y +
                WARRIOR_WIDTH / 6* info->scale,
        info->hitbox_x, info->hitbox_y};
    else
        return (sfIntRect){pos.x - WARRIOR_WIDTH / 6* info->scale -
            WARRIOR_WIDTH / 3* info->scale,
        pos.y - WARRIOR_WIDTH / 6 * info->scale - WARRIOR_WIDTH / 3 *
            info->scale +
        (WARRIOR_WIDTH * info->scale- info->hitbox_y) / 2, info->hitbox_x,
            info->hitbox_y};
}

static sfIntRect get_warrior_hitbox_attack_right(sfVector2f pos, side_y_t y,
    box_t *info)
{
    if (y == UP)
        return (sfIntRect){pos.x - WARRIOR_WIDTH / 6 * info->scale -
            WARRIOR_WIDTH / 3 * info->scale +
            (WARRIOR_WIDTH * info->scale - info->hitbox_x) / 2,
                pos.y - WARRIOR_WIDTH / 3 * info->scale,
        info->hitbox_x, info->hitbox_y};
    else if (y == DOWN)
        return (sfIntRect){pos.x - WARRIOR_WIDTH / 6 * info->scale -
            WARRIOR_WIDTH / 3 * info->scale +
            (WARRIOR_WIDTH * info->scale - info->hitbox_x) / 2,
                pos.y + WARRIOR_WIDTH / 6 * info->scale,
        info->hitbox_x, info->hitbox_y};
    else
        return (sfIntRect){pos.x + WARRIOR_WIDTH / 6 * info->scale,
            pos.y - WARRIOR_WIDTH
            / 6 * info->scale - WARRIOR_WIDTH / 3 * info->scale +
                (WARRIOR_WIDTH * info->scale - info->hitbox_y) / 2,
        info->hitbox_x, info->hitbox_y};
}

// Récupère la hitbox d'attaque d'un guerrier en fonction de sa position
// et de son orientation
sfIntRect get_warrior_hitbox_attack(sfVector2f pos, side_x_t x, side_y_t y,
    float scale)
{
    box_t info = {0};

    info.scale = scale;
    info.hitbox_x = (y == NONE) ? WARRIOR_WIDTH / 3 * info.scale :
        3 * WARRIOR_WIDTH / 4 * info.scale;
    info.hitbox_y = (y == NONE) ? 3 * WARRIOR_WIDTH / 4 * info.scale :
        WARRIOR_WIDTH / 4 * info.scale;
    if (x == RIGHT)
        return get_warrior_hitbox_attack_right(pos, y, &info);
    else
        return get_warrior_hitbox_attack_left(pos, y, &info);
}

sfIntRect get_hitbox_warrior_foot(sfVector2f pos, float scale)
{
    return (sfIntRect){pos.x - WARRIOR_WIDTH / 6 * scale,
        (pos.y + WARRIOR_WIDTH / 6 * scale) -
            (2 * (WARRIOR_WIDTH / 3 * scale) / 4) / 2,
        WARRIOR_WIDTH / 3 * scale, 2 * (WARRIOR_WIDTH / 3 * scale) / 4};
}
