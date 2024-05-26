/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_pause_menu
*/

#include "rpg.h"


void update_pause_menu(rpg_t *rpg)
{
    anim_text_anim(rpg->pause_menu->title);
    update_shadow_buttons(rpg->pause_menu->buttons);
}
