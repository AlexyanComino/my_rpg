/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** line_of_sight
*/

#include "rpg.h"


static bool hitbox_collision_region(rpg_t *rpg, int col, int row,
    sfVector2f point)
{
    if (col < 0 || col >= (int)rpg->collision->cols || row < 0 ||
        row >= (int)rpg->collision->rows)
        return false;
    for (unsigned int i = 0; i < rpg->collision->regions[col][row]->size;
        i++) {
        rpg->collision->rect.left =
            rpg->collision->regions[col][row]->pos[i].x;
        rpg->collision->rect.top =
            rpg->collision->regions[col][row]->pos[i].y;
        if (!intrect_is_in_view(rpg, rpg->collision->rect))
            continue;
        if (sfIntRect_contains(&rpg->collision->rect, point.x, point.y))
            return true;
    }
    return false;
}

static bool hitbox_collision2(rpg_t *rpg, int col, int row, sfVector2f point)
{
    if (hitbox_collision_region(rpg, col, row - 1, point))
        return true;
    if (hitbox_collision_region(rpg, col - 1, row - 1, point))
        return true;
    if (hitbox_collision_region(rpg, col + 1, row - 1, point))
        return true;
    if (hitbox_collision_region(rpg, col - 1, row + 1, point))
        return true;
    return false;
}

static bool hitbox_collision(rpg_t *rpg, sfVector2f point)
{
    int col = point.x / WIDTH;
    int row = point.y / HEIGHT;

    if (hitbox_collision_region(rpg, col, row, point))
        return true;
    if (hitbox_collision_region(rpg, col + 1, row, point))
        return true;
    if (hitbox_collision_region(rpg, col, row + 1, point))
        return true;
    if (hitbox_collision_region(rpg, col + 1, row + 1, point))
        return true;
    if (hitbox_collision_region(rpg, col - 1, row, point))
        return true;
    return hitbox_collision2(rpg, col, row, point);
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
    data->sample_interval = 15;
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

static bool check_collision_point(rpg_t *rpg, entity_t *entity,
    line_of_sight_data_t *data)
{
    if (data->sample_counter == 0) {
        if (!sfIntRect_contains(&entity->common->zones->hitbox, data->start.x,
            data->start.y) && hitbox_collision(rpg, data->start))
            return true;
        data->sample_counter = data->sample_interval;
    }
    return false;
}

bool is_in_line_of_sight(rpg_t *rpg, entity_t *entity, sfVector2f start,
    sfVector2f end)
{
    line_of_sight_data_t *data = init_line_of_sight_data(start, end);
    float distance;

    while (true) {
        if (check_collision_point(rpg, entity, data))
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
