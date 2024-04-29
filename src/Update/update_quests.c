/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_quests
*/

#include "rpg.h"

void check_quest_done(lwarrior_t *lwarrior, quest_t *tmp, rpg_t *rpg)
{
    if (lwarrior->warrior->state == DEAD &&
        strcmp(lwarrior->warrior->name, tmp->objective) == 0) {
        tmp->is_done = true;
        rpg->quest_header->state = Q_END;
        printf("Quest done: %s\n", tmp->name);
    }
}

void update_quest_list(rpg_t *rpg, quest_t *tmp)
{
    lwarrior_t *lwarrior = NULL;

    if (tmp->is_active && !tmp->is_done && tmp->type == KILL) {
        lwarrior = rpg->lwarrior->next;
        for (; lwarrior; lwarrior = lwarrior->next) {
            check_quest_done(lwarrior, tmp, rpg);
        }
    }
}

void update_quests(rpg_t *rpg)
{
    all_quests_t *quests = rpg->quests;
    quest_t *tmp = NULL;

    for (; quests; quests = quests->next) {
        tmp = quests->quest;
        for (; tmp; tmp = tmp->next) {
            update_quest_list(rpg, tmp);
        }
    }
}

void update_quest_header(rpg_t *rpg)
{
    sfColor color = {0, 0, 0, 0};
    sfColor color2 = {0, 0, 0, 0};
    sfColor color3 = {0, 0, 0, 0};

    if (rpg->quest_header->state == Q_START || rpg->quest_header->state == Q_END) {
        if (rpg->quest_header->myclock == NULL)
            rpg->quest_header->myclock = init_my_clock();
        rpg->quest_header->myclock->time = sfClock_getElapsedTime(rpg->quest_header->myclock->clock);
        rpg->quest_header->myclock->seconds = rpg->quest_header->myclock->time.microseconds / 1000000.0;
        if (rpg->quest_header->myclock->time.microseconds % 1 == 0) {
            color = sfText_getFillColor(rpg->quest_header->text);
            color2 = sfRectangleShape_getFillColor(rpg->quest_header->rect);
            if (color.a < 249) {
                if  (color2.a < 150)
                sfRectangleShape_setFillColor(rpg->quest_header->rect,
                    sfColor_fromRGBA(color2.r, color2.g, color2.b, color2.a + 10));
                sfText_setColor(rpg->quest_header->text, 
                    sfColor_fromRGBA(color.r, color.g, color.b, color.a + 10));
            }
        }
        if (rpg->quest_header->state == Q_END && rpg->quest_header->myclock->seconds > 2) {
            color3 = sfText_getFillColor(rpg->quest_header->done);
            if (color3.a < 249)
                sfText_setColor(rpg->quest_header->done, 
                    sfColor_fromRGBA(color3.r, color3.g, color3.b, color3.a + 10));
        }
        if (rpg->quest_header->myclock->seconds > 5) {
            sfRectangleShape_setFillColor(rpg->quest_header->rect,
                sfColor_fromRGBA(0, 0, 0, 0));
            sfText_setColor(rpg->quest_header->text,
                sfColor_fromRGBA(color.r, color.g, color.b, 0));
            rpg->quest_header->state = Q_HIDDEN;
            rpg->quest_header->myclock = NULL;
        }
    }
}