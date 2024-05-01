/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_entities
*/
#pragma once

// Init ent
my_clock_t *init_my_clock(void);
anim_t *init_anim(char *texture_path, int width, int height);
entity_t **init_ent(unsigned int *size);

// Init damage texts
damage_text_t *init_damage_text(rpg_t *rpg, entity_t *entity,
    int attack, damage_text_state_t state);
