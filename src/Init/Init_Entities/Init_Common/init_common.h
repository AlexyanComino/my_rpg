/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_common
*/
#pragma once

// Init common
common_entity_t *init_common(char **infos, entity_type_t type);

// Init common 2
void init_common2(common_entity_t *common, entity_type_t type);

// Init entity zones
zones_entity_t *init_entity_zones(char **infos, sfVector2f pos,
    entity_type_t type, float scale);

// Get anim
anim_t *get_anim(entity_type_t type, color_entity_t color);

// Get anim 2
anim_t *get_anim_archer(color_entity_t color);

// Init common3
health_bar_t *init_health_bar(entity_type_t type, float scale);
health_bar_t *init_health_bar_boss(void);
