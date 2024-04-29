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
            sfRenderWindow_drawRectangleShape(rpg->win->window,
                tmp->rect_shape, NULL);
        sfRenderWindow_drawText(rpg->win->window, tmp->text, NULL);
        tmp = tmp->next;
    }
}

static void display_text(rpg_t *rpg)
{

    int len = strlen(rpg->text_box->str);

    if (rpg->text_box->is_fully_displayed) {
        sfText_setString(rpg->text_box->npc_text, rpg->text_box->str);
        sfRenderWindow_drawText(rpg->win->window, rpg->text_box->npc_text, NULL);
    }
    if (!rpg->text_box->is_fully_displayed && rpg->text_box->len < len) {
        rpg->text_box->displayed_str[rpg->text_box->len] = rpg->text_box->str[rpg->text_box->len];
        rpg->text_box->displayed_str[rpg->text_box->len + 1] = '\0';
        sfText_setString(rpg->text_box->npc_text, rpg->text_box->displayed_str);
        sfRenderWindow_drawText(rpg->win->window, rpg->text_box->npc_text, NULL);
        if (sfTime_asMilliseconds(sfClock_getElapsedTime(rpg->text_box->clock)) >= 25) {
            rpg->text_box->len++;
            sfClock_restart(rpg->text_box->clock);
        }
    } else
        rpg->text_box->is_fully_displayed = true;
}

void display_text_box(rpg_t *rpg)
{
    if (rpg->text_box->is_displayed == true) {
        sfSprite_setPosition(rpg->text_box->box, (sfVector2f){rpg->
            lwarrior->warrior->pos.x - 300, rpg->lwarrior->warrior->pos.y +
            300});
        sfText_setPosition(rpg->text_box->npc_name, (sfVector2f){rpg->
            lwarrior->warrior->pos.x - 200, rpg->lwarrior->warrior->pos.y + 275});
        sfText_setPosition(rpg->text_box->npc_text, (sfVector2f){rpg->
            lwarrior->warrior->pos.x - 200, rpg->lwarrior->warrior->pos.y + 380});
        sfRenderWindow_drawSprite(rpg->win->window, rpg->text_box->box,
            NULL);
        sfRenderWindow_drawText(rpg->win->window, rpg->text_box->npc_name, NULL);
        display_text(rpg);
    }

}

void display_quests(rpg_t *rpg)
{
    if (rpg->quest_header->state == Q_START || rpg->quest_header->state == Q_END) {
        sfText_setPosition(rpg->quest_header->text, (sfVector2f){rpg->lwarrior->
            warrior->pos.x - 400, rpg->lwarrior->warrior->pos.y - 370});
        sfRectangleShape_setPosition(rpg->quest_header->rect, (sfVector2f){rpg->
            lwarrior->warrior->pos.x - WIDTH / 2, rpg->lwarrior->warrior->pos.y -
            400});
        sfText_setPosition(rpg->quest_header->done, (sfVector2f){rpg->lwarrior->
            warrior->pos.x + 200, rpg->lwarrior->warrior->pos.y - 250});
        sfRenderWindow_drawRectangleShape(rpg->win->window, rpg->
            quest_header->rect, NULL);
        sfRenderWindow_drawText(rpg->win->window, rpg->quest_header->text, NULL);
        if (rpg->quest_header->state == Q_END)
            sfRenderWindow_drawText(rpg->win->window, rpg->quest_header->done, NULL);
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
    if (rpg->gamestate == SAVE_MENU)
        display_save_menu(rpg);
    if (rpg->gamestate == SETTINGS)
        display_settings(rpg);
    if (rpg->gamestate == GAME || rpg->gamestate == INVENTORY) {
        sfRenderWindow_drawSprite(rpg->win->window, rpg->map->ground_sprite,
            NULL);
        display_warriors(rpg);
        //sfRenderWindow_drawSprite(rpg->win->window, rpg->map->high_sprite,
        //    NULL);
        if (rpg->debug)
            display_collision(rpg);
        update_inv(rpg);
        display_restricted_text(rpg);
        display_text_box(rpg);
        display_quests(rpg);
    }
    sfRenderWindow_display(rpg->win->window);
}
