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
void anim_line(common_entity_t *common, int offset, int width, float time);

// Anim mark
void anim_mark(mark_t *mark, sfIntRect *info);
