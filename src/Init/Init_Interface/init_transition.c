/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_transition
*/

#include "rpg.h"

void launch_transition(rpg_t *rpg, void (*callback)(rpg_t *rpg))
{
    sfIntRect rect = rpg->transition->anim->rect;

    rpg->transition->displayed = true;
    rpg->transition->anim->rect = (sfIntRect){TRANSI_WIDTH, TRANSI_HEIGHT * 8,
        rect.width, rect.height};
    sfClock_restart(rpg->transition->anim->myclock->clock);
    rpg->transition->callback = callback;
}

transition_t *init_transition(void)
{
    sfIntRect rect;
    transition_t *transi = malloc(sizeof(transition_t));

    transi->anim = init_anim("assets/interface/transition.png",
        TRANSI_WIDTH, TRANSI_HEIGHT);
    sfSprite_setPosition(transi->anim->sprite, (sfVector2f){WIDTH / 2,
        HEIGHT / 2});
    sfSprite_setScale(transi->anim->sprite, (sfVector2f){2, 2});
    rect = transi->anim->rect;
    transi->anim->rect = (sfIntRect){TRANSI_WIDTH, TRANSI_HEIGHT * 8,
        rect.width, rect.height};
    sfSprite_setTextureRect(transi->anim->sprite, transi->anim->rect);
    transi->displayed = false;
    transi->callback = NULL;
    return transi;
}
