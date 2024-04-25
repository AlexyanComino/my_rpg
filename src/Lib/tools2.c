/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** tools2
*/

#include "rpg.h"

bool hitbox_collision(rpg_t *rpg, sfVector2f point)
{
    for (unsigned int i = 0; i < rpg->collision->size; i++) {
        rpg->collision->rect.left = rpg->collision->pos[i].x;
        rpg->collision->rect.top = rpg->collision->pos[i].y;
        if (!intrect_is_in_view(rpg, rpg->collision->rect))
            continue;
        if (sfIntRect_contains(&rpg->collision->rect, point.x, point.y))
            return true;
    }
    return false;
}

static line_of_sight_data_t *init_line_of_sight_data(sfVector2f start,
    sfVector2f end)
{
    line_of_sight_data_t *data = malloc(sizeof(line_of_sight_data_t));

    data->start = start;
    data->end = end;
    data->dx = abs((int)end.x - (int)start.x);
    data->dy = abs((int)end.y - (int)start.y);
    data->sx = start.x < end.x ? 1 : -1;
    data->sy = start.y < end.y ? 1 : -1;
    data->err = data->dx - data->dy;
    data->e2 = 0;
    data->sample_interval = 10;
    data->sample_counter = 0;
    return data;
}

static void update_line_of_sight_data(line_of_sight_data_t *data)
{
    data->e2 = 2 * data->err;
    if (data->e2 > -data->dy) {
        data->err -= data->dy;
        data->start.x += data->sx;
    }
    if (data->e2 < data->dx) {
        data->err += data->dx;
        data->start.y += data->sy;
    }
}

static bool check_collision_point(rpg_t *rpg, line_of_sight_data_t *data)
{
    if (data->sample_counter == 0) {
        if (hitbox_collision(rpg, data->start))
            return true;
        data->sample_counter = data->sample_interval;
    }
    return false;
}

bool is_in_line_of_sight(rpg_t *rpg, sfVector2f start, sfVector2f end)
{
    line_of_sight_data_t *data = init_line_of_sight_data(start, end);
    float distance;

    while (true) {
        if (check_collision_point(rpg, data))
            return true;
        update_line_of_sight_data(data);
        data->sample_counter--;
        distance = sqrtf((data->start.x - data->end.x) *
            (data->start.x - data->end.x) + (data->start.y - data->end.y) *
            (data->start.y - data->end.y));
        if (distance < 10)
            break;
    }
    return false;
}

bool warrior_see_enemy(rpg_t *rpg, warrior_t *warrior, warrior_t *enemy)
{
    if (warrior_look_at_enemy(warrior, enemy)) {
        if (hitbox_in_detection(enemy->zones->hitbox,
            warrior->zones->radius_max_detection, warrior->pos))
            return !is_in_line_of_sight(rpg, warrior->pos, enemy->pos);
        else
            return false;
    }
    if (!is_discreet(enemy)) {
        if (hitbox_in_detection(enemy->zones->hitbox,
            warrior->inter->radius, warrior->pos))
            return !is_in_line_of_sight(rpg, warrior->pos, enemy->pos);
        else
            return false;
    }
    return false;
}

sfColor get_color_from_faction(warrior_t *warrior)
{
    faction_t faction = warrior->faction;

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
    return sfWhite;
}
