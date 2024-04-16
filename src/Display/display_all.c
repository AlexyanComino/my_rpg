/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** displayAll
*/

#include "rpg.h"

void display_all(rpg_t *rpg)
{
    sfRenderWindow_clear(rpg->win->window, sfBlack);
    sfRenderWindow_drawSprite(rpg->win->window, rpg->main_menu->background, NULL);
    button_t *tmp = rpg->main_menu->buttons;
    while (tmp != NULL) {
        sfSprite_setTextureRect(tmp->sprite, tmp->rect);
        sfRenderWindow_drawSprite(rpg->win->window, tmp->sprite, NULL);
        sfRenderWindow_drawText(rpg->win->window, tmp->text, NULL);
        tmp = tmp->next;
    }
    sfRenderWindow_display(rpg->win->window);
}
