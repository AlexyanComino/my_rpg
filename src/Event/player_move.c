/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** move_player
*/

#include "rpg.h"

static void check_player_is_right(warrior_t *player, sfVector2f *newPos)
{
    if (player->x == RIGHT) {
        newPos->x += WARRIOR_WIDTH;
    }
}

static void check_player_is_left(warrior_t *player, sfVector2f *newPos)
{
    if (player->x == LEFT) {
        newPos->x -= WARRIOR_WIDTH;
    }
}

static void get_newpos_and_newx(warrior_t *player, sfVector2f *newPos,
    float dt)
{
    if (sfKeyboard_isKeyPressed(sfKeyQ)) {
        check_player_is_right(player, newPos);
        player->x = LEFT;
        newPos->x -= player->attributes->speed * dt;
    } else if (sfKeyboard_isKeyPressed(sfKeyD)) {
        check_player_is_left(player, newPos);
        player->x = RIGHT;
        newPos->x += player->attributes->speed * dt;
    }
}

static void update_player_x(rpg_t *rpg, warrior_t *player, float dt)
{
    sfVector2f newPos = player->pos;
    sfIntRect newHitbox = player->zones->hitbox;

    get_newpos_and_newx(player, &newPos, dt);
    newHitbox = get_hitbox_warrior(newPos, player->x);
    if (!is_warrior_hitbox_collide(rpg, player, newHitbox)) {
        player->pos.x = newPos.x;
        player->zones->hitbox = newHitbox;
    }
}

//
static void get_newpos_and_newy(warrior_t *player, sfVector2f *newPos,
    float dt)
{
    if (sfKeyboard_isKeyPressed(sfKeyZ) && sfKeyboard_isKeyPressed(sfKeyS)) {
        player->y = NONE;
        return;
    }
    if (sfKeyboard_isKeyPressed(sfKeyZ)) {
        player->y = UP;
        newPos->y -= player->attributes->speed * dt;
        return;
    }
    if (sfKeyboard_isKeyPressed(sfKeyS)) {
        player->y = DOWN;
        newPos->y += player->attributes->speed * dt;
        return;
    }
    player->y = NONE;
}

static void update_player_y(rpg_t *rpg, warrior_t *player, float dt)
{
    sfVector2f newPos = player->pos;
    sfIntRect newHitbox = player->zones->hitbox;

    get_newpos_and_newy(player, &newPos, dt);
    newHitbox = get_hitbox_warrior(newPos, player->x);
    if (!is_warrior_hitbox_collide(rpg, player, newHitbox)) {
        player->pos.y = newPos.y;
        player->zones->hitbox = newHitbox;
    }
}

//
void player_move(rpg_t *rpg, float dt)
{
    warrior_t *player = rpg->lwarrior->warrior;

    if (sfKeyboard_isKeyPressed(sfKeyZ) || sfKeyboard_isKeyPressed(sfKeyS) ||
    sfKeyboard_isKeyPressed(sfKeyQ) || sfKeyboard_isKeyPressed(sfKeyD)) {
        player->state = WALK;
    } else if (player->state != ATTACK)
        player->state = IDLE;
    update_player_x(rpg, player, dt);
    update_player_y(rpg, player, dt);
}
