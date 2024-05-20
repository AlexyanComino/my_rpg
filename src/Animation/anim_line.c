/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** anim_line
*/

#include "rpg.h"

void anim_line(anim_t *anim, int offset, int width, float time)
{
    if (anim->myclock->seconds > time) {
        if (anim->rect.left >= offset) {
            anim->rect.left = 0;
        } else
            anim->rect.left += width;
        sfSprite_setTextureRect(anim->sprite, anim->rect);
        sfClock_restart(anim->myclock->clock);
    }
}
