/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** anim_mark
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
        mark->anim->rect.left = 0;
        mark->anim->rect.top = 0;
    } else
        mark->anim->rect.top += height;
    sfSprite_setTextureRect(mark->anim->sprite, mark->anim->rect);
    sfClock_restart(mark->anim->myclock->clock);
}

void anim_fire_mark(mark_t *fire_mark, int width, int max_offset)
{
    if (fire_mark->anim->rect.left >= width * max_offset) {
        fire_mark->anim->rect.left = 0;
    } else
        fire_mark->anim->rect.left += width;
    sfSprite_setTextureRect(fire_mark->anim->sprite, fire_mark->anim->rect);
    sfClock_restart(fire_mark->anim->myclock->clock);
}

void anim_poison_mark(mark_t *poison_mark)
{
    if (poison_mark->anim->rect.left >= POISON_WIDTH * 3) {
        poison_mark->anim->rect.left = 0;
        poison_mark->anim->rect.top += POISON_WIDTH;
    } else if (poison_mark->anim->rect.top >= POISON_WIDTH) {
        poison_mark->anim->rect.top = 0;
        poison_mark->anim->rect.left = 0;
        poison_mark->is_display = 2;
    } else
        poison_mark->anim->rect.left += POISON_WIDTH;
    sfSprite_setTextureRect(poison_mark->anim->sprite,
        poison_mark->anim->rect);
    sfClock_restart(poison_mark->anim->myclock->clock);
}
