/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_quest_header
*/

#include "rpg.h"

void update_header_color(rpg_t *rpg, sfColor *color)
{
    sfColor color2 = sfRectangleShape_getFillColor(rpg->quest_header->rect);
    sfColor color3 = sfRectangleShape_getFillColor(rpg->quest_header->rect2);

    if (color->a < 249) {
        if (color2.a < 150) {
            sfRectangleShape_setFillColor(rpg->quest_header->rect,
                sfColor_fromRGBA(color2.r, color2.g, color2.b, color2.a + 10));
            sfRectangleShape_setFillColor(rpg->quest_header->rect2,
                sfColor_fromRGBA(color3.r, color3.g, color3.b, color3.a + 10));
        }
        sfText_setColor(rpg->quest_header->text,
            sfColor_fromRGBA(color->r, color->g, color->b, color->a + 10));
    }
}

void update_done_text(rpg_t *rpg)
{
    sfColor color3 = {0, 0, 0, 0};

    if (rpg->quest_header->state == Q_END
        && rpg->quest_header->myclock->seconds > 2) {
        color3 = sfText_getFillColor(rpg->quest_header->done);
        if (color3.a < 249)
            sfText_setColor(rpg->quest_header->done,
                sfColor_fromRGBA(color3.r, color3.g, color3.b, color3.a + 10));
    }
}

void remove_header(rpg_t *rpg, sfColor *color)
{
    sfColor color2 = sfText_getColor(rpg->quest_header->done);

    sfRectangleShape_setFillColor(rpg->quest_header->rect,
            sfColor_fromRGBA(0, 0, 0, 0));
    sfRectangleShape_setFillColor(rpg->quest_header->rect2,
            sfColor_fromRGBA(0, 0, 0, 0));
    sfText_setColor(rpg->quest_header->text,
        sfColor_fromRGBA(color->r, color->g, color->b, 0));
    sfText_setColor(rpg->quest_header->done,
        sfColor_fromRGBA(color2.r, color2.g, color2.b, 0));
    rpg->quest_header->state = Q_HIDDEN;
    rpg->quest_header->myclock = NULL;
}

static void update_header_pos(rpg_t *rpg)
{
    sfRectangleShape_setPosition(rpg->quest_header->rect, (sfVector2f){
        rpg->ent[0]->common->pos.x - WIDTH / 2,
        rpg->ent[0]->common->pos.y - 400});
    sfRectangleShape_setPosition(rpg->quest_header->rect2, (sfVector2f){
        rpg->ent[0]->common->pos.x - WIDTH / 2,
        rpg->ent[0]->common->pos.y - 390});
    sfText_setPosition(rpg->quest_header->done, (sfVector2f){
        rpg->ent[0]->common->pos.x + 200,
        rpg->ent[0]->common->pos.y - 250});
}

void update_quest_header(rpg_t *rpg)
{
    sfColor color = {0, 0, 0, 0};

    if (rpg->quest_header->state != Q_START
        && rpg->quest_header->state != Q_END)
        return;
    if (rpg->quest_header->myclock == NULL)
        rpg->quest_header->myclock = init_my_clock();
    update_clock_seconds(rpg->quest_header->myclock);
    update_header_pos(rpg);
    if (rpg->quest_header->myclock->time.microseconds % 1 == 0) {
        color = sfText_getFillColor(rpg->quest_header->text);
        update_header_color(rpg, &color);
    }
    update_done_text(rpg);
    if (rpg->quest_header->myclock->seconds > 5)
        remove_header(rpg, &color);
}
