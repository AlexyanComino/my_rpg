/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** display_menus
*/

#include "rpg.h"

void display_main_menu(rpg_t *rpg)
{
    button_t *tmp = rpg->main_menu->buttons;

    sfRenderWindow_drawSprite(
        rpg->win->window, rpg->main_menu->background, NULL);
    sfRenderWindow_drawText(rpg->win->window, rpg->main_menu->text, NULL);
    while (tmp != NULL) {
        sfRenderWindow_drawText(rpg->win->window, tmp->text, NULL);
        tmp = tmp->next;
    }
}

void display_settings(rpg_t *rpg)
{
    button_t *tmp = rpg->settings->buttons;

    sfRenderWindow_drawSprite(
        rpg->win->window, rpg->main_menu->background, NULL);
    while (tmp != NULL) {
        sfRenderWindow_drawText(rpg->win->window, tmp->text, NULL);
        tmp = tmp->next;
    }
}

void display_save_menu(rpg_t *rpg)
{
    save_button_t *tmp = rpg->save_menu->buttons;

    sfRenderWindow_drawSprite(
        rpg->win->window, rpg->main_menu->background, NULL);
    while (tmp != NULL) {
        if (strcmp(tmp->name, "BACK") != 0)
            sfRenderWindow_drawRectangleShape(rpg->win->window,
                tmp->rect_shape, NULL);
        sfRenderWindow_drawText(rpg->win->window, tmp->text, NULL);
        tmp = tmp->next;
    }
}

static void draw_stats(rpg_t *rpg, select_button_t *tmp)
{
    sfRenderWindow_drawSprite(rpg->win->window, tmp->sprite, NULL);
    sfRenderWindow_drawText(rpg->win->window, tmp->text, NULL);
    sfRenderWindow_drawText(rpg->win->window, tmp->hp, NULL);
    sfRenderWindow_drawText(rpg->win->window, tmp->attack, NULL);
    sfRenderWindow_drawText(rpg->win->window, tmp->defense, NULL);
    sfRenderWindow_drawText(rpg->win->window, tmp->speed, NULL);
    sfRenderWindow_drawSprite(rpg->win->window,
        rpg->inventory->player_status->s_hp, NULL);
    sfRenderWindow_drawSprite(rpg->win->window,
        rpg->inventory->player_status->s_attack, NULL);
    sfRenderWindow_drawSprite(rpg->win->window,
        rpg->inventory->player_status->s_def, NULL);
    sfRenderWindow_drawSprite(rpg->win->window,
        rpg->inventory->player_status->s_speed, NULL);
}

static void set_sprites_pos(rpg_t *rpg, select_button_t *tmp)
{
    sfVector2f pos = sfRectangleShape_getPosition(tmp->rect_shape);
    sfVector2f size = sfRectangleShape_getSize(tmp->rect_shape);

    sfSprite_setPosition(rpg->inventory->player_status->pp,
        (sfVector2f){pos.x, pos.y + 200});
    sfSprite_setPosition(rpg->inventory->player_status->s_hp,
        (sfVector2f){pos.x - (size.x / 6), pos.y + 250});
    sfSprite_setPosition(rpg->inventory->player_status->s_attack,
        (sfVector2f){pos.x - (size.x / 6), pos.y + 300});
    sfSprite_setPosition(rpg->inventory->player_status->s_def,
        (sfVector2f){pos.x - (size.x / 6), pos.y + 350});
    sfSprite_setPosition(rpg->inventory->player_status->s_speed,
        (sfVector2f){pos.x - (size.x / 6), pos.y + 400});
}

void display_selector(rpg_t *rpg)
{
    select_button_t *tmp = rpg->selector->buttons;

    sfRenderWindow_drawSprite(
        rpg->win->window, rpg->main_menu->background, NULL);
    for (; tmp != NULL; tmp = tmp->next) {
        if (strcmp(tmp->name, "BACK") == 0) {
            sfRenderWindow_drawText(rpg->win->window, tmp->text, NULL);
            continue;
        }
        set_sprites_pos(rpg, tmp);
        sfRenderWindow_drawRectangleShape(rpg->win->window, tmp->rect_shape,
            NULL);
        sfRenderWindow_drawSprite(rpg->win->window,
            rpg->inventory->player_status->pp, NULL);
        draw_stats(rpg, tmp);
    }
}
