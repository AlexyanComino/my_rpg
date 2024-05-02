/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_common
*/
#pragma once

// Init common
common_entity_t *init_common(char **infos, entity_type_t type);

// Init entity zones
zones_entity_t *init_entity_zones(char **infos, sfVector2f pos,
    entity_type_t type);

// Get anim
anim_t *get_anim(entity_type_t type, color_entity_t color);
