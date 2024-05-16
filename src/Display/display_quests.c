/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** display_quests
*/

#include "rpg.h"

void display_quests(rpg_t *rpg)
{
    entity_t *player = get_player(rpg);

    if (rpg->quest_header->state == Q_START
        || rpg->quest_header->state == Q_END) {
        sfText_setPosition(rpg->quest_header->text, (sfVector2f){
            player->common->pos.x - 400, player->common->pos.y - 370});
        sfRectangleShape_setPosition(rpg->quest_header->rect, (sfVector2f){
            player->common->pos.x - WIDTH / 2,
            player->common->pos.y - 400});
        sfText_setPosition(rpg->quest_header->done, (sfVector2f){rpg->
        ent[0]->common->pos.x + 200, player->common->pos.y - 250});
        sfRenderWindow_drawRectangleShape(rpg->win->window, rpg->
            quest_header->rect, NULL);
        sfRenderWindow_drawText(rpg->win->window,
            rpg->quest_header->text, NULL);
        if (rpg->quest_header->state == Q_END)
            sfRenderWindow_drawText(rpg->win->window,
                rpg->quest_header->done, NULL);
    }
}
