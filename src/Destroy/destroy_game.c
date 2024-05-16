/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** destroy_game
*/

#include "rpg.h"

void destroy_anim(anim_t *anim)
{
    sfTexture_destroy(anim->texture);
    sfSprite_destroy(anim->sprite);
    free(anim);
}
