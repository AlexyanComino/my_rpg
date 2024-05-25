/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_entity_pos
*/

#include "rpg.h"

sfVector2f get_movement(sfVector2f center_target, sfVector2f center_entity,
    float distance, int speed)
{
    sfVector2f direction =
        {center_target.x - center_entity.x,
        center_target.y - center_entity.y};

    return (sfVector2f)
        {direction.x / distance * speed, direction.y / distance * speed};
}

static void update_side_x(entity_t *entity, sfVector2f movement)
{
    if (movement.x < 0)
        entity->common->x = LEFT;
    else if (movement.x > 0)
        entity->common->x = RIGHT;
}

static void update_side_y(entity_t *entity, sfVector2f movement)
{
    bool y_is_sup = fabs(movement.y) > fabs(movement.x);

    if (movement.y > 0) {
        if (y_is_sup)
            entity->common->y = DOWN;
        else
            entity->common->y = NONE;
        return;
    }
    if (movement.y < 0) {
        if (y_is_sup)
            entity->common->y = UP;
        else
            entity->common->y = NONE;
        return;
    }
    entity->common->y = NONE;
}

static void get_new_pos_x(entity_t *entity, sfVector2f *newPos,
    sfVector2f movement, float dt)
{
    update_side_x(entity, movement);
    if (movement.x < 0) {
        newPos->x += movement.x * dt;
    } else if (movement.x > 0) {
        newPos->x += movement.x * dt;
    }
}

static void update_entity_x(rpg_t *rpg, entity_t *entity, sfVector2f movement)
{
    sfVector2f newPos = entity->common->pos;
    sfIntRect newHitbox;

    get_new_pos_x(entity, &newPos, movement, rpg->win->dt);
    newHitbox = entity->get_hitbox_foot(newPos, entity->common->scale);
    if (!is_entity_hitbox_collide(rpg, entity, newHitbox)) {
        entity->common->pos.x = newPos.x;
    }
}

static void get_new_pos_y(entity_t *entity, sfVector2f *newPos,
    sfVector2f movement, float dt)
{
    update_side_y(entity, movement);
    if (movement.y < 0) {
        newPos->y += movement.y * dt;
    } else if (movement.y > 0) {
        newPos->y += movement.y * dt;
    }
}

static void update_entity_y(rpg_t *rpg, entity_t *entity, sfVector2f movement)
{
    sfVector2f newPos = entity->common->pos;
    sfIntRect newHitbox;

    get_new_pos_y(entity, &newPos, movement, rpg->win->dt);
    newHitbox = entity->get_hitbox_foot(newPos, entity->common->scale);
    if (!is_entity_hitbox_collide(rpg, entity, newHitbox)) {
        entity->common->pos.y = newPos.y;
    }
}

void update_entity_pos(rpg_t *rpg, entity_t *entity, sfVector2f movement)
{
    update_entity_x(rpg, entity, movement);
    update_entity_y(rpg, entity, movement);
}
