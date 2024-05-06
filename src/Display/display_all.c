/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** displayAll
*/

#include "rpg.h"
#include "singleton.h"

static void add_letter(rpg_t *rpg, sfFloatRect rect, sfVector2f pos)
{
    rpg->text_box->displayed_str[rpg->text_box->len] =
        rpg->text_box->str[rpg->text_box->len];
    rpg->text_box->displayed_str[rpg->text_box->len + 1] = '\0';
    sfText_setString(rpg->text_box->npc_text,
        rpg->text_box->displayed_str);
    sfText_setOrigin(rpg->text_box->npc_text,
        (sfVector2f){rect.width / 2, rect.height / 2});
    sfText_setPosition(rpg->text_box->npc_text,
        (sfVector2f){pos.x, pos.y - 10});
    sfRenderWindow_drawText(rpg->win->window,
        rpg->text_box->npc_text, NULL);
    if (sfTime_asMilliseconds(
        sfClock_getElapsedTime(rpg->text_box->clock)) >= 25) {
        rpg->text_box->len++;
        sfClock_restart(rpg->text_box->clock);
    }
}

static void display_text(rpg_t *rpg)
{
    int len = strlen(rpg->text_box->str);
    sfVector2f pos = sfSprite_getPosition(rpg->text_box->box);
    sfFloatRect rect = sfText_getGlobalBounds(rpg->text_box->npc_text);

    if (!rpg->text_box->is_fully_displayed && rpg->text_box->len < len) {
        add_letter(rpg, rect, pos);
    } else
        rpg->text_box->is_fully_displayed = true;
    if (rpg->text_box->is_fully_displayed) {
        sfText_setString(rpg->text_box->npc_text, rpg->text_box->str);
        sfText_setOrigin(rpg->text_box->npc_text, (sfVector2f){
            rect.width / 2, rect.height / 2});
        sfText_setPosition(rpg->text_box->npc_text, (sfVector2f){
            pos.x, pos.y - 10});
        sfRenderWindow_drawText(rpg->win->window,
            rpg->text_box->npc_text, NULL);
    }
}

static void move_rect(button_t *tmp)
{
    if (tmp->state == HOVERED) {
        tmp->rect.top = 100;
        sfSprite_setTextureRect(tmp->sprite, tmp->rect);
    } else {
        tmp->rect.top = 0;
        sfSprite_setTextureRect(tmp->sprite, tmp->rect);
    }
}

void display_choices(rpg_t *rpg)
{
    button_t *tmp = rpg->text_box->choice;
    int i = 0;

    if (rpg->text_box->is_fully_displayed != true ||
        rpg->text_box->dialog->next != NULL)
        return;
    for (; tmp != NULL; tmp = tmp->next) {
        move_rect(tmp);
        sfSprite_setPosition(tmp->sprite, (sfVector2f){rpg->ent[0]->common->
        pos.x + 500, rpg->ent[0]->common->pos.y + 300 + (i * 50)});
        sfText_setPosition(tmp->text, (sfVector2f){rpg->ent[0]->common->pos.x
        + 540, rpg->ent[0]->common->pos.y + 318 + (i * 50)});
        sfRenderWindow_drawSprite(rpg->win->window, tmp->sprite, NULL);
        sfRenderWindow_drawText(rpg->win->window, tmp->text, NULL);
        i++;
    }
}

void display_text_box(rpg_t *rpg)
{
    if (rpg->text_box->is_displayed == true) {
        sfSprite_setPosition(rpg->text_box->box, (sfVector2f){rpg->
            ent[0]->common->pos.x, rpg->ent[0]->common->pos.y + 400});
        sfText_setPosition(rpg->text_box->npc_name, (sfVector2f){rpg->
        ent[0]->common->pos.x - 200, rpg->ent[0]->common->pos.y + 280});
        display_choices(rpg);
        sfRenderWindow_drawSprite(rpg->win->window, rpg->text_box->box,
            NULL);
        sfRenderWindow_drawText(rpg->win->window, rpg->text_box->npc_name,
            NULL);
        display_text(rpg);
    }
}

void display_quests(rpg_t *rpg)
{
    if (rpg->quest_header->state == Q_START
        || rpg->quest_header->state == Q_END) {
        sfText_setPosition(rpg->quest_header->text, (sfVector2f){
            rpg->ent[0]->common->pos.x - 400,
            rpg->ent[0]->common->pos.y - 370});
        sfRectangleShape_setPosition(rpg->quest_header->rect, (sfVector2f){
            rpg->ent[0]->common->pos.x - WIDTH / 2,
            rpg->ent[0]->common->pos.y - 400});
        sfText_setPosition(rpg->quest_header->done, (sfVector2f){rpg->
        ent[0]->common->pos.x + 200, rpg->ent[0]->common->pos.y - 250});
        sfRenderWindow_drawRectangleShape(rpg->win->window, rpg->
            quest_header->rect, NULL);
        sfRenderWindow_drawText(rpg->win->window,
            rpg->quest_header->text, NULL);
        if (rpg->quest_header->state == Q_END)
            sfRenderWindow_drawText(rpg->win->window,
                rpg->quest_header->done, NULL);
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

void display_game(rpg_t *rpg)
{
    sfRenderWindow_drawSprite(rpg->win->window, rpg->map->ground_sprite,
        NULL);
    display_entities(rpg);
    sfRenderWindow_drawSprite(rpg->win->window, rpg->map->high_sprite,
        NULL);
    if (rpg->debug)
        display_collision(rpg);
    display_inv(rpg);
    display_restricted_text(rpg);
    display_text_box(rpg);
    display_quests(rpg);
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
    if (rpg->gamestate == GAME || rpg->gamestate == INVENTORY)
        display_game(rpg);
    sfRenderWindow_display(rpg->win->window);
}
