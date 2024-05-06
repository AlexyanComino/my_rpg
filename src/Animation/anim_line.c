/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** anim_line
*/

#include "rpg.h"

void anim_line(common_entity_t *common, int offset, int width, float time)
{
    if (common->anim->myclock->seconds > time) {
        if (common->anim->rect.left >= offset) {
            common->anim->rect.left = 0;
        } else
            common->anim->rect.left += width;
        sfSprite_setTextureRect(common->anim->sprite, common->anim->rect);
        sfClock_restart(common->anim->myclock->clock);
    }
}
