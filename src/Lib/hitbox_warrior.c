/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** hitbox_warrior
*/

#include "rpg.h"


// Récupère la hitbox d'un guerrier en fonction de sa position
// et de son orientation
sfIntRect get_hitbox_warrior(sfVector2f pos, x_warrior_t x)
{
    int hitbox_size = WARRIOR_WIDTH / 3;
    int offset = (WARRIOR_WIDTH - hitbox_size) / 2;

    if (x == RIGHT)
        return (sfIntRect){pos.x + offset, pos.y + offset, hitbox_size,
            hitbox_size};
    else
        return (sfIntRect){pos.x - hitbox_size - offset, pos.y + offset,
            hitbox_size, hitbox_size};
}

static sfIntRect get_hitbox_attack_left(sfVector2f pos, y_warrior_t y,
    int hitbox_x, int hitbox_y)
{
    if (y == UP)
        return (sfIntRect){pos.x + hitbox_x / 5 - WARRIOR_WIDTH,
        pos.y + hitbox_y / 3, hitbox_x, hitbox_y};
    else if (y == DOWN)
        return (sfIntRect){pos.x + hitbox_x / 5 - WARRIOR_WIDTH,
        pos.y + hitbox_y / 3 + hitbox_y + WARRIOR_WIDTH / 3, hitbox_x,
        hitbox_y};
    else
        return (sfIntRect){pos.x - WARRIOR_WIDTH, pos.y + (WARRIOR_WIDTH / 4)
        / 2, hitbox_x, hitbox_y};
}

static sfIntRect get_hitbox_attack_right(sfVector2f pos, y_warrior_t y,
    int hitbox_x, int hitbox_y)
{
    if (y == UP)
        return (sfIntRect){pos.x + hitbox_x / 5, pos.y + hitbox_y / 3,
        hitbox_x, hitbox_y};
    else if (y == DOWN)
        return (sfIntRect){pos.x + hitbox_x / 5, pos.y + hitbox_y / 3 +
        hitbox_y + WARRIOR_WIDTH / 3, hitbox_x, hitbox_y};
    else
        return (sfIntRect){pos.x + (2 * WARRIOR_WIDTH / 3), pos.y +
        (WARRIOR_WIDTH / 4) / 2, hitbox_x, hitbox_y};
}

// Récupère la hitbox d'attaque d'un guerrier en fonction de sa position
// et de son orientation
sfIntRect get_hitbox_attack(sfVector2f pos, x_warrior_t x, y_warrior_t y)
{
    int hitbox_x = (y == NONE) ? WARRIOR_WIDTH / 3 : 3 * WARRIOR_WIDTH / 4;
    int hitbox_y = (y == NONE) ? 3 * WARRIOR_WIDTH / 4 : WARRIOR_WIDTH / 4;

    if (x == RIGHT)
        return get_hitbox_attack_right(pos, y, hitbox_x, hitbox_y);
    else
        return get_hitbox_attack_left(pos, y, hitbox_x, hitbox_y);
}

// Vérifie si la hitbox d'un guerrier est en collision avec celle
// d'un autre guerrier
bool is_warrior_hitbox_collide(rpg_t *rpg, warrior_t *warrior,
    sfIntRect hitbox)
{
    lwarrior_t *tmp = rpg->lwarrior;

    while (tmp) {
        if (tmp->warrior != warrior &&
            sfIntRect_intersects(&hitbox, &tmp->warrior->hitbox, NULL))
            return (true);
        tmp = tmp->next;
    }
    return (false);
}

// Vérifie si l'attaque d'un guerrier touche un autre guerrier
bool is_warrior_attack_collide(warrior_t *target, sfIntRect attack)
{
    sfIntRect hitbox = target->hitbox;

    if (sfIntRect_intersects(&attack, &hitbox, NULL))
        return (true);
    return (false);
}
