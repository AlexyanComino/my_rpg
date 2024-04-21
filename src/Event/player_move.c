/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** move_player
*/

#include "rpg.h"

static void get_newpos_and_newx(warrior_t *player, sfVector2f *newPos,
    float dt)
{
    float speed = player->state == WALK ? player->attributes->speed / 3 :
        player->attributes->speed;

    if (sfKeyboard_isKeyPressed(sfKeyQ)) {
        player->x = LEFT;
        newPos->x -= speed * dt;
    } else if (sfKeyboard_isKeyPressed(sfKeyD)) {
        player->x = RIGHT;
        newPos->x += speed * dt;
    }
}

static void update_player_x(rpg_t *rpg, warrior_t *player)
{
    sfVector2f newPos = player->pos;
    sfIntRect newHitbox;

    get_newpos_and_newx(player, &newPos, rpg->win->dt);
    newHitbox = get_hitbox_warrior(newPos);
    if (!is_warrior_hitbox_collide(rpg, player, newHitbox)) {
        player->pos.x = newPos.x;
        player->zones->hitbox = newHitbox;
    }
}

//
static void get_newpos_and_newy(warrior_t *player, sfVector2f *newPos,
    float dt)
{
    float speed = player->state == WALK ? player->attributes->speed / 3 :
        player->attributes->speed;

    if (sfKeyboard_isKeyPressed(sfKeyZ) && sfKeyboard_isKeyPressed(sfKeyS)) {
        player->y = NONE;
        return;
    }
    if (sfKeyboard_isKeyPressed(sfKeyZ)) {
        player->y = UP;
        newPos->y -= speed * dt;
        return;
    }
    if (sfKeyboard_isKeyPressed(sfKeyS)) {
        player->y = DOWN;
        newPos->y += speed * dt;
        return;
    }
    player->y = NONE;
}

static void update_player_y(rpg_t *rpg, warrior_t *player)
{
    sfVector2f newPos = player->pos;
    sfIntRect newHitbox;

    get_newpos_and_newy(player, &newPos, rpg->win->dt);
    newHitbox = get_hitbox_warrior(newPos);
    if (!is_warrior_hitbox_collide(rpg, player, newHitbox)) {
        player->pos.y = newPos.y;
        player->zones->hitbox = newHitbox;
    }
}

//
void player_move(rpg_t *rpg)
{
    warrior_t *player = rpg->lwarrior->warrior;
    bool is_walking = false;

    if (sfKeyboard_isKeyPressed(sfKeyLControl))
            is_walking = true;
    if (sfKeyboard_isKeyPressed(sfKeyZ) || sfKeyboard_isKeyPressed(sfKeyS) ||
        sfKeyboard_isKeyPressed(sfKeyQ) || sfKeyboard_isKeyPressed(sfKeyD)) {
            player->state = (is_walking) ? WALK : RUN;
    } else if (player->state != ATTACK)
        player->state = IDLE;
    update_player_x(rpg, player);
    update_player_y(rpg, player);
}
