/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** destroy_damage_text
*/

#include "rpg.h"

void destroy_damage_text(damage_text_t *damage_text)
{
    sfText_destroy(damage_text->text);
    sfFont_destroy(damage_text->font);
    if (damage_text->effect != NULL) {
        sfSprite_destroy(damage_text->effect->sprite);
        sfTexture_destroy(damage_text->effect->texture);
        sfClock_destroy(damage_text->effect->myclock->clock);
        free(damage_text->effect->myclock);
        free(damage_text->effect);
    }
    free(damage_text);
}
