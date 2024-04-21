/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** displayAll
*/

#include "rpg.h"

void display_main_menu(rpg_t *rpg)
{
    button_t *tmp = rpg->main_menu->buttons;

    sfRenderWindow_drawSprite(
        rpg->win->window, rpg->main_menu->background, NULL);
    while (tmp != NULL) {
        sfSprite_setTextureRect(tmp->sprite, tmp->rect);
        sfRenderWindow_drawSprite(rpg->win->window, tmp->sprite, NULL);
        sfRenderWindow_drawText(rpg->win->window, tmp->text, NULL);
        tmp = tmp->next;
    }
}

void display_settings(rpg_t *rpg)
{
    button_t *tmp = rpg->settings->buttons;

    sfRenderWindow_drawSprite(
        rpg->win->window, rpg->settings->background, NULL);
    while (tmp != NULL) {
        sfSprite_setTextureRect(tmp->sprite, tmp->rect);
        sfRenderWindow_drawSprite(rpg->win->window, tmp->sprite, NULL);
        sfRenderWindow_drawText(rpg->win->window, tmp->text, NULL);
        tmp = tmp->next;
    }
}

static void display_restricted_text(rpg_t *rpg)
{
    restricted_t *restricted = rpg->interface->restricted;

    sfRenderWindow_drawSprite(rpg->win->window, restricted->sprite, NULL);
}

void display_all(rpg_t *rpg)
{
    sfRenderWindow_clear(rpg->win->window, sfBlack);
    if (rpg->gamestate == MAIN_MENU)
        display_main_menu(rpg);
    if (rpg->gamestate == SETTINGS)
        display_settings(rpg);
    if (rpg->gamestate == GAME) {
        display_warriors(rpg);
        display_restricted_text(rpg);
    }
    sfRenderWindow_display(rpg->win->window);
}
