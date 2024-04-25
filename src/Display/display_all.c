/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** displayAll
*/

#include "rpg.h"
#include "singleton.h"

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

    if (!is_alive(rpg->lwarrior->warrior))
        return;
    sfRenderWindow_drawSprite(rpg->win->window, restricted->sprite, NULL);
}

static void display_collision(rpg_t *rpg)
{
    collision_t *collision = rpg->collision;

    for (unsigned int i = 0; i < collision->size; i++) {
        sfRectangleShape_setPosition(collision->shape, collision->pos[i]);
        sfRenderWindow_drawRectangleShape(rpg->win->window, collision->shape,
            NULL);
    }
}

void display_all(rpg_t *rpg)
{
    sfRenderWindow_clear(rpg->win->window, sfBlack);
    if (rpg->gamestate == MAIN_MENU)
        display_main_menu(rpg);
    if (rpg->gamestate == SETTINGS)
        display_settings(rpg);
    if (rpg->gamestate == GAME || rpg->gamestate == INVENTORY) {
        sfRenderWindow_drawSprite(rpg->win->window, rpg->map->ground_sprite,
            NULL);
        display_warriors(rpg);
        sfRenderWindow_drawSprite(rpg->win->window, rpg->map->high_sprite,
            NULL);
        if (rpg->debug)
            display_collision(rpg);
        update_inv(rpg);
        display_restricted_text(rpg);
    }
    sfRenderWindow_display(rpg->win->window);
}
