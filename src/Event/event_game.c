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

static void chest_is_interacted(rpg_t *rpg, entity_t *player, int i)
{
    if (rpg->chests[i]->item_type != OTHER &&
        !rpg->chests[i]->is_interacted && !rpg->chests[i]->is_recieved) {
        quest_done_item(rpg, rpg->chests[i]->item_name);
        add_item_from_type(rpg, rpg->chests[i]->item_name,
            rpg->chests[i]->item_type);
        rpg->chests[i]->is_recieved = true;
    }
    rpg->chests[i]->is_interacted = !rpg->chests[i]->is_interacted;
    player->common->state = (rpg->chests[i]->is_interacted) ?
        INTERACT : IDLE;
}

static void check_event_chests(rpg_t *rpg, sfKeyCode key)
{
    entity_t *player = get_player(rpg);

    if (rpg->gamestate != GAME || key != sfKeyE)
        return;
    for (unsigned int i = 0; i < rpg->chests_size; i++) {
        if (!intrect_is_in_view(rpg, rpg->chests[i]->rect))
            continue;
        if (sfIntRect_intersects(&rpg->chests[i]->rect,
            &player->common->zones->hitbox_attack, NULL)) {
            return chest_is_interacted(rpg, player, i);
        }
    }
}

void event_game(rpg_t *rpg)
{
    entity_t *player = get_player(rpg);
    sfKeyCode key = rpg->event.key.code;

    quest_event(rpg);
    if (rpg->event.type == sfEvtMouseButtonPressed)
        printf("Mouse pos: %f, %f\n", rpg->win->mouse_pos.x,
            rpg->win->mouse_pos.y);
    if (rpg->event.type != sfEvtKeyPressed)
        return;
    event_entity(rpg, player, key);
    event_other_key(rpg, player, key);
    check_event_chests(rpg, key);
}
