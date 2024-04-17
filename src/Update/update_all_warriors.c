/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_all_warriors
*/

#include "rpg.h"

//
static void update_warrior_pos(warrior_t *warrior)
{
    if (IS_ALIVE(warrior)) {
        sfSprite_setPosition(warrior->sprite, warrior->pos);
        sfCircleShape_setPosition(warrior->exclam->circle,
            warrior->exclam->circle_pos);
        sfCircleShape_setPosition(warrior->inter->circle,
            warrior->inter->circle_pos);
        sfCircleShape_setPosition(warrior->zones->circle_reset,
            warrior->zones->circle_reset_pos);
    } else if (warrior->state == DEAD) {
        sfSprite_setPosition(warrior->death->sprite_dead,
            warrior->death->dead_pos);
    }
}

static void update_hitboxs_pos(warrior_t *warrior)
{
    warrior->zones->hitbox = get_hitbox_warrior(warrior->pos, warrior->x);
    sfRectangleShape_setPosition(warrior->zones->rect_hitbox,
        (sfVector2f){warrior->zones->hitbox.left, warrior->zones->hitbox.top});
    if (sfRectangleShape_getSize(warrior->zones->rect_hitbox).x !=
        warrior->zones->hitbox.width)
        sfRectangleShape_setSize(warrior->zones->rect_hitbox, (sfVector2f)
        {warrior->zones->hitbox.width, warrior->zones->hitbox.height});
    warrior->zones->hitbox_attack = get_hitbox_attack(warrior->pos, warrior->x,
        warrior->y);
    sfRectangleShape_setPosition(warrior->zones->rect_hitbox_attack,
        (sfVector2f){warrior->zones->hitbox_attack.left,
        warrior->zones->hitbox_attack.top});
    if (sfRectangleShape_getSize(warrior->zones->rect_hitbox_attack).x !=
        warrior->zones->hitbox_attack.width)
        sfRectangleShape_setSize(warrior->zones->rect_hitbox_attack,
        (sfVector2f){warrior->zones->hitbox_attack.width,
        warrior->zones->hitbox_attack.height});
}

static sfVector2f get_detection_pos(warrior_t *warrior)
{
    if (warrior->x == RIGHT) {
        return (sfVector2f){warrior->pos.x + WARRIOR_WIDTH / 3 + WARRIOR_WIDTH
        / 6, warrior->pos.y + WARRIOR_WIDTH / 3 + WARRIOR_WIDTH / 6};
    } else {
        return (sfVector2f){warrior->pos.x - WARRIOR_WIDTH / 3 - WARRIOR_WIDTH
        / 6, warrior->pos.y + WARRIOR_WIDTH / 3 + WARRIOR_WIDTH / 6};
    }
}

static void update_zones_pos(warrior_t *warrior)
{
    update_hitboxs_pos(warrior);
    warrior->exclam->circle_pos = get_detection_pos(warrior);
    warrior->inter->circle_pos = get_detection_pos(warrior);
    warrior->zones->circle_reset_pos = get_detection_pos(warrior);
}

static void update_sprite_scale(warrior_t *warrior)
{
    sfVector2f scale = sfSprite_getScale(warrior->sprite);

    if (warrior->x == RIGHT && scale.x != 1)
        sfSprite_setScale(warrior->sprite, (sfVector2f){1, 1});
    if (warrior->x == LEFT && scale.x != -1)
        sfSprite_setScale(warrior->sprite, (sfVector2f){-1, 1});
}

void update_all_warriors(rpg_t *rpg, warrior_t *tmp)
{
    anim_warrior(rpg, tmp);
    update_warrior_pos(tmp);
    update_zones_pos(tmp);
    update_sprite_scale(tmp);
}
