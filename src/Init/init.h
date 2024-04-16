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
warrior_t *init_warrior(color_warrior_t color, sfVector2f pos);
