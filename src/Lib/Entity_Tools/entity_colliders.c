/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** entity_colliders
*/

#include "rpg.h"

static bool is_entity_hitbox_collide_entity(rpg_t *rpg, entity_t *entity,
    sfIntRect hitbox)
{
    for (unsigned int i = 0; i < rpg->ent_size; i++) {
        if (!rpg->ent[i]->in_view ||
            rpg->ent[i] == entity ||
            !is_alive(rpg->ent[i]))
            continue;
        if (sfIntRect_intersects(&hitbox,
            &rpg->ent[i]->common->zones->hitbox_foot, NULL))
            return (true);
    }
    return (false);
}

static bool check_region(rpg_t *rpg, sfIntRect hitbox, int col, int row)
{
    if (col < 0 || col >= (int)rpg->collision->cols)
        return (false);
    if (row < 0 || row >= (int)rpg->collision->rows)
        return (false);
    for (unsigned int i = 0; i < rpg->collision->regions[col][row]->size;
        i++) {
        rpg->collision->rect.left =
            rpg->collision->regions[col][row]->pos[i].x;
        rpg->collision->rect.top =
            rpg->collision->regions[col][row]->pos[i].y;
        if (!intrect_is_in_view(rpg, rpg->collision->rect))
            continue;
        if (sfIntRect_intersects(&hitbox, &rpg->collision->rect, NULL))
            return (true);
    }
    return (false);
}

static bool is_entity_hitbox_in_collision_with_map(rpg_t *rpg,
    sfIntRect hitbox)
{
    unsigned int col = hitbox.left / WIDTH;
    unsigned int row = hitbox.top / HEIGHT;

    if (col >= rpg->collision->cols || row >= rpg->collision->rows)
        return (false);
    if (check_region(rpg, hitbox, col, row) ||
        check_region(rpg, hitbox, col + 1, row) ||
        check_region(rpg, hitbox, col, row + 1) ||
        check_region(rpg, hitbox, col + 1, row + 1) ||
        check_region(rpg, hitbox, col - 1, row) ||
        check_region(rpg, hitbox, col, row - 1) ||
        check_region(rpg, hitbox, col - 1, row - 1) ||
        check_region(rpg, hitbox, col + 1, row - 1) ||
        check_region(rpg, hitbox, col - 1, row + 1))
        return (true);
    rpg->collision->rect.left = 0;
    rpg->collision->rect.top = 0;
    return (false);
}

static bool is_entity_hitbox_collide_chest(rpg_t *rpg, sfIntRect hitbox)
{
    for (unsigned int i = 0; i < rpg->chests_size; i++) {
        if (sfIntRect_intersects(&hitbox, &rpg->chests[i]->rect, NULL))
            return (true);
    }
    return (false);
}

bool is_entity_hitbox_collide(rpg_t *rpg, entity_t *entity,
    sfIntRect hitbox)
{
    if (is_entity_hitbox_collide_entity(rpg, entity, hitbox))
        return (true);
    if (is_entity_hitbox_in_collision_with_map(rpg, hitbox))
        return (true);
    if (is_entity_hitbox_collide_chest(rpg, hitbox))
        return (true);
    return (false);
}
