/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** skill tree
*/

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "rpg.h"

typedef struct skill_s {
    int id;
    char *name;
    char *description;
    int level;
    int max_level;
    int cost;
    int unlocked;
    sfSprite *sprite;
    sfSprite *highlight;
    sfSprite *background;
    int (*function)(rpg_t *rpg);
    struct skill_s *next;
} skill_t;

int manage_skill_tree(rpg_t *rpg);
skill_t *init_all_skill(void);
skill_t *init_skill(char *name, char *description, int cost, int (*function)(rpg_t *rpg));
skill_t *add_skill(skill_t *skill, skill_t *new_skill);
int unlock_skill(skill_t *skill, char *name);
int draw_ui_tree(rpg_t *rpg);
int draw_skill_tree(rpg_t *rpg);