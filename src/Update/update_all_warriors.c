/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_all_warriors
*/

#include "rpg.h"

//
static void update_sprite_dead(warrior_t *warrior)
{
    sfVector2f scale = sfSprite_getScale(warrior->death->sprite_dead);
    sfVector2f pos = sfSprite_getPosition(warrior->death->sprite_dead);

    if (warrior->x == RIGHT && scale.x != 1)
        sfSprite_setScale(warrior->death->sprite_dead, (sfVector2f){1, 1});
    if (warrior->x == LEFT && scale.x != -1)
        sfSprite_setScale(warrior->death->sprite_dead, (sfVector2f){-1, 1});
    if (warrior->pos.x != pos.x || warrior->pos.y !=
        pos.y)
        sfSprite_setPosition(warrior->death->sprite_dead,
            warrior->pos);
}

//
static void update_sprites_warrior_pos(warrior_t *warrior)
{
    if (is_alive(warrior)) {
        sfSprite_setPosition(warrior->sprite, warrior->pos);
        sfCircleShape_setPosition(warrior->exclam->circle,
            warrior->pos);
        sfCircleShape_setPosition(warrior->inter->circle,
            warrior->pos);
        sfCircleShape_setPosition(warrior->zones->circle_max_detection,
            warrior->pos);
    } else if (is_dead(warrior)) {
        update_sprite_dead(warrior);
    }
}

//
static void update_sprites_hitboxs_pos(warrior_t *warrior)
{
    warrior->zones->hitbox = get_hitbox_warrior(warrior->pos);
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

//
static void update_sprite_scale(warrior_t *warrior)
{
    sfVector2f scale = sfSprite_getScale(warrior->sprite);

    if (warrior->x == RIGHT && scale.x != 1)
        sfSprite_setScale(warrior->sprite, (sfVector2f){1, 1});
    if (warrior->x == LEFT && scale.x != -1)
        sfSprite_setScale(warrior->sprite, (sfVector2f){-1, 1});
}

//
static void remove_damage_text(warrior_t *warrior, damage_text_t *tmp)
{
    damage_text_t *prev = warrior->damage_texts;

    if (prev == tmp) {
        warrior->damage_texts = tmp->next;
        destroy_damage_text(tmp);
        return;
    }
    while (prev->next != tmp)
        prev = prev->next;
    prev->next = tmp->next;
    destroy_damage_text(tmp);
}

static void change_pos_and_alpha(damage_text_t *tmp, sfColor color,
    sfColor color_shadow)
{
    if (tmp->state != CRITICAL && tmp->state != BAM) {
        tmp->pos.y -= 1.5;
        sfText_setPosition(tmp->text, tmp->pos);
        sfText_setPosition(tmp->text_shadow, (sfVector2f){tmp->pos.x + 2,
            tmp->pos.y + 2});
    }
    color.a -= 5;
    color_shadow.a -= 5;
    sfText_setColor(tmp->text, color);
    sfText_setColor(tmp->text_shadow, color_shadow);
}

static void update_damage_texts(warrior_t *warrior)
{
    damage_text_t *tmp = warrior->damage_texts;
    damage_text_t *next = NULL;
    sfColor color;
    sfColor color_shadow;

    if (tmp == NULL)
        return;
    while (tmp != NULL) {
        next = tmp->next;
        color = sfText_getColor(tmp->text);
        color_shadow = sfText_getColor(tmp->text_shadow);
        if (color.a <= 0) {
            remove_damage_text(warrior, tmp);
            tmp = next;
            continue;
        }
        change_pos_and_alpha(tmp, color, color_shadow);
        tmp = next;
    }
}

//
void update_all_warriors(rpg_t *rpg, warrior_t *tmp)
{
    anim_warrior(rpg, tmp);
    update_sprites_warrior_pos(tmp);
    update_sprites_hitboxs_pos(tmp);
    update_sprite_scale(tmp);
    update_damage_texts(tmp);
    update_damage_text_effects(tmp);
}
