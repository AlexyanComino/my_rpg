/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** move_player
*/

#include "rpg.h"

static void get_newpos_and_newx(entity_t *player, sfVector2f *newPos,
    float dt)
{
    float speed = is_slow(player) ?
        player->common->attributes->speed / 2 :
        player->common->attributes->speed;

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

    get_newpos_and_newx(player, &newPos, rpg->win->dt);
    newHitbox = player->get_hitbox(newPos);
    if (!is_entity_hitbox_collide(rpg, player, newHitbox) ||
        (rpg->debug && player->common->state == WALK)) {
        player->common->pos.x = newPos.x;
        player->common->zones->hitbox = newHitbox;
    }
}

//
static void get_newpos_and_newy(entity_t *player, sfVector2f *newPos,
    float dt)
{
    float speed = is_slow(player) ?
        player->common->attributes->speed / 2 :
        player->common->attributes->speed;

    if (sfKeyboard_isKeyPressed(sfKeyZ) && sfKeyboard_isKeyPressed(sfKeyS)) {
        player->common->y = NONE;
        return;
    }
    if (sfKeyboard_isKeyPressed(sfKeyZ)) {
        player->common->y = UP;
        newPos->y -= speed * dt;
        return;
    }
    if (sfKeyboard_isKeyPressed(sfKeyS)) {
        player->common->y = DOWN;
        newPos->y += speed * dt;
        return;
    }
    player->common->y = NONE;
}

static void update_player_y(rpg_t *rpg, entity_t *player)
{
    sfVector2f newPos = player->common->pos;
    sfIntRect newHitbox;

    get_newpos_and_newy(player, &newPos, rpg->win->dt);
    newHitbox = player->get_hitbox(newPos);
    if (!is_entity_hitbox_collide(rpg, player, newHitbox) ||
        (rpg->debug && player->common->state == WALK)) {
        player->common->pos.y = newPos.y;
        player->common->zones->hitbox = newHitbox;
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
    if (sfKeyboard_isKeyPressed(sfKeyLControl))
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

void player_move(rpg_t *rpg)
{
    entity_t *player = rpg->ent[0];
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
