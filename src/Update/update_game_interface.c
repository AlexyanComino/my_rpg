/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_game_interface
*/

#include "rpg.h"

static void check_player_in_base(rpg_t *rpg, restricted_t *restricted)
{
    entity_t *player = rpg->ent[0];

    for (unsigned int i = 0; i < rpg->ent_size; i++) {
        if (entity_has_base(rpg->ent[i]) && rpg->ent[i]->common->faction !=
        player->common->faction && rpg->ent[i]->common->state != DEAD &&
        sfIntRect_intersects(&player->common->zones->hitbox,
            &rpg->ent[i]->spe->warrior->base->rect,
        NULL)) {
            restricted->in_base = true;
            return;
        }
    }
    restricted->in_base = false;
}

static void appear_the_text(rpg_t *rpg, restricted_t *restricted,
    sfColor color, sfVector2f view_center)
{
    int alpha = color.a;

    if (alpha + 12 > 255)
        color.a = 255;
    else
        color.a += 12;
    sfSprite_setColor(restricted->sprite, color);
    if (restricted->danger_pos.y + 5 < view_center.y - rpg->win->height / 2 +
        rpg->win->height / 10) {
        restricted->danger_pos.y += 5;
        sfSprite_setPosition(restricted->sprite, restricted->danger_pos);
    }
}

static void disappear_the_text(restricted_t *restricted, sfColor color)
{
    int alpha = color.a;

    if (alpha - 7 < 0)
        color.a = 0;
    else
        color.a -= 7;
    sfSprite_setColor(restricted->sprite, color);
    restricted->danger_pos.y -= 2.5;
    sfSprite_setPosition(restricted->sprite, restricted->danger_pos);
}

void update_game_interface(rpg_t *rpg)
{
    restricted_t *restricted = rpg->interface->restricted;
    sfColor color = sfSprite_getColor(restricted->sprite);
    sfVector2f view_center = sfView_getCenter(rpg->win->view);

    if (color.a == 0)
        restricted->danger_pos = (sfVector2f){view_center.x,
            view_center.y - rpg->win->height / 2};
    check_player_in_base(rpg, restricted);
    if ((restricted->in_base && color.a < 255) || (!restricted->in_base &&
    color.a > 0)) {
        restricted->animation = true;
    } else {
        restricted->animation = false;
    }
    if (restricted->animation) {
        if (restricted->in_base)
            appear_the_text(rpg, restricted, color, view_center);
        else
            disappear_the_text(restricted, color);
    }
}
