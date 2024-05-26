/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** shoot_arrow
*/

#include "rpg.h"

static bool is_point_collide(sfVector2f point, rpg_t *rpg, int col, int row)
{
    if (col < 0 || col >= (int)rpg->collision->cols)
        return (false);
    if (row < 0 || row >= (int)rpg->collision->rows)
        return (false);
    for (unsigned int i = 0; i <
        rpg->collision->regions[col][row]->size; i++) {
        rpg->collision->rect.left =
            rpg->collision->regions[col][row]->pos[i].x;
        rpg->collision->rect.top =
            rpg->collision->regions[col][row]->pos[i].y;
        if (!intrect_is_in_view(rpg, rpg->collision->rect))
            continue;
        if (sfIntRect_contains(&rpg->collision->rect, (int)point.x,
            (int)point.y))
            return (true);
    }
    return false;
}

// Fonction pour vérifier la collision d'un point avec une liste de rectangles
bool point_is_collide_with_rects(sfVector2f point, rpg_t *rpg)
{
    int col = point.x / WIDTH;
    int row = point.y / HEIGHT;

    if (col >= (int)rpg->collision->cols || row >= (int)rpg->collision->rows)
        return false;
    if (is_point_collide(point, rpg, col, row) ||
        is_point_collide(point, rpg, col + 1, row) ||
        is_point_collide(point, rpg, col, row + 1) ||
        is_point_collide(point, rpg, col + 1, row + 1) ||
        is_point_collide(point, rpg, col - 1, row) ||
        is_point_collide(point, rpg, col, row - 1) ||
        is_point_collide(point, rpg, col - 1, row - 1) ||
        is_point_collide(point, rpg, col + 1, row - 1) ||
        is_point_collide(point, rpg, col - 1, row + 1))
        return true;
    rpg->collision->rect.left = 0;
    rpg->collision->rect.top = 0;
    return false;
}

static bool point_is_in_view(rpg_t *rpg, sfVector2f point)
{
    sfVector2f view_size = {WIDTH, HEIGHT};
    sfVector2f view_center = get_player(rpg)->common->pos;

    if (point.x < view_center.x - view_size.x ||
        point.x > view_center.x + view_size.x)
        return false;
    if (point.y < view_center.y - view_size.y ||
        point.y > view_center.y + view_size.y)
        return false;
    return true;
}

sfVector2f get_last_point_collision(sfVector2f startPoint,
    sfVector2f direction, rpg_t *rpg, entity_t *entity)
{
    sfVector2f endPoint = startPoint;
    sfVector2f nextPoint = startPoint;

    while (sfIntRect_contains(&entity->common->zones->hitbox,
        endPoint.x, endPoint.y) || (!point_is_collide_with_rects(endPoint, rpg)
        && point_is_in_view(rpg, endPoint))) {
        nextPoint.x = endPoint.x + direction.x;
        nextPoint.y = endPoint.y + direction.y;
        endPoint = nextPoint;
    }
    return endPoint;
}

static sfVector2f get_direction_arrow_dir(arrow_dir_t dir)
{
    if (dir == UP_ARROW)
        return (sfVector2f){0, -1};
    if (dir == DOWN_ARROW)
        return (sfVector2f){0, 1};
    if (dir == LEFT_ARROW)
        return (sfVector2f){-1, 0};
    if (dir == RIGHT_ARROW)
        return (sfVector2f){1, 0};
    if (dir == UP_LEFT_ARROW)
        return (sfVector2f){-1, -1};
    if (dir == UP_RIGHT_ARROW)
        return (sfVector2f){1, -1};
    if (dir == DOWN_LEFT_ARROW)
        return (sfVector2f){-1, 1};
    if (dir == DOWN_RIGHT_ARROW)
        return (sfVector2f){1, 1};
    return (sfVector2f){0, 0};
}

static float get_arrow_speed(rpg_t *rpg)
{
    return 900 * rpg->win->dt;
}

static float get_arrow_rotation(sfVector2f direction)
{
    return atan2(direction.y, direction.x) * 180 / M_PI;
}

static arrows_t *get_new_arrow(rpg_t *rpg, entity_t *entity, arrow_dir_t dir)
{
    arrows_t *new = malloc(sizeof(arrows_t));
    sfVector2f pos = entity->common->pos;
    sfVector2f direction = get_direction_arrow_dir(dir);
    float speed = get_arrow_speed(rpg);
    float rotation = get_arrow_rotation(direction);

    new->pos = entity->common->pos;
    new->end = get_last_point_collision(pos, direction, rpg, entity);
    new->dir = get_movement(new->end, new->pos,
        get_distance(new->pos, new->end), speed);
    new->anim = init_anim("assets/Entities/Archer/Arrow.png",
        ARROW_WIDTH, ARROW_WIDTH);
    sfSprite_setRotation(new->anim->sprite, rotation);
    sfSprite_setScale(new->anim->sprite, (sfVector2f){entity->common->scale,
        entity->common->scale});
    new->vertices[0] = (sfVertex){.position = new->pos, .color = sfWhite};
    new->vertices[1] = (sfVertex){.position = new->end, .color = sfWhite};
    new->state = FLY_ARROW;
    new->myclock = init_my_clock();
    return new;
}

void shoot_arrow(rpg_t *rpg, entity_t *entity, arrow_dir_t dir)
{
    arrows_t *tmp = entity->spe->archer->arrows;
    arrows_t *new_arrow = get_new_arrow(rpg, entity, dir);

    new_arrow->next = NULL;
    while (tmp && tmp->next != NULL)
        tmp = tmp->next;
    if (tmp == NULL) {
        entity->spe->archer->arrows = new_arrow;
    } else {
        tmp->next = new_arrow;
    }
}
