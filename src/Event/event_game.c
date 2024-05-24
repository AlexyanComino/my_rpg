/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** event_game
*/

#include "rpg.h"

static void event_player_warrior(rpg_t *rpg, entity_t *player)
{
    if (rpg->event.key.code == sfKeySpace &&
        is_attacking(player)) {
        player->spe->warrior->max_line_attack = 1;
    }
}

static void event_player_pawn(rpg_t *rpg, entity_t *player)
{
    if (rpg->event.key.code == sfKeyA) {
        player->common->state = ST_WORK;
        init_entity_action(player);
    }
    if (rpg->event.key.code == sfKeyR) {
        player->common->state = IDLE_CARRY;
        init_entity_action(player);
    }
}

static arrow_dir_t get_arrow_right_or_left(entity_t *player)
{
    if (player->common->x == RIGHT)
        return RIGHT_ARROW;
    else
        return LEFT_ARROW;
}

static arrow_dir_t get_player_arrow_dir(entity_t *player)
{
    bool top = (bool)sfKeyboard_isKeyPressed(sfKeyZ);
    bool down = (bool)sfKeyboard_isKeyPressed(sfKeyS);
    bool left = (bool)sfKeyboard_isKeyPressed(sfKeyQ);
    bool right = (bool)sfKeyboard_isKeyPressed(sfKeyD);

    if ((!top && !down && !left && !right) || (!top && !down && !left && right)
        || (!top && !down && left && !right)) {
        return get_arrow_right_or_left(player);
    }
    if (top && !down && !left && !right)
        return UP_ARROW;
    if (top && (left || right))
        return UP_RIGHT_ARROW;
    if (down && !top && !left && !right)
        return DOWN_ARROW;
    if (down && (left || right))
        return DOWN_RIGHT_ARROW;
    return RIGHT_ARROW;
}

static void event_entity(rpg_t *rpg, entity_t *player, sfKeyCode key)
{
    if (player->type == WARRIOR && is_alive(player))
        event_player_warrior(rpg, player);
    if (player->type == PAWN && !in_action(player) && is_alive(player))
        event_player_pawn(rpg, player);
    if (key == sfKeySpace && !in_action(player) &&
        player->common->state != INTERACT && is_alive(player) &&
        (player->type != TNT || !player->spe->tnt->is_launched)) {
        if (player->type == ARCHER)
            player->spe->archer->arrow_dir = get_player_arrow_dir(player);
        player->common->state = ST_ATT;
        init_entity_action(player);
    }
}

static void event_other_key(rpg_t *rpg, entity_t *player, sfKeyCode key)
{
    if (key == sfKeyP)
        printf("Player pos: %f, %f\n", player->common->pos.x,
            player->common->pos.y);
    if (key == sfKeyB)
        rpg->plus = !rpg->plus;
    if (key == sfKeyT) {
        rpg->gamestate = MAP;
        init_map_pos(rpg);
    }
    if (key == sfKeyRControl && sfKeyboard_isKeyPressed(sfKeyLControl))
        rpg->debug = !rpg->debug;
}

void event_game(rpg_t *rpg)
{
    entity_t *player = get_player(rpg);
    sfKeyCode key = rpg->event.key.code;

    quest_event(rpg);
    if (rpg->event.type != sfEvtKeyPressed)
        return;
    event_entity(rpg, player, key);
    event_other_key(rpg, player, key);
    event_chests(rpg, key);
    if (rpg->event.key.code == sfKeyV)
        save(rpg, rpg->save_index + 1);
}
