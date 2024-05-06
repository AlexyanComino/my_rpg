/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_common
*/

#include "rpg.h"

static void check_against_all(rpg_t *rpg, entity_t *entity)
{
    entity_t *other;

    if (entity->common->faction == AGAINST_ALL) {
        other = get_nearest_entity(rpg, entity, true);
        if (!other || !hitbox_in_detection(entity->common->zones->hitbox,
            other->common->zones->l_radius, other->common->pos))
            entity->common->faction = entity->common->faction_origin;
    }
}

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
}

static void update_stun(entity_t *entity)
{
    if (entity->common->stun->is_stunned) {
        update_clock_seconds(entity->common->stun->stun_clock);
        if (entity->common->stun->stun_clock->seconds >=
            entity->common->stun->stun_time) {
            entity->common->stun->is_stunned = false;
            entity->common->stun->stun_mark->anim->rect.left = 0;
            entity->common->stun->stun_mark->anim->rect.top = 0;
        }
    }
}

void anim_stun(entity_t *entity)
{
    sfIntRect info;

    if (entity->common->stun->is_stunned) {
        update_clock_seconds(entity->common->stun->stun_mark->anim->myclock);
        if (entity->common->stun->stun_mark->anim->myclock->seconds > 0.05) {
            info = (sfIntRect){STUN_WIDTH, STUN_HEIGHT, 2, 41};
            anim_mark(entity->common->stun->stun_mark, &info);
        }
        entity->common->stun->stun_mark->is_display = 1;
        entity->common->stun->stun_mark->pos = (sfVector2f){
            entity->common->pos.x, entity->common->pos.y - 50};
        sfSprite_setPosition(entity->common->stun->stun_mark->anim->sprite,
            entity->common->stun->stun_mark->pos);
    } else {
        entity->common->stun->stun_mark->is_display = 0;
    }
}

void update_common(rpg_t *rpg, entity_t *entity)
{
    anim_stun(entity);
    update_sprites_pos(entity);
    update_sprite_scale(entity->common);
    update_sprites_hitboxs_pos(entity);
    check_against_all(rpg, entity);
    update_damage_texts(&entity->common->damage_texts);
    update_damage_text_effects(&entity->common->damage_texts);
    update_entity_detection(rpg, entity);
    update_stun(entity);
}
