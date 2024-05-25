/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_interface_pos
*/

#include "rpg.h"

//
static void update_front_bar_interface_pos(rpg_t *rpg, entity_t *player)
{
    round_rectangle_t *front = rpg->interface->health_bar->front;
    float r = front->r;

    front->pos =
        (sfVector2f){player->common->pos.x - WIDTH / 2 + WIDTH / 20 + 5,
        player->common->pos.y + HEIGHT / 2 - HEIGHT / 10 + 5};
    sfRectangleShape_setPosition(front->rect_w,
        (sfVector2f){front->pos.x, front->pos.y + r});
    sfRectangleShape_setPosition(front->rect_h,
        (sfVector2f){front->pos.x + r, front->pos.y});
    fill_round(front, r, front->pos, front->size);
}

static void update_back_bar_interface_pos(rpg_t *rpg, entity_t *player)
{
    round_rectangle_t *back = rpg->interface->health_bar->back;
    float r = back->r;

    back->pos = (sfVector2f){player->common->pos.x - WIDTH / 2 + WIDTH / 20,
        player->common->pos.y + HEIGHT / 2 - HEIGHT / 10};
    sfRectangleShape_setPosition(back->rect_w, (sfVector2f)
        {back->pos.x, back->pos.y + r});
    sfRectangleShape_setPosition(back->rect_h, (sfVector2f)
        {back->pos.x + r, back->pos.y});
    fill_round(back, r, back->pos, back->size);
}

static void update_health_bar_pos(rpg_t *rpg, entity_t *player)
{
    update_front_bar_interface_pos(rpg, player);
    update_back_bar_interface_pos(rpg, player);
}

//
void update_interface_pos(rpg_t *rpg, entity_t *player, sfVector2f oldPos)
{
    float diff_x = player->common->pos.x - oldPos.x;
    float diff_y = player->common->pos.y - oldPos.y;

    sfView_setCenter(rpg->win->view, player->common->pos);
    (*view_pos()) = player->common->pos;
    rpg->interface->restricted->danger_pos.x += diff_x;
    rpg->interface->restricted->danger_pos.y += diff_y;
    sfSprite_setPosition(rpg->interface->restricted->sprite,
        rpg->interface->restricted->danger_pos);
    update_health_bar_pos(rpg, player);
    sfText_setPosition(rpg->interface->player_infos->player_text,
        (sfVector2f){player->common->pos.x - WIDTH / 2 + WIDTH / 20,
        player->common->pos.y + HEIGHT / 2 - HEIGHT / 10 - 50});
    set_command_pos(rpg->interface->command_list, player->common->pos,
        rpg->win->zoom);
}
