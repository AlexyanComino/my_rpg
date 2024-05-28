/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** display_pawn
*/

#include "rpg.h"

static void display_reverse_item(rpg_t *rpg, entity_t *entity)
{
    sfVector2f scale =
        sfSprite_getScale(entity->spe->pawn->carry->item->sprite);

    scale.x = -scale.x;
    sfSprite_setScale(entity->spe->pawn->carry->item->sprite, scale);
    sfRenderWindow_drawSprite(rpg->win->window,
        entity->spe->pawn->carry->item->sprite, NULL);
    scale.x = -scale.x;
    sfSprite_setScale(entity->spe->pawn->carry->item->sprite, scale);
}

static void display_items(rpg_t *rpg, entity_t *entity)
{
    sfVector2f pos;

    for (int i = 0; i < entity->spe->pawn->carry->item->quantity; i++) {
        pos.x = entity->common->pos.x +
            entity->spe->pawn->carry->item->pos[i].x;
        pos.y = entity->common->pos.y +
            entity->spe->pawn->carry->item->pos[i].y;
        sfSprite_setPosition(entity->spe->pawn->carry->item->sprite, pos);
        if (entity->spe->pawn->carry->item->index_rev_scale[i] == 1) {
            display_reverse_item(rpg, entity);
        } else {
            sfRenderWindow_drawSprite(rpg->win->window,
                entity->spe->pawn->carry->item->sprite, NULL);
        }
    }
}

static void display_alive_pawn(rpg_t *rpg, entity_t *entity)
{
    display_common(rpg, entity);
    if (is_carrying(entity))
        display_items(rpg, entity);
}

void display_pawn(rpg_t *rpg, entity_t *entity)
{
    if (entity->common->state == RIEN)
        return;
    if (entity->common->state == DEAD) {
        sfRenderWindow_drawSprite(rpg->win->window,
        entity->common->death->anim->sprite, NULL);
        if (entity->common->grade_type == SOLDAT_QUEST)
            sfRenderWindow_drawSprite(rpg->win->window,
            entity->common->grade_icon->sprite, NULL);
    } else
        display_alive_pawn(rpg, entity);
}
