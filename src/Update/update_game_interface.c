/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_game_interface
*/

#include "rpg.h"

static void check_player_in_base(rpg_t *rpg, restricted_t *restricted)
{
    warrior_t *player = rpg->lwarrior->warrior;
    lwarrior_t *tmp = rpg->lwarrior->next;

    while (tmp) {
        if (tmp->warrior->faction != player->faction &&
        tmp->warrior->state != DEAD &&
        sfIntRect_intersects(&player->zones->hitbox, &tmp->warrior->base->rect,
        NULL)) {
            restricted->in_base = true;
            return;
        }
        tmp = tmp->next;
    }
    restricted->in_base = false;
}

static void appear_the_text(restricted_t *restricted, sfColor color)
{
    int alpha = color.a;

    if (alpha + 10 > 255)
        color.a = 255;
    else
        color.a += 10;
    sfSprite_setColor(restricted->sprite, color);
    restricted->danger_pos.y += 5;
    sfSprite_setPosition(restricted->sprite, restricted->danger_pos);
}

static void disappear_the_text(restricted_t *restricted, sfColor color)
{
    int alpha = color.a;

    if (alpha - 8 < 0)
        color.a = 0;
    else
        color.a -= 8;
    sfSprite_setColor(restricted->sprite, color);
    restricted->danger_pos.y -= 3;
    sfSprite_setPosition(restricted->sprite, restricted->danger_pos);
}

void update_game_interface(rpg_t *rpg)
{
    restricted_t *restricted = rpg->interface->restricted;
    sfColor color = sfSprite_getColor(restricted->sprite);

    if (color.a == 0)
        restricted->danger_pos = (sfVector2f){(*view_pos()).x,
            (*view_pos()).y - 1080 / 2};
    check_player_in_base(rpg, restricted);
    if ((restricted->in_base && color.a < 255) || (!restricted->in_base &&
    color.a > 0)) {
        restricted->animation = true;
    } else {
        restricted->animation = false;
    }
    if (restricted->animation) {
        if (restricted->in_base)
            appear_the_text(restricted, color);
        else
            disappear_the_text(restricted, color);
    }
}
