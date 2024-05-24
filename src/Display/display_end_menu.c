/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** display_end_menu
*/

#include "rpg.h"

void display_end_menu(rpg_t *rpg)
{
    button_t *tmp = rpg->end_menu->buttons;

    sfRenderWindow_drawText(rpg->win->window,
        rpg->end_menu->title1->text, NULL);
    sfRenderWindow_drawText(rpg->win->window,
        rpg->end_menu->title2->text, NULL);
    while (tmp != NULL) {
        sfRenderWindow_drawText(rpg->win->window, tmp->shadow, NULL);
        sfRenderWindow_drawText(rpg->win->window, tmp->text, NULL);
        tmp = tmp->next;
    }
}
