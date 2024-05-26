/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_game_interface
*/

#include "rpg.h"

static void check_player_in_base(rpg_t *rpg, restricted_t *restricted)
{
    entity_t *player = get_player(rpg);

    for (unsigned int i = 0; i < rpg->ent_size; i++) {
        if (entity_has_base(rpg->ent[i]) && rpg->ent[i]->common->faction !=
        player->common->faction && is_alive(rpg->ent[i]) &&
            enemy_is_in_base(rpg->ent[i], player)) {
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

    if (alpha + 9 > 255)
        color.a = 255;
    else
        color.a += 9;
    sfSprite_setColor(restricted->sprite, color);
    if (restricted->danger_pos.y + 3 < view_center.y - rpg->win->height / 2 +
        rpg->win->height / 15) {
        restricted->danger_pos.y += 3;
        sfSprite_setPosition(restricted->sprite, restricted->danger_pos);
    }
}

static void disappear_the_text(restricted_t *restricted, sfColor color)
{
    int alpha = color.a;

    if (alpha - 5 < 0)
        color.a = 0;
    else
        color.a -= 5;
    sfSprite_setColor(restricted->sprite, color);
    restricted->danger_pos.y -= 1;
    sfSprite_setPosition(restricted->sprite, restricted->danger_pos);
}

static void update_restricted(rpg_t *rpg)
{
    restricted_t *restricted = rpg->interface->restricted;
    sfColor color = sfSprite_getColor(restricted->sprite);
    sfVector2f view_center = sfView_getCenter(rpg->win->view);

    if (color.a == 0)
        restricted->danger_pos = (sfVector2f){view_center.x -
            rpg->win->width / 2 + 240, view_center.y - rpg->win->height / 2};
    check_player_in_base(rpg, restricted);
    attack_music(rpg);
    if ((restricted->in_base && color.a < 255) || (!restricted->in_base &&
    color.a > 0))
        restricted->animation = true;
    else
        restricted->animation = false;
    if (restricted->animation) {
        if (restricted->in_base)
            appear_the_text(rpg, restricted, color, view_center);
        else
            disappear_the_text(restricted, color);
    }
}

static sfVector2f update_size(sfVector2f size, sfVector2f current_size,
    float transition_speed)
{
    if (current_size.x == size.x)
        return size;
    if (current_size.x < size.x) {
        if (current_size.x + transition_speed < size.x)
            size.x = current_size.x + transition_speed;
        else
            size.x = current_size.x;
    } else {
        if (current_size.x - transition_speed > size.x)
            size.x = current_size.x - transition_speed;
        else
            size.x = current_size.x;
    }
    return size;
}

static void update_front_bar_interface(rpg_t *rpg, sfVector2f size,
    sfColor color, float transition_speed)
{
    round_rectangle_t *front = rpg->interface->health_bar->front;
    float r = front->r;
    sfVector2f current_size = sfRectangleShape_getSize(front->rect_w);

    size = update_size(size, current_size, transition_speed);
    if (size.x < rpg->interface->health_bar->front->r * 2) {
        rpg->interface->health_bar->front->r = size.x / 2;
        r = rpg->interface->health_bar->front->r;
    }
    sfRectangleShape_setSize(front->rect_w,
        (sfVector2f){size.x, size.y - r * 2});
    sfRectangleShape_setSize(front->rect_h,
        (sfVector2f){size.x - r * 2, size.y});
    sfRectangleShape_setFillColor(front->rect_w, color);
    sfRectangleShape_setFillColor(front->rect_h, color);
    sfCircleShape_setFillColor(front->circle, color);
    if (sfCircleShape_getRadius(front->circle) != r)
        sfCircleShape_setRadius(front->circle, r);
    fill_round(front, r, front->pos, size);
}

static void update_health_bar_interface(rpg_t *rpg)
{
    entity_t *player = get_player(rpg);
    float ratio = (float)player->common->attributes->health /
        (float)player->common->attributes->max_health;
    sfVector2f size;
    sfColor color;
    sfVector2f current_size =
        sfRectangleShape_getSize(rpg->interface->health_bar->front->rect_w);
    float diff_x;
    float transition_speed;

    if (rpg->transition->displayed)
        return;
    if (ratio < 0)
        ratio = 0;
    size = (sfVector2f){rpg->interface->health_bar->front->size.x * ratio,
        rpg->interface->health_bar->front->size.y};
    color = sfColor_fromRGB(255 * (1 - ratio), 255 * ratio, 0);
    diff_x = size.x - current_size.x;
    transition_speed = fabs(diff_x) / 15.0f;
    update_front_bar_interface(rpg, size, color, transition_speed);
}

void update_game_interface(rpg_t *rpg)
{
    update_restricted(rpg);
    update_health_bar_interface(rpg);
    update_popup_item(rpg);
}
