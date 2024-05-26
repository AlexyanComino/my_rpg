/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** destroy
*/
#pragma once

#include "rpg.h"

// DestroyRpg
void destroy(rpg_t *rpg);

// Destroy damage text
void destroy_damage_text(damage_text_t *damage_text);

// Destroy game
void destroy_anim(anim_t *anim);

// Destroy common
void destroy_arrows(arrows_t *arrows);
void destroy_common(common_entity_t *common);

// Destroy entity
void destroy_entity_warrior(entity_t *entity);
void destroy_entity_pawn(entity_t *entity);

// Destroy entity 2
void destroy_entity_torch(entity_t *entity);
void destroy_entity_tnt(entity_t *entity);
void destroy_entity_archer(entity_t *entity);

// Destroy ent
void destroy_base(base_t *base);
void destroy_mark(mark_t *mark);
void destroy_my_clock(my_clock_t *clock);
void destroy_ent(entity_t **ent, unsigned int size);
