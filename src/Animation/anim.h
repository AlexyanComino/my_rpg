/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** anim
*/
#pragma once

#include "rpg.h"

// Anim death
void animation_death(common_entity_t *common);

// Anim damage text effects
void update_damage_text_effects(damage_text_t **damage_texts);

// Anim line
void anim_line(anim_t *anim, int offset, int width, float time);

// Anim mark
void anim_mark(mark_t *mark, sfIntRect *info);
void anim_fire_mark(mark_t *fire_mark, int width, int max_offset);
void anim_poison_mark(mark_t *poison_mark);

// Anim common effects
void anim_common_effects(entity_t *entity);

// Animations
void update_decors_anim(rpg_t *rpg, bool(*in_view)(rpg_t *, sfIntRect));
void anim_transition(rpg_t *rpg);
void anim_text_anim(anim_text_t *anim_text);
void anim_sprite_anim(anim_sprite_t *anim_sprite);
