/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init
*/
#pragma once

#include "rpg.h"

// InitRpg
rpg_t *init_rpg(void);

// Init_Lwarrior
lwarrior_t *init_lwarrior(void);

// Init warrior
my_clock_t *init_my_clock(void);
warrior_t *init_warrior(color_warrior_t color, sfVector2f pos);

// Init warrior marks
mark_t *init_exclam(warrior_t *warrior);
mark_t *init_inter(warrior_t *warrior);
