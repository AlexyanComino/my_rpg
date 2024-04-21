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
    sfText_destroy(damage_text->text_shadow);
    free(damage_text);
}
