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
    float speed = player->common->state == WALK ?
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
    if (!is_entity_hitbox_collide(rpg, player, newHitbox)) {
        player->common->pos.x = newPos.x;
        player->common->zones->hitbox = newHitbox;
    }
}

//
static void get_newpos_and_newy(entity_t *player, sfVector2f *newPos,
    float dt)
{
    float speed = player->common->state == WALK ?
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
    if (!is_entity_hitbox_collide(rpg, player, newHitbox)) {
        player->common->pos.y = newPos.y;
        player->common->zones->hitbox = newHitbox;
    }
}

//
void player_move(rpg_t *rpg)
{
    entity_t *player = rpg->ent[0];
    bool is_walking = false;
    sfVector2f oldPos = player->common->pos;

    if (sfKeyboard_isKeyPressed(sfKeyLControl))
            is_walking = true;
    if (sfKeyboard_isKeyPressed(sfKeyZ) || sfKeyboard_isKeyPressed(sfKeyS) ||
        sfKeyboard_isKeyPressed(sfKeyQ) || sfKeyboard_isKeyPressed(sfKeyD)) {
            player->common->state = (is_walking) ? WALK : RUN;
    } else if (not_attacking(player))
        player->common->state = IDLE;
    update_player_x(rpg, player);
    update_player_y(rpg, player);
    if (oldPos.x != player->common->pos.x ||
        oldPos.y != player->common->pos.y) {
        update_interface_pos(rpg, player, oldPos);
    }
}
