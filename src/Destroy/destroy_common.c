/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** destroy_common
*/

#include "rpg.h"

static void destroy_zones(zones_entity_t *zones)
{
    sfRectangleShape_destroy(zones->rect_hitbox);
    sfRectangleShape_destroy(zones->rect_hitbox_attack);
    sfRectangleShape_destroy(zones->rect_hitbox_foot);
    sfCircleShape_destroy(zones->l_circle);
    sfCircleShape_destroy(zones->m_circle);
    sfCircleShape_destroy(zones->s_circle);
    free(zones);
}

static void destroy_damage_texts(damage_text_t *damage_texts)
{
    damage_text_t *tmp = NULL;

    while (damage_texts) {
        tmp = damage_texts;
        damage_texts = damage_texts->next;
        sfText_destroy(tmp->text);
        free(tmp);
    }
}

static void destroy_eff(eff_t *eff)
{
    destroy_mark(eff->eff_mark);
    destroy_my_clock(eff->eff_clock);
    destroy_my_clock(eff->eff_damage_clock);
    free(eff);
}

static void destroy_stun(stun_t *stun)
{
    destroy_mark(stun->stun_mark);
    destroy_my_clock(stun->stun_clock);
    free(stun);
}

static void destroy_round_rectangle(round_rectangle_t *round_rectangle)
{
    sfRectangleShape_destroy(round_rectangle->rect_w);
    sfRectangleShape_destroy(round_rectangle->rect_h);
    sfCircleShape_destroy(round_rectangle->circle);
    free(round_rectangle);
}

static void destroy_health_bar(health_bar_t *health_bar)
{
    destroy_round_rectangle(health_bar->back);
    destroy_round_rectangle(health_bar->front);
    free(health_bar);
}

void destroy_arrows(arrows_t *arrows)
{
    arrows_t *tmp = NULL;

    while (arrows) {
        tmp = arrows;
        arrows = arrows->next;
        destroy_anim(tmp->anim);
        destroy_my_clock(tmp->myclock);
        free(tmp);
    }
}

void destroy_anim_sprite(anim_sprite_t *anim_sprite)
{
    if (anim_sprite == NULL)
        return;
    sfSprite_destroy(anim_sprite->sprite);
    sfTexture_destroy(anim_sprite->texture);
    free(anim_sprite);
}

void destroy_common(common_entity_t *common)
{
    free(common->name);
    sfText_destroy(common->name_text);
    destroy_anim(common->anim);
    destroy_zones(common->zones);
    free(common->attributes);
    destroy_anim(common->death->anim);
    free(common->death);
    destroy_my_clock(common->clock_cooldown_attack);
    destroy_damage_texts(common->damage_texts);
    destroy_stun(common->stun);
    destroy_eff(common->fire);
    destroy_eff(common->poison);
    destroy_health_bar(common->health_bar);
    destroy_arrows(common->arrows_hit);
    destroy_anim_sprite(common->grade_icon);
    free(common);
}
