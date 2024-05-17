/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** display_text_box
*/

#include "rpg.h"

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
    entity_t *player = get_player(rpg);

    if (rpg->text_box->is_fully_displayed != true ||
        rpg->text_box->dialog->next != NULL)
        return;
    for (; tmp != NULL; tmp = tmp->next) {
        move_rect(tmp);
        sfSprite_setPosition(tmp->sprite, (sfVector2f){player->common->
        pos.x + 500, player->common->pos.y + 300 + (i * 50)});
        sfText_setPosition(tmp->text, (sfVector2f){player->common->pos.x
        + 540, player->common->pos.y + 318 + (i * 50)});
        sfRenderWindow_drawSprite(rpg->win->window, tmp->sprite, NULL);
        sfRenderWindow_drawText(rpg->win->window, tmp->text, NULL);
        i++;
    }
}

void display_text_box(rpg_t *rpg)
{
    entity_t *player;

    if (rpg->text_box->is_displayed == true) {
        player = get_player(rpg);
        sfSprite_setPosition(rpg->text_box->box,
            (sfVector2f){player->common->pos.x, player->common->pos.y + 400});
        sfText_setPosition(rpg->text_box->npc_name,
            (sfVector2f){player->common->pos.x - 200,
            player->common->pos.y + 280});
        display_choices(rpg);
        sfRenderWindow_drawSprite(rpg->win->window, rpg->text_box->box,
            NULL);
        sfRenderWindow_drawText(rpg->win->window, rpg->text_box->npc_name,
            NULL);
        display_text(rpg);
    }
}
