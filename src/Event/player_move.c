/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** move_player
*/

#include "rpg.h"

static float get_player_speed(rpg_t *rpg, entity_t *player)
{
    if (rpg->modes->k)
        return player->common->attributes->speed * 4;
    else if (is_slow(player))
        return player->common->attributes->speed / 2;
    return player->common->attributes->speed;
}

static void get_newpos_and_newx(rpg_t *rpg, entity_t *player,
    sfVector2f *newPos, float dt)
{
    float speed = get_player_speed(rpg, player);

    if (sfKeyboard_isKeyPressed(sfKeyZ) || sfKeyboard_isKeyPressed(sfKeyS))
        speed /= sqrt(2.0f);
    if (sfKeyboard_isKeyPressed(sfKeyQ)) {
        player->common->x = LEFT;
        newPos->x -= speed * dt;
    } else if (sfKeyboard_isKeyPressed(sfKeyD)) {
        player->common->x = RIGHT;
        newPos->x += speed * dt;
    }
}

static void update_player_x(rpg_t *rpg, entity_t *player)
{
    sfVector2f newPos = player->common->pos;
    sfIntRect newHitbox;

    get_newpos_and_newx(rpg, player, &newPos, rpg->win->dt);
    newHitbox = player->get_hitbox_foot(newPos, player->common->scale);
    if (!is_entity_hitbox_collide(rpg, player, newHitbox) ||
        rpg->modes->debug) {
        player->common->pos.x = newPos.x;
    }
}

//
static void get_newpos_and_newy(rpg_t *rpg, entity_t *player,
    sfVector2f *newPos, float dt)
{
    float speed = get_player_speed(rpg, player);

    if (sfKeyboard_isKeyPressed(sfKeyQ) || sfKeyboard_isKeyPressed(sfKeyD))
        speed /= sqrt(2.0f);
    if (sfKeyboard_isKeyPressed(sfKeyZ) && sfKeyboard_isKeyPressed(sfKeyS)) {
        player->common->y = NONE;
        return;
    }
    if (sfKeyboard_isKeyPressed(sfKeyZ)) {
        player->common->y = UP;
        newPos->y -= speed * dt;
    } else if (sfKeyboard_isKeyPressed(sfKeyS)) {
        player->common->y = DOWN;
        newPos->y += speed * dt;
    } else {
        player->common->y = NONE;
    }
}

static void update_player_y(rpg_t *rpg, entity_t *player)
{
    sfVector2f newPos = player->common->pos;
    sfIntRect newHitbox;

    get_newpos_and_newy(rpg, player, &newPos, rpg->win->dt);
    newHitbox = player->get_hitbox_foot(newPos, player->common->scale);
    if (!is_entity_hitbox_collide(rpg, player, newHitbox) ||
        rpg->modes->debug) {
        player->common->pos.y = newPos.y;
    }
}

//
static void check_player_stun(entity_t *player, sfVector2f oldPos)
{
    if (fabs(player->common->pos.x - oldPos.x) < 0.1 &&
        fabs(player->common->pos.y - oldPos.y) < 0.1) {
        if (player->type == PAWN && (player->common->state == MOVE_CARRY ||
            player->common->state == IDLE_CARRY))
            player->common->state = IDLE_CARRY;
        else
            player->common->state = IDLE;
    }
}

static void event_player_move(entity_t *player)
{
    bool is_walking = false;

    if (in_action(player))
        return;
    if (sfKeyboard_isKeyPressed(sfKeyLShift))
            is_walking = true;
    if (sfKeyboard_isKeyPressed(sfKeyZ) || sfKeyboard_isKeyPressed(sfKeyS) ||
        sfKeyboard_isKeyPressed(sfKeyQ) || sfKeyboard_isKeyPressed(sfKeyD)) {
        if (player->type == PAWN && (player->common->state == IDLE_CARRY ||
            player->common->state == MOVE_CARRY) && is_walking)
            player->common->state = MOVE_CARRY;
        else
            player->common->state = (is_walking) ? WALK : RUN;
    } else {
        if (player->type == PAWN && (player->common->state == MOVE_CARRY ||
            player->common->state == IDLE_CARRY))
            player->common->state = IDLE_CARRY;
        else
            player->common->state = IDLE;
    }
}

static void player_move(rpg_t *rpg)
{
    entity_t *player = get_player(rpg);
    sfVector2f oldPos = player->common->pos;

    event_player_move(player);
    update_player_x(rpg, player);
    update_player_y(rpg, player);
    check_player_stun(player, oldPos);
    if (oldPos.x != player->common->pos.x ||
        oldPos.y != player->common->pos.y) {
        update_interface_pos(rpg, player, oldPos);
    }
}

void player_move_event(rpg_t *rpg)
{
    entity_t *player = get_player(rpg);

    if (!in_action(player) && is_alive(player) && !is_stunned(player) &&
        player->common->state != INTERACT && !rpg->vict->is_win)
        player_move(rpg);
}
