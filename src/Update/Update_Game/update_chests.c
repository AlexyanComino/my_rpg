/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_chests
*/

#include "rpg.h"

static void check_state_chest(chest_t *chest)
{
    if (chest->state == CLOSED && chest->is_interacted)
        chest->state = OPENING;
    if (chest->state == OPENED && !chest->is_interacted)
        chest->state = CLOSING;
}

static void anim_chest(chest_t *chest)
{
    update_clock_seconds(chest->anim->myclock);
    if (chest->anim->myclock->seconds < 0.1)
        return;
    if (chest->state == OPENING) {
        if (chest->anim->rect.left < 7 * CHEST_WIDTH)
            chest->anim->rect.left += CHEST_WIDTH;
        else
            chest->state = OPENED;
    }
    if (chest->state == CLOSING) {
        if (chest->anim->rect.left < 14 * CHEST_WIDTH)
            chest->anim->rect.left += CHEST_WIDTH;
        else {
            chest->anim->rect.left = 0;
            chest->state = CLOSED;
        }
    }
    sfSprite_setTextureRect(chest->anim->sprite, chest->anim->rect);
    sfClock_restart(chest->anim->myclock->clock);
}

void update_chests(rpg_t *rpg)
{
    for (unsigned int i = 0; i < rpg->chests_size; i++) {
        if (!intrect_is_in_view(rpg, rpg->chests[i]->rect))
            continue;
        check_state_chest(rpg->chests[i]);
        anim_chest(rpg->chests[i]);
    }
}
