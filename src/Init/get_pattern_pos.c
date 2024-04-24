/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** get_pattern_pos
*/

#include "rpg.h"

sfVector2f *get_pattern_pos(warrior_t *warrior, base_t *base)
{
    sfVector2f *pos;

    warrior = warrior;
    pos = malloc(sizeof(sfVector2f) * 5);
    pos[0] = (sfVector2f){base->rect.left + 100, base->rect.top + 100};
    pos[1] = (sfVector2f){base->rect.left + base->rect.width - 100,
        base->rect.top + 100};
    pos[2] = (sfVector2f){base->rect.left + 100, base->rect.top +
        base->rect.height - 100};
    pos[3] = (sfVector2f){base->rect.left + base->rect.width - 100,
        base->rect.top + base->rect.height - 100};
    pos[4] = (sfVector2f){-1, -1};
    return pos;
}
