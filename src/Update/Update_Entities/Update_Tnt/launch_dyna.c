/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** launch_dyna
*/

#include "rpg.h"

void launch_dyna(entity_t *entity)
{
    sfVector2f point_pos = {0, 0};
    int nb_points = entity->spe->tnt->curve->nb_points;

    entity->spe->tnt->is_launched = true;
    entity->spe->tnt->dyna->pos = entity->common->pos;
    sfSprite_setPosition(entity->spe->tnt->dyna->anim->sprite,
        entity->common->pos);
    entity->spe->tnt->dyna->anim->rect.left = 0;
    for (int i = 0; i < nb_points; i++) {
        point_pos = (sfVector2f){entity->common->pos.x +
            entity->spe->tnt->curve->points[i].x,
            entity->common->pos.y + entity->spe->tnt->curve->points[i].y};
        entity->spe->tnt->dyna->points[i] = point_pos;
    }
    entity->spe->tnt->explo->boom_center =
        entity->spe->tnt->dyna->points[nb_points - 1];
    sfCircleShape_setPosition(entity->spe->tnt->explo->boom_circle,
        entity->spe->tnt->explo->boom_center);
    entity->spe->tnt->dyna->index = 0;
    entity->spe->tnt->dyna->side = entity->common->x;
}
