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

void display_quests(rpg_t *rpg)
{
    all_quests_t *tmp = rpg->quests;

    while (tmp != NULL) {
        if (tmp->entity != NULL &&
            is_player_interact_entity(rpg, tmp->entity) == false)
            tmp->quest->is_displayed = false;
        if (tmp->quest->is_displayed == true) {
            sfRenderWindow_drawText(rpg->win->window, rpg->quest_text, NULL);
            sfRenderWindow_drawText(rpg->win->window, rpg->quest_desc, NULL);
            sfRenderWindow_drawText(rpg->win->window, rpg->quest_info, NULL);
        }
        tmp = tmp->next;
    }
}

static void display_restricted_text(rpg_t *rpg)
{
    restricted_t *restricted = rpg->interface->restricted;
    entity_t *player = rpg->ent[0];

    if (!is_alive(player))
        return;
    sfRenderWindow_drawSprite(rpg->win->window, restricted->sprite, NULL);
}

static void display_collision(rpg_t *rpg)
{
    collision_t *collision = rpg->collision;
    unsigned int col = rpg->ent[0]->common->pos.x / WIDTH;
    unsigned int row = rpg->ent[0]->common->pos.y / HEIGHT;

    if (col >= collision->cols || row >= collision->rows)
        return;
    for (unsigned int i = 0; i < collision->regions[col][row]->size; i++) {
        collision->rect.left = collision->regions[col][row]->pos[i].x;
        collision->rect.top = collision->regions[col][row]->pos[i].y;
        if (!intrect_is_in_view(rpg, collision->rect))
            continue;
        sfRectangleShape_setPosition(collision->shape,
            (sfVector2f){collision->rect.left, collision->rect.top});
        sfRenderWindow_drawRectangleShape(rpg->win->window, collision->shape,
            NULL);
    }
    sfRectangleShape_setPosition(collision->region_shape,
        (sfVector2f){col * WIDTH, row * HEIGHT});
    sfRenderWindow_drawRectangleShape(rpg->win->window,
        collision->region_shape, NULL);
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
        display_entities(rpg);
        display_quests(rpg);
        sfRenderWindow_drawSprite(rpg->win->window, rpg->map->high_sprite,
            NULL);
        if (rpg->debug)
            display_collision(rpg);
        display_inv(rpg);
        display_restricted_text(rpg);
    }
    sfRenderWindow_display(rpg->win->window);
}
