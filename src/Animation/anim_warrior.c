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
        sfClock_restart(mark->myclock->clock);
    } else
        mark->rect.top += height;
    sfSprite_setTextureRect(mark->sprite, mark->rect);
    sfClock_restart(mark->myclock->clock);
}

static void anim_exclam(warrior_t *warrior)
{
    warrior->exclam->myclock->time =
        sfClock_getElapsedTime(warrior->exclam->myclock->clock);
    warrior->exclam->myclock->seconds =
        warrior->exclam->myclock->time.microseconds / 1000000.0;
    if (warrior->exclam->myclock->seconds > 0.02) {
        anim_mark(warrior->exclam, EXCLAM_WIDTH, EXCLAM_HEIGHT, 11);
    }
}

static void anim_inter(warrior_t *warrior)
{
    warrior->inter->myclock->time =
        sfClock_getElapsedTime(warrior->inter->myclock->clock);
    warrior->inter->myclock->seconds =
        warrior->inter->myclock->time.microseconds / 1000000.0;
    if (warrior->inter->myclock->seconds > 0.02) {
        anim_mark(warrior->inter, INTER_WIDTH, INTER_HEIGHT, 14);
    }
}

static void check_player_is_far(rpg_t *rpg, warrior_t *warrior, mark_t *mark)
{
    sfIntRect hitbox_player = rpg->lwarrior->warrior->zones->hitbox;

    if (!hitbox_in_detection(hitbox_player, warrior->zones->radius_reset,
        warrior->zones->circle_reset_pos)) {
        mark->is_display = 0;
        mark->is_detecting = false;
    }
}

void anim_warrior(rpg_t *rpg, warrior_t *warrior)
{
    if (warrior->state == RIEN)
        return;
    warrior->myclock->time = sfClock_getElapsedTime(warrior->myclock->clock);
    warrior->myclock->seconds =
        warrior->myclock->time.microseconds / 1000000.0;
    if (warrior->state == DEAD) {
        animation_dead(warrior);
    } else
        animation_alive(rpg, warrior);
    if (warrior->exclam->is_display == 1)
        anim_exclam(warrior);
    else if (warrior->exclam->is_display == 2)
        check_player_is_far(rpg, warrior, warrior->exclam);
    if (warrior->inter->is_display == 1)
        anim_inter(warrior);
    else if (warrior->inter->is_display == 2)
        check_player_is_far(rpg, warrior, warrior->inter);
}
