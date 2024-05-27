/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** skill_funt
*/

#include "rpg.h"

int skill_fire_sword(rpg_t *rpg)
{
    rpg->comp->fire = true;
    return 1;
}

int skill_poison_sword(rpg_t *rpg)
{
    rpg->comp->poison = true;
    return 1;
}
