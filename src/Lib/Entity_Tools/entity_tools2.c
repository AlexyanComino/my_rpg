/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** entity_tools2
*/

#include "rpg.h"

bool entity_see_enemy(rpg_t *rpg, entity_t *entity, entity_t *enemy)
{
    if (!enemy)
        return false;
    if (entity_look_at_enemy(entity, enemy)) {
        if (hitbox_in_detection(enemy->common->zones->hitbox,
            entity->common->zones->l_radius, entity->common->pos))
            return !is_in_line_of_sight(rpg, entity, entity->common->pos,
                enemy->common->pos);
        else
            return false;
    }
    if (!is_discreet(enemy)) {
        if (hitbox_in_detection(enemy->common->zones->hitbox,
            entity->common->zones->m_radius, entity->common->pos))
            return !is_in_line_of_sight(rpg, entity, entity->common->pos,
                enemy->common->pos);
        else
            return false;
    }
    return false;
}

sfColor get_color_from_faction(entity_t *entity)
{
    faction_t faction = entity->common->faction;

    if (faction == BLUE_TEAM)
        return DAMAGE_COLOR_BLUE;
    if (faction == PURPLE_TEAM)
        return DAMAGE_COLOR_PURPLE;
    if (faction == YELLOW_TEAM)
        return DAMAGE_COLOR_YELLOW;
    if (faction == RED_TEAM)
        return DAMAGE_COLOR_RED;
    if (faction == GOBLIN_TEAM)
        return DAMAGE_COLOR_GREEN;
    if (faction == WITH_ALL)
        return sfBlack;
    return sfWhite;
}

// Vérifie si un cercle est en collision avec une hitbox
bool hitbox_in_detection(sfIntRect hitbox, unsigned int radius,
    sfVector2f circle_pos)
{
    float cx = circle_pos.x;
    float cy = circle_pos.y;
    float r = radius;
    float rx = hitbox.left;
    float ry = hitbox.top;
    float w = hitbox.width;
    float h = hitbox.height;
    float closestX = fmaxf(rx, fminf(cx, rx + w));
    float closestY = fmaxf(ry, fminf(cy, ry + h));
    float distance = sqrtf((cx - closestX) * (cx - closestX) + (cy - closestY)
        * (cy - closestY));

    if (distance <= r)
        return true;
    else
        return false;
}

bool entity_can_attack_enemy(rpg_t *rpg, entity_t *entity)
{
    sfIntRect hitbox_attack = entity->common->zones->hitbox_attack;
    sfIntRect hitbox;

    for (unsigned int i = 0; i < rpg->ent_size; i++) {
        if (!rpg->ent[i]->in_view)
            continue;
        hitbox = rpg->ent[i]->common->zones->hitbox;
        if (sfIntRect_intersects(&hitbox_attack, &hitbox, NULL))
            return true;
    }
    return false;
}
