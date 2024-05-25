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
entity_t *init_entity(char **infos);
entity_t **init_ent(unsigned int *size);

// Init damage texts
damage_text_t *init_damage_text(rpg_t *rpg, entity_t *entity,
    int attack, damage_text_state_t state);

// Init round rectangle
round_rectangle_t *init_round_rectangle(sfVector2f pos, float r,
    sfVector2f size, sfColor color);

// Init base
base_t *init_base(char **infos);

// Init damage texts
damage_text_t *init_damage_text(rpg_t *rpg, entity_t *entity,
    int attack, damage_text_state_t state);
