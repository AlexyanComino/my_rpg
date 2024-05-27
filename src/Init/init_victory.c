/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_victory
*/

#include "rpg.h"

static void init_victory2(vict_t *vict)
{
    sfFloatRect rect = sfText_getLocalBounds(vict->text);

    sfText_setOrigin(vict->text, (sfVector2f){rect.width / 2,
        rect.height / 2});
    sfText_setPosition(vict->text, vict->text_pos);
    sfText_setColor(vict->text, sfWhite);
    sfText_setOutlineColor(vict->text, sfBlack);
    sfText_setOutlineThickness(vict->text, vict->thickness);
    vict->myclock = init_my_clock();
}

vict_t *init_victory(void)
{
    vict_t *vict = malloc(sizeof(vict_t));

    vict->is_win = false;
    vict->state = WAIT_EXTEND;
    vict->text = sfText_create();
    vict->font =
        sfFont_createFromFile("assets/fonts/BreatheFireIii-PKLOB.ttf");
    vict->size = 3000;
    vict->thickness = 300;
    vict->text_pos = (sfVector2f){0, 0};
    sfText_setFont(vict->text, vict->font);
    sfText_setCharacterSize(vict->text, vict->size);
    sfText_setString(vict->text, "The End");
    init_victory2(vict);
    return vict;
}
