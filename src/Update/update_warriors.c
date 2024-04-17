/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_warrior
*/

#include "rpg.h"

static x_warrior_t get_player_side(warrior_t *player, warrior_t *tmp)
{
    if (player->pos.x < tmp->pos.x) {
        if (tmp->x == RIGHT)
            tmp->pos.x += WARRIOR_WIDTH;
        return LEFT;
    } else {
        if (tmp->x == LEFT)
            tmp->pos.x -= WARRIOR_WIDTH;
        return RIGHT;
    }
}

static void update_exclam_detection(sfIntRect hitbox, warrior_t *tmp)
{
    if (hitbox_in_detection(hitbox, tmp->exclam->radius,
        tmp->exclam->circle_pos)) {
        tmp->exclam->is_detecting = true;
        if (tmp->exclam->is_display == 0) {
            tmp->exclam->is_display = 1;
            tmp->exclam->rect.left = 0;
            tmp->exclam->rect.top = 0;
        }
    } else {
        tmp->exclam->is_detecting = false;
    }
}

static void is_detecting_warrior(warrior_t *player, warrior_t *tmp)
{
    sfIntRect hitbox = player->zones->hitbox;

    update_exclam_detection(hitbox, tmp);
    if (hitbox_in_detection(hitbox, tmp->inter->radius,
        tmp->inter->circle_pos)) {
        tmp->inter->is_detecting = true;
        if (tmp->inter->is_display == 0) {
            tmp->x = get_player_side(player, tmp);
            tmp->inter->is_display = 1;
            tmp->inter->rect.left = 0;
            tmp->inter->rect.top = 0;
        }
    } else {
        tmp->inter->is_detecting = false;
    }
}

static sfVector2f get_exclam_pos(warrior_t *warrior)
{
    if (warrior->x == RIGHT)
        return (sfVector2f){warrior->pos.x + WARRIOR_WIDTH / 3,
            warrior->pos.y - WARRIOR_WIDTH / 3};
    else
        return (sfVector2f){warrior->pos.x - 8 * WARRIOR_WIDTH / 9,
            warrior->pos.y - WARRIOR_WIDTH / 3};
}

static sfVector2f get_inter_pos(warrior_t *warrior)
{
    if (warrior->x == RIGHT)
        return (sfVector2f){warrior->pos.x + WARRIOR_WIDTH / 2,
            warrior->pos.y - WARRIOR_WIDTH / 3};
    else
        return (sfVector2f){warrior->pos.x - 8 * WARRIOR_WIDTH / 9,
            warrior->pos.y - WARRIOR_WIDTH / 3};
}

static void update_marks_pos(warrior_t *warrior)
{
    if (!warrior->exclam->is_display) {
        warrior->exclam->pos = get_exclam_pos(warrior);
        sfSprite_setPosition(warrior->exclam->sprite, warrior->exclam->pos);
    }
    if (!warrior->inter->is_display) {
        warrior->inter->pos = get_inter_pos(warrior);
        sfSprite_setPosition(warrior->inter->sprite, warrior->inter->pos);
    }
}

static void update_pnj_warrior(warrior_t *player, warrior_t *tmp)
{
    is_detecting_warrior(player, tmp);
    update_marks_pos(tmp);
}

void update_warriors(rpg_t *rpg)
{
    lwarrior_t *tmp = rpg->lwarrior;
    warrior_t *player = rpg->lwarrior->warrior;

    while (tmp) {
        update_all_warriors(rpg, tmp->warrior);
        if (tmp->warrior != player)
            update_pnj_warrior(player, tmp->warrior);
        tmp = tmp->next;
    }
}
