/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** display_quests
*/

#include "rpg.h"

static void set_pos(rpg_t *rpg, entity_t *player)
{
    sfFloatRect rect = sfText_getGlobalBounds(rpg->quest_header->text);

    sfText_setOrigin(rpg->quest_header->text, (sfVector2f){
        rect.width / 2, rect.height / 2});
    sfText_setPosition(rpg->quest_header->text, (sfVector2f){
        player->common->pos.x, player->common->pos.y - 340});
    sfRectangleShape_setPosition(rpg->quest_header->rect, (sfVector2f){
        player->common->pos.x - WIDTH / 2,
        player->common->pos.y - 400});
    sfRectangleShape_setPosition(rpg->quest_header->rect2, (sfVector2f){
        player->common->pos.x - WIDTH / 2,
        player->common->pos.y - 390});
    sfText_setPosition(rpg->quest_header->done, (sfVector2f){
        player->common->pos.x + 200, player->common->pos.y - 250});
}

void display_quests(rpg_t *rpg)
{
    entity_t *player = get_player(rpg);

    if (rpg->quest_header->state == Q_START
        || rpg->quest_header->state == Q_END) {
        set_pos(rpg, player);
        sfRenderWindow_drawRectangleShape(rpg->win->window, rpg->
            quest_header->rect, NULL);
        sfRenderWindow_drawRectangleShape(rpg->win->window, rpg->
            quest_header->rect2, NULL);
        sfRenderWindow_drawText(rpg->win->window,
            rpg->quest_header->text, NULL);
        if (rpg->quest_header->state == Q_END) {
            sfRenderWindow_drawText(rpg->win->window,
                rpg->quest_header->done, NULL);
        }
    }
}
