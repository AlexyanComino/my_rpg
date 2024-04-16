/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** move_player
*/

#include "rpg.h"

static void update_hitboxs_pos(warrior_t *warrior)
{
    warrior->hitbox = get_hitbox_warrior(warrior->pos, warrior->x);
    sfRectangleShape_setPosition(warrior->rect_hitbox,
        (sfVector2f){warrior->hitbox.left, warrior->hitbox.top});
    if (sfRectangleShape_getSize(warrior->rect_hitbox).x !=
        warrior->hitbox.width)
        sfRectangleShape_setSize(warrior->rect_hitbox,
        (sfVector2f){warrior->hitbox.width, warrior->hitbox.height});
    warrior->hitbox_attack = get_hitbox_attack(warrior->pos, warrior->x,
        warrior->y);
    sfRectangleShape_setPosition(warrior->rect_hitbox_attack,
        (sfVector2f){warrior->hitbox_attack.left, warrior->hitbox_attack.top});
    if (sfRectangleShape_getSize(warrior->rect_hitbox_attack).x !=
        warrior->hitbox_attack.width)
        sfRectangleShape_setSize(warrior->rect_hitbox_attack, (sfVector2f)
        {warrior->hitbox_attack.width, warrior->hitbox_attack.height});
}

static void check_player_is_right(warrior_t *player, sfVector2f *newPos)
{
    if (player->x == RIGHT) {
        sfSprite_setScale(player->sprite, (sfVector2f){-1, 1});
        newPos->x += WARRIOR_WIDTH;
    }
}

static void check_player_is_left(warrior_t *player, sfVector2f *newPos)
{
    if (player->x == LEFT) {
        sfSprite_setScale(player->sprite, (sfVector2f){1, 1});
        newPos->x -= WARRIOR_WIDTH;
    }
}

static void get_newpos_and_newx(warrior_t *player, sfVector2f *newPos,
    float dt)
{
    if (sfKeyboard_isKeyPressed(sfKeyQ)) {
        check_player_is_right(player, newPos);
        player->x = LEFT;
        newPos->x -= PLAYER_SPEED * dt;
    } else if (sfKeyboard_isKeyPressed(sfKeyD)) {
        check_player_is_left(player, newPos);
        player->x = RIGHT;
        newPos->x += PLAYER_SPEED * dt;
    }
}

static void update_player_x(rpg_t *rpg, warrior_t *player, float dt)
{
    sfVector2f newPos = player->pos;
    sfIntRect newHitbox = player->hitbox;

    get_newpos_and_newx(player, &newPos, dt);
    newHitbox = get_hitbox_warrior(newPos, player->x);
    if (!is_warrior_hitbox_collide(rpg, player, newHitbox)) {
        player->pos.x = newPos.x;
        player->hitbox = newHitbox;
        update_hitboxs_pos(player);
    }
}

static void get_newpos_and_newy(warrior_t *player, sfVector2f *newPos,
    float dt)
{
    if (sfKeyboard_isKeyPressed(sfKeyZ) && sfKeyboard_isKeyPressed(sfKeyS)) {
        player->y = NONE;
        return;
    }
    if (sfKeyboard_isKeyPressed(sfKeyZ)) {
        player->y = UP;
        newPos->y -= PLAYER_SPEED * dt;
        return;
    }
    if (sfKeyboard_isKeyPressed(sfKeyS)) {
        player->y = DOWN;
        newPos->y += PLAYER_SPEED * dt;
        return;
    }
    player->y = NONE;
}

static void update_player_y(rpg_t *rpg, warrior_t *player, float dt)
{
    sfVector2f newPos = player->pos;
    sfIntRect newHitbox = player->hitbox;

    get_newpos_and_newy(player, &newPos, dt);
    newHitbox = get_hitbox_warrior(newPos, player->x);
    if (!is_warrior_hitbox_collide(rpg, player, newHitbox)) {
        player->pos.y = newPos.y;
        player->hitbox = newHitbox;
        update_hitboxs_pos(player);
    }
}

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
    sfSprite_setPosition(player->sprite, player->pos);
}
