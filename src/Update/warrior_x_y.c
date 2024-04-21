/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** warrior_x_y
*/

#include "rpg.h"

void update_side_x(warrior_t *warrior, sfVector2f movement)
{
    if (movement.x < 0)
        warrior->x = LEFT;
    else if (movement.x > 0)
        warrior->x = RIGHT;
}

void update_side_y(warrior_t *warrior, sfVector2f movement)
{
    bool y_is_sup = fabs(movement.y) > fabs(movement.x);

    if (movement.y > 0) {
        if (y_is_sup)
            warrior->y = DOWN;
        else
            warrior->y = NONE;
    } else if (movement.y < 0) {
        if (y_is_sup)
            warrior->y = UP;
        else
            warrior->y = NONE;
    } else {
        warrior->y = NONE;
    }
}

static void get_new_pos_x(warrior_t *warrior, sfVector2f *newPos,
    sfVector2f movement, float dt)
{
    update_side_x(warrior, movement);
    if (movement.x < 0) {
        newPos->x += movement.x * dt;
    } else if (movement.x > 0) {
        newPos->x += movement.x * dt;
    }
}

void update_warrior_x(rpg_t *rpg, warrior_t *warrior, sfVector2f movement)
{
    sfVector2f newPos = warrior->pos;
    sfIntRect newHitbox;

    get_new_pos_x(warrior, &newPos, movement, rpg->win->dt);
    newHitbox = get_hitbox_warrior(newPos);
    if (!is_warrior_hitbox_collide(rpg, warrior, newHitbox)) {
        warrior->pos.x = newPos.x;
        warrior->zones->hitbox = newHitbox;
    }
}

static void get_new_pos_y(warrior_t *warrior, sfVector2f *newPos,
    sfVector2f movement, float dt)
{
    update_side_y(warrior, movement);
    if (movement.y < 0) {
        newPos->y += movement.y * dt;
    } else if (movement.y > 0) {
        newPos->y += movement.y * dt;
    }
}

void update_warrior_y(rpg_t *rpg, warrior_t *warrior, sfVector2f movement)
{
    sfVector2f newPos = warrior->pos;
    sfIntRect newHitbox;

    get_new_pos_y(warrior, &newPos, movement, rpg->win->dt);
    newHitbox = get_hitbox_warrior(newPos);
    if (!is_warrior_hitbox_collide(rpg, warrior, newHitbox)) {
        warrior->pos.y = newPos.y;
        warrior->zones->hitbox = newHitbox;
    }
}
