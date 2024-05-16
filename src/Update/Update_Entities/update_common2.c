/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_common2
*/

#include "rpg.h"

static void update_sprite_dead(common_entity_t *common)
{
    sfVector2f scale = sfSprite_getScale(common->death->anim->sprite);
    sfVector2f pos = sfSprite_getPosition(common->death->anim->sprite);

    if (common->x == RIGHT && scale.x != 1)
        sfSprite_setScale(common->death->anim->sprite, (sfVector2f){1, 1});
    if (common->x == LEFT && scale.x != -1)
        sfSprite_setScale(common->death->anim->sprite, (sfVector2f){-1, 1});
    if (common->pos.x != pos.x || common->pos.y !=
        pos.y)
        sfSprite_setPosition(common->death->anim->sprite,
            common->pos);
}

static void update_sprites_pos(entity_t *entity)
{
    if (is_alive(entity)) {
        sfSprite_setPosition(entity->common->anim->sprite,
            entity->common->pos);
        sfCircleShape_setPosition(entity->common->zones->l_circle,
            entity->common->pos);
        sfCircleShape_setPosition(entity->common->zones->m_circle,
            entity->common->pos);
        sfCircleShape_setPosition(entity->common->zones->s_circle,
            entity->common->pos);
    } else if (is_dead(entity)) {
        update_sprite_dead(entity->common);
    }
}

static void update_sprite_scale(common_entity_t *common)
{
    sfVector2f scale = sfSprite_getScale(common->anim->sprite);

    if (common->x == RIGHT && scale.x != 1)
        sfSprite_setScale(common->anim->sprite, (sfVector2f){1, 1});
    if (common->x == LEFT && scale.x != -1)
        sfSprite_setScale(common->anim->sprite, (sfVector2f){-1, 1});
}

static void update_sprite_foot_hitbox(entity_t *entity)
{
    entity->common->zones->hitbox_foot = entity->get_hitbox_foot(
        entity->common->pos);
    sfRectangleShape_setPosition(entity->common->zones->rect_hitbox_foot,
        (sfVector2f){entity->common->zones->hitbox_foot.left,
        entity->common->zones->hitbox_foot.top});
    sfRectangleShape_setSize(entity->common->zones->rect_hitbox_foot,
        (sfVector2f){entity->common->zones->hitbox_foot.width,
        entity->common->zones->hitbox_foot.height});
}

static void update_sprites_hitboxs_pos(entity_t *tmp)
{
    tmp->common->zones->hitbox = tmp->get_hitbox(tmp->common->pos);
    sfRectangleShape_setPosition(tmp->common->zones->rect_hitbox,
        (sfVector2f){tmp->common->zones->hitbox.left,
        tmp->common->zones->hitbox.top});
    if (sfRectangleShape_getSize(tmp->common->zones->rect_hitbox).x !=
        tmp->common->zones->hitbox.width)
        sfRectangleShape_setSize(tmp->common->zones->rect_hitbox,
        (sfVector2f){tmp->common->zones->hitbox.width,
        tmp->common->zones->hitbox.height});
    tmp->common->zones->hitbox_attack = tmp->get_hitbox_attack(
        tmp->common->pos, tmp->common->x, tmp->common->y);
    sfRectangleShape_setPosition(tmp->common->zones->rect_hitbox_attack,
        (sfVector2f){tmp->common->zones->hitbox_attack.left,
        tmp->common->zones->hitbox_attack.top});
    if (sfRectangleShape_getSize(tmp->common->zones->rect_hitbox_attack).x !=
        tmp->common->zones->hitbox_attack.width)
        sfRectangleShape_setSize(tmp->common->zones->rect_hitbox_attack,
        (sfVector2f){tmp->common->zones->hitbox_attack.width,
        tmp->common->zones->hitbox_attack.height});
    update_sprite_foot_hitbox(tmp);
}

void update_entity_sprite(entity_t *entity)
{
    update_sprites_pos(entity);
    update_sprite_scale(entity->common);
    update_sprites_hitboxs_pos(entity);
}
