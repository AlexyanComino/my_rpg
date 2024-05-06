/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_entity_zones
*/

#include "rpg.h"

static sfRectangleShape *init_rect_hitbox(sfIntRect hitbox, sfColor color)
{
    sfRectangleShape *rect_hitbox = sfRectangleShape_create();

    sfRectangleShape_setSize(rect_hitbox, (sfVector2f){hitbox.width,
        hitbox.height});
    sfRectangleShape_setPosition(rect_hitbox, (sfVector2f){hitbox.left,
        hitbox.top});
    sfRectangleShape_setFillColor(rect_hitbox, sfTransparent);
    sfRectangleShape_setOutlineColor(rect_hitbox, color);
    sfRectangleShape_setOutlineThickness(rect_hitbox, 1);
    return rect_hitbox;
}

static void init_detect_circles(zones_entity_t *zones)
{
    sfCircleShape_setRadius(zones->l_circle, zones->l_radius);
    sfCircleShape_setRadius(zones->m_circle, zones->m_radius);
    sfCircleShape_setRadius(zones->s_circle, zones->s_radius);
    sfCircleShape_setFillColor(zones->l_circle, sfTransparent);
    sfCircleShape_setFillColor(zones->m_circle, sfTransparent);
    sfCircleShape_setFillColor(zones->s_circle, sfTransparent);
    sfCircleShape_setOutlineColor(zones->l_circle, sfWhite);
    sfCircleShape_setOutlineColor(zones->m_circle, sfYellow);
    sfCircleShape_setOutlineColor(zones->s_circle, sfRed);
    sfCircleShape_setOutlineThickness(zones->l_circle, 1);
    sfCircleShape_setOutlineThickness(zones->m_circle, 1);
    sfCircleShape_setOutlineThickness(zones->s_circle, 1);
    sfCircleShape_setOrigin(zones->l_circle, (sfVector2f){zones->l_radius,
        zones->l_radius});
    sfCircleShape_setOrigin(zones->m_circle, (sfVector2f){zones->m_radius,
        zones->m_radius});
    sfCircleShape_setOrigin(zones->s_circle, (sfVector2f){zones->s_radius,
        zones->s_radius});
}

static void init_detect(char **infos, zones_entity_t *zones)
{
    zones->l_radius = atoi(infos[5]);
    zones->m_radius = atoi(infos[6]);
    zones->s_radius = atoi(infos[7]);
    zones->m_detect = false;
    zones->s_detect = false;
    zones->l_circle = sfCircleShape_create();
    zones->m_circle = sfCircleShape_create();
    zones->s_circle = sfCircleShape_create();
    init_detect_circles(zones);
}

static sfIntRect get_hitbox_from_type(entity_type_t type, sfVector2f pos)
{
    if (type == WARRIOR)
        return get_hitbox_warrior(pos);
    if (type == PAWN)
        return get_hitbox_pawn(pos);
    if (type == TORCH)
        return get_hitbox_torch(pos);
    return (sfIntRect){0, 0, 0, 0};
}

zones_entity_t *init_entity_zones(char **infos, sfVector2f pos,
    entity_type_t type)
{
    zones_entity_t *zones = malloc(sizeof(zones_entity_t));

    zones->hitbox = get_hitbox_from_type(type, pos);
    zones->rect_hitbox = init_rect_hitbox(zones->hitbox, sfBlue);
    zones->hitbox_attack = (sfIntRect){0, 0, 0, 0};
    zones->rect_hitbox_attack = init_rect_hitbox(zones->hitbox_attack,
        sfRed);
    init_detect(infos, zones);
    return zones;
}
