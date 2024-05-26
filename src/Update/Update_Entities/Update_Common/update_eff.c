/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_eff
*/

#include "rpg.h"

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

static void update_eff_damage(rpg_t *rpg, entity_t *entity, eff_t *eff,
    damage_text_state_t text)
{
    update_clock_seconds(eff->eff_damage_clock);
    if (eff->eff_damage_clock->seconds >= eff->eff_cooldown) {
        entity->common->attributes->health -=
            entity->common->fire->eff_damage;
        add_dmg_text(rpg, entity, eff->eff_damage, text);
        if (entity->common->attributes->health <= 0)
            entity_is_dead(rpg, entity);
        sfClock_restart(eff->eff_damage_clock->clock);
    }
}

static void check_is_fire(rpg_t *rpg, damage_text_state_t text)
{
    if (text == FIRE_TEXT)
        sfMusic_play(rpg->sounds->burn);
}

static void update_eff(rpg_t *rpg, entity_t *entity, eff_t *eff,
    damage_text_state_t text)
{
    if (eff->is_on_eff) {
        update_clock_seconds(eff->eff_clock);
        if (eff->eff_clock->seconds >= eff->eff_duration) {
            eff->is_on_eff = false;
            check_is_fire(rpg, text);
            eff->eff_mark->anim->rect.left = 0;
            eff->eff_mark->anim->rect.top = 0;
            sfSprite_setTextureRect(eff->eff_mark->anim->
                sprite, eff->eff_mark->anim->rect);
        }
        update_eff_damage(rpg, entity, eff, text);
    }
}

void update_effs(rpg_t *rpg, entity_t *entity)
{
    if (!is_alive(entity))
        return;
    update_stun(entity);
    update_eff(rpg, entity, entity->common->fire, FIRE_TEXT);
    update_eff(rpg, entity, entity->common->poison, POISON_TEXT);
}
