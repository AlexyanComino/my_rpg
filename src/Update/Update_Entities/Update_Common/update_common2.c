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

    if (common->x == RIGHT && scale.x != common->scale)
        sfSprite_setScale(common->death->anim->sprite,
            (sfVector2f){common->scale, common->scale});
    if (common->x == LEFT && scale.x != -common->scale)
        sfSprite_setScale(common->death->anim->sprite,
            (sfVector2f){-common->scale, common->scale});
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

    if (common->x == RIGHT && scale.x != common->scale)
        sfSprite_setScale(common->anim->sprite, (sfVector2f){common->scale,
            common->scale});
    if (common->x == LEFT && scale.x != -common->scale)
        sfSprite_setScale(common->anim->sprite, (sfVector2f){-common->scale,
            common->scale});
}

static void update_sprite_foot_hitbox(entity_t *entity)
{
    entity->common->zones->hitbox_foot = entity->get_hitbox_foot(
        entity->common->pos, entity->common->scale);
    sfRectangleShape_setPosition(entity->common->zones->rect_hitbox_foot,
        (sfVector2f){entity->common->zones->hitbox_foot.left,
        entity->common->zones->hitbox_foot.top});
    sfRectangleShape_setSize(entity->common->zones->rect_hitbox_foot,
        (sfVector2f){entity->common->zones->hitbox_foot.width,
        entity->common->zones->hitbox_foot.height});
}

static void update_sprites_hitboxs_pos(entity_t *tmp)
{
    zones_entity_t *z = tmp->common->zones;

    z->hitbox = tmp->get_hitbox(tmp->common->pos, tmp->common->scale);
    sfRectangleShape_setPosition(z->rect_hitbox, (sfVector2f)
        {z->hitbox.left, z->hitbox.top});
    if (sfRectangleShape_getSize(z->rect_hitbox).x != z->hitbox.width)
        sfRectangleShape_setSize(z->rect_hitbox,
        (sfVector2f){z->hitbox.width, z->hitbox.height});
    z->hitbox_attack = tmp->get_hitbox_attack(
        tmp->common->pos, tmp->common->x, tmp->common->y, tmp->common->scale);
    sfRectangleShape_setPosition(z->rect_hitbox_attack,
        (sfVector2f){z->hitbox_attack.left, z->hitbox_attack.top});
    if (sfRectangleShape_getSize(z->rect_hitbox_attack).x !=
        z->hitbox_attack.width)
        sfRectangleShape_setSize(z->rect_hitbox_attack,
        (sfVector2f){z->hitbox_attack.width, z->hitbox_attack.height});
    update_sprite_foot_hitbox(tmp);
}

void update_entity_sprite(entity_t *entity)
{
    update_sprites_pos(entity);
    update_sprite_scale(entity->common);
    update_sprites_hitboxs_pos(entity);
}
