/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** displayAll
*/

#include "rpg.h"

static void draw_circles_hitbox(rpg_t *rpg, warrior_t *warrior)
{
    sfRenderWindow_drawCircleShape(rpg->win->window,
        warrior->exclam->circle, NULL);
    sfRenderWindow_drawCircleShape(rpg->win->window,
        warrior->inter->circle, NULL);
    sfRenderWindow_drawCircleShape(rpg->win->window,
        warrior->zones->circle_reset, NULL);
}

static void display_alive_warrior(rpg_t *rpg, warrior_t *warrior)
{
    warrior_t *player = rpg->lwarrior->warrior;

    sfRenderWindow_drawSprite(rpg->win->window, warrior->sprite, NULL);
    if (warrior->exclam->is_display)
        sfRenderWindow_drawSprite(rpg->win->window, warrior->exclam->sprite,
            NULL);
    if (warrior->inter->is_display)
        sfRenderWindow_drawSprite(rpg->win->window, warrior->inter->sprite,
            NULL);
    if (rpg->debug) {
        sfRenderWindow_drawRectangleShape(rpg->win->window,
            warrior->zones->rect_hitbox, NULL);
        sfRenderWindow_drawRectangleShape(rpg->win->window,
            warrior->zones->rect_hitbox_attack, NULL);
        if (warrior != player)
            draw_circles_hitbox(rpg, warrior);
    }
}

static void display_warrior(rpg_t *rpg, warrior_t *warrior)
{
    if (warrior->state == DEAD)
        sfRenderWindow_drawSprite(rpg->win->window,
        warrior->death->sprite_dead, NULL);
    else {
        sfRenderWindow_drawSprite(rpg->win->window,
        warrior->death->sprite_dead, NULL);
        display_alive_warrior(rpg, warrior);
    }
}

static void display_warriors(rpg_t *rpg)
{
    lwarrior_t *tmp = rpg->lwarrior->next;

    while (tmp) {
        if (tmp->warrior->state != RIEN)
            display_warrior(rpg, tmp->warrior);
        tmp = tmp->next;
    }
    display_warrior(rpg, rpg->lwarrior->warrior);
}

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
    button_t *tmp = rpg->save_menu->buttons;

    sfRenderWindow_drawSprite(
        rpg->win->window, rpg->main_menu->background, NULL);
    while (tmp != NULL) {
        if (strcmp(tmp->name, "BACK") != 0)
            sfRenderWindow_drawRectangleShape(rpg->win->window, tmp->rect_shape,
                NULL);
        sfRenderWindow_drawText(rpg->win->window, tmp->text, NULL);
        tmp = tmp->next;
    }
}

void display_quests(rpg_t *rpg)
{
    all_quests_t *tmp = rpg->quests;

    while (tmp != NULL) {
        if (tmp->warrior != NULL && is_player_interact_warrior(rpg, tmp->warrior) == false)
            tmp->quest->is_displayed = false;
        if (tmp->quest->is_displayed == true) {
            sfRenderWindow_drawText(rpg->win->window, rpg->quest_text, NULL);
            sfRenderWindow_drawText(rpg->win->window, rpg->quest_desc, NULL);
            sfRenderWindow_drawText(rpg->win->window, rpg->quest_info, NULL);
        }
        tmp = tmp->next;
    }

}

void display_all(rpg_t *rpg)
{
    sfRenderWindow_clear(rpg->win->window, sfBlack);
    if (rpg->gamestate == MAIN_MENU)
        display_main_menu(rpg);
    if (rpg->gamestate == SAVE_MENU)
        display_save_menu(rpg);
    if (rpg->gamestate == SETTINGS)
        display_settings(rpg);
    if (rpg->gamestate == GAME) {
        display_warriors(rpg);
        display_quests(rpg);
    }
    sfRenderWindow_display(rpg->win->window);
}
