/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** colliders
*/

#include "rpg.h"

// Vérifie si la hitbox d'un guerrier est en collision avec celle
// d'un autre guerrier
bool is_warrior_hitbox_collide_warrior(rpg_t *rpg, warrior_t *warrior,
    sfIntRect hitbox)
{
    lwarrior_t *tmp = rpg->lwarrior;

    while (tmp) {
        if (tmp->warrior != warrior && warrior_is_in_view(rpg, tmp->warrior) &&
            tmp->warrior->state != DEAD &&
            tmp->warrior->state != RIEN &&
            sfIntRect_intersects(&hitbox, &tmp->warrior->zones->hitbox, NULL))
            return (true);
        tmp = tmp->next;
    }
    return (false);
}

bool is_warrior_hitbox_in_collision_with_map(rpg_t *rpg, sfIntRect hitbox)
{
    for (unsigned int i = 0; i < rpg->collision->size; i++) {
        rpg->collision->rect.left = rpg->collision->pos[i].x;
        rpg->collision->rect.top = rpg->collision->pos[i].y;
        if (sfIntRect_intersects(&hitbox, &rpg->collision->rect, NULL))
            return (true);
    }
    rpg->collision->rect.left = 0;
    rpg->collision->rect.top = 0;
    return (false);
}

bool is_warrior_hitbox_collide(rpg_t *rpg, warrior_t *warrior,
    sfIntRect hitbox)
{
    if (is_warrior_hitbox_collide_warrior(rpg, warrior, hitbox))
        return (true);
    if (is_warrior_hitbox_in_collision_with_map(rpg, hitbox))
        return (true);
    return (false);
}
