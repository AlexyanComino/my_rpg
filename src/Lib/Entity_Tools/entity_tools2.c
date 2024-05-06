/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** entity_tools2
*/

#include "rpg.h"

static bool hitbox_collision(rpg_t *rpg, sfVector2f point)
{
    unsigned int col = point.x / WIDTH;
    unsigned int row = point.y / HEIGHT;

    if (col >= rpg->collision->cols || row >= rpg->collision->rows)
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

bool entity_see_enemy(rpg_t *rpg, entity_t *entity, entity_t *enemy)
{
    if (entity_look_at_enemy(entity, enemy)) {
        if (hitbox_in_detection(enemy->common->zones->hitbox,
            entity->common->zones->l_radius, entity->common->pos))
            return !is_in_line_of_sight(rpg, entity->common->pos,
                enemy->common->pos);
        else
            return false;
    }
    if (!is_discreet(enemy)) {
        if (hitbox_in_detection(enemy->common->zones->hitbox,
            entity->common->zones->m_radius, entity->common->pos))
            return !is_in_line_of_sight(rpg, entity->common->pos,
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
