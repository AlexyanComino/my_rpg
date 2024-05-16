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

static void update_fire_damage(rpg_t *rpg, entity_t *entity)
{
    update_clock_seconds(entity->common->fire->fire_damage_clock);
    if (entity->common->fire->fire_damage_clock->seconds >= 1) {
        entity->common->attributes->health -=
            entity->common->fire->fire_damage;
        add_dmg_text(rpg, entity, entity->common->fire->fire_damage,
            FIRE_TEXT);
        sfClock_restart(entity->common->fire->fire_damage_clock->clock);
    }
}

static void update_fire(rpg_t *rpg, entity_t *entity)
{
    if (entity->common->fire->is_on_fire && is_alive(entity)) {
        update_clock_seconds(entity->common->fire->fire_clock);
        if (entity->common->fire->fire_clock->seconds >=
            entity->common->fire->burn_time) {
            entity->common->fire->is_on_fire = false;
            entity->common->fire->fire_mark->anim->rect.left = 0;
            entity->common->fire->fire_mark->anim->rect.top = 0;
            sfSprite_setTextureRect(entity->common->fire->fire_mark->anim->
                sprite, entity->common->fire->fire_mark->anim->rect);
        }
        update_fire_damage(rpg, entity);
    }
}

static void update_name_text_pos(entity_t *entity)
{
    sfVector2f pos = entity->common->pos;

    pos.y -= 50;
    sfText_setPosition(entity->common->name_text, pos);
}

static void update_list_arrows_hit(entity_t *entity)
{
    arrows_t *tmp = entity->common->arrows_hit;
    arrows_t *prev = NULL;

    if (!tmp)
        return;
    while (tmp) {
        update_clock_seconds(tmp->myclock);
        if (tmp->myclock->seconds >= ARROW_HIT_ENTITY_COOLDOWN) {
            remove_arrow(&entity->common->arrows_hit, tmp, prev);
            tmp = prev;
        }
        if (tmp) {
            tmp->pos = (sfVector2f){entity->common->pos.x + tmp->diff_center.x,
            entity->common->pos.y + tmp->diff_center.y};
            sfSprite_setPosition(tmp->anim->sprite, tmp->pos);
            prev = tmp;
            tmp = tmp->next;
        }
    }
}

void update_common(rpg_t *rpg, entity_t *entity)
{
    anim_common_effects(entity);
    check_against_all(rpg, entity);
    update_entity_sprite(entity);
    update_damage_texts(&entity->common->damage_texts);
    update_damage_text_effects(&entity->common->damage_texts);
    update_entity_detection(rpg, entity);
    update_stun(entity);
    update_fire(rpg, entity);
    update_list_arrows_hit(entity);
    if (rpg->plus) {
        update_health_bar(entity);
        update_name_text_pos(entity);
    }
}
