/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** anim_stun
*/

#include "rpg.h"

void anim_mark(mark_t *mark, sfIntRect *info)
{
    int width = info->left;
    int height = info->top;
    int max_width = info->width;
    int max_height = info->height;

    if (mark->anim->rect.top >= height * max_height) {
        mark->anim->rect.top = 0;
        mark->anim->rect.left += width;
    } else if (mark->anim->rect.left >= width * max_width) {
        mark->is_display = 2;
    } else
        mark->anim->rect.top += height;
    sfSprite_setTextureRect(mark->anim->sprite, mark->anim->rect);
    sfClock_restart(mark->anim->myclock->clock);
}
