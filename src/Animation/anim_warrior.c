/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** anim_warrior
*/

#include "rpg.h"

static void anim_mark(mark_t *mark, int width, int height, int max_width)
{
    if (mark->rect.top >= height * 2) {
        mark->rect.top = 0;
        mark->rect.left += width;
    } else if (mark->rect.left >= width * max_width) {
        mark->is_display = 2;
    } else
        mark->rect.top += height;
    sfSprite_setTextureRect(mark->sprite, mark->rect);
    sfClock_restart(mark->myclock->clock);
}

static void anim_exclam(warrior_t *warrior)
{
    update_clock_seconds(warrior->exclam->myclock);
    if (warrior->exclam->myclock->seconds > 0.02) {
        anim_mark(warrior->exclam, EXCLAM_WIDTH, EXCLAM_HEIGHT, 11);
    }
}

static void anim_inter(warrior_t *warrior)
{
    update_clock_seconds(warrior->inter->myclock);
    if (warrior->inter->myclock->seconds > 0.02) {
        anim_mark(warrior->inter, INTER_WIDTH, INTER_HEIGHT, 14);
    }
}

void anim_warrior(rpg_t *rpg, warrior_t *warrior)
{
    if (warrior->state == RIEN)
        return;
    update_clock_seconds(warrior->myclock);
    if (warrior->state == DEAD) {
        animation_dead(warrior);
    } else
        animation_alive(rpg, warrior);
    if (warrior->exclam->is_display == 1)
        anim_exclam(warrior);
    if (warrior->inter->is_display == 1)
        anim_inter(warrior);
}
