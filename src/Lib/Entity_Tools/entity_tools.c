/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** entity_tools
*/

#include "rpg.h"

entity_t *get_nearest_entity(rpg_t *rpg, entity_t *entity, bool same_faction)
{
    entity_t *nearest = NULL;
    float min_distance = 0;
    float distance = 0;

    for (unsigned int i = 0; i < rpg->ent_size; i++) {
        if (!rpg->ent[i]->in_view || !is_alive(rpg->ent[i]) ||
            rpg->ent[i] == entity || (!same_faction &&
            entities_in_same_faction(entity, rpg->ent[i])))
            continue;
        distance = get_distance_between_pos(entity->common->pos,
            rpg->ent[i]->common->pos);
        if (nearest == NULL || distance < min_distance) {
            nearest = rpg->ent[i];
            min_distance = distance;
        }
    }
    return nearest;
}

bool entity_look_at_enemy(entity_t *entity, entity_t *enemy)
{
    if (!enemy)
        return false;
    if (entity->common->x == LEFT &&
        enemy->common->pos.x < entity->common->pos.x)
        return true;
    else if (entity->common->x == RIGHT &&
        enemy->common->pos.x > entity->common->pos.x)
        return true;
    return false;
}

//
// Vérifie si un guerrier peut interagir avec le joueur
bool is_player_interact_entity(rpg_t *rpg, entity_t *entity)
{
    entity_t *player = rpg->ent[0];
    sfIntRect hitbox_attack = player->common->zones->hitbox_attack;

    if (sfIntRect_intersects(&hitbox_attack,
        &entity->common->zones->hitbox, NULL))
        return (true);
    return (false);
}
