/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** entity_colliders
*/

#include "rpg.h"


// Vérifie si la hitbox d'un guerrier est en collision avec celle
// d'un autre guerrier
static bool is_entity_hitbox_collide_entity(rpg_t *rpg, entity_t *entity,
    sfIntRect hitbox)
{
    for (unsigned int i = 0; i < rpg->ent_size; i++) {
        if (!rpg->ent[i]->in_view || rpg->ent[i] == entity ||
            !is_alive(rpg->ent[i]))
            continue;
        if (sfIntRect_intersects(&hitbox, &rpg->ent[i]->common->zones->hitbox,
            NULL))
            return (true);
    }
    return (false);
}

static bool is_entity_hitbox_in_collision_with_map(rpg_t *rpg,
    sfIntRect hitbox)
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

bool is_entity_hitbox_collide(rpg_t *rpg, entity_t *entity,
    sfIntRect hitbox)
{
    if (is_entity_hitbox_collide_entity(rpg, entity, hitbox))
        return (true);
    if (is_entity_hitbox_in_collision_with_map(rpg, hitbox))
        return (true);
    return (false);
}
