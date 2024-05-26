/*
** EPITECH PROJECT, 2024
** skill
** File description:
** skill tree
*/

#include <stdio.h>
#include <stdlib.h>
#include "rpg.h"
#include "skill_tree.h"

int draw_ui_tree(rpg_t *rpg)
{
    static sfText *title = NULL;

    if (title == NULL) {
        title = init_text((sfVector2f){100, 100}, 100, sfWhite, "Skill Tree");
        sfText_setFont(title,
        sfFont_createFromFile("assets/fonts/BreatheFireIii-PKLOB.ttf"));
        sfText_setOrigin(title,
        (sfVector2f){sfText_getLocalBounds(title).width / 2, 0});
    }
    sfText_setPosition(title, (sfVector2f){(*view_pos()).x,
    (*view_pos()).y - 500});
    sfRenderWindow_drawText(rpg->win->window, title, NULL);
    return 1;
}

int draw_tree(rpg_t *rpg)
{
    skill_t *tmp = rpg->skill_tree;
    sfVector2f pos = {-260, 300};
    int nb = 0;

    while (tmp != NULL) {
        if (tmp->next == NULL)
            pos.x += 175;
        sfSprite_setPosition(tmp->background, (sfVector2f)
        {pos.x + (*view_pos()).x, pos.y + (*view_pos()).y});
        sfRenderWindow_drawSprite(rpg->win->window, tmp->background, NULL);
        sfSprite_setPosition(tmp->logo, (sfVector2f)
        {pos.x + + (*view_pos()).x + 50, pos.y + (*view_pos()).y + 50});
        sfRenderWindow_drawSprite(rpg->win->window, tmp->logo, NULL);
        if (tmp->unlocked == 0) {
            sfSprite_setPosition(tmp->locked, (sfVector2f)
            {pos.x  - 10 + (*view_pos()).x, pos.y - 10 + (*view_pos()).y});
            sfRenderWindow_drawSprite(rpg->win->window, tmp->locked, NULL);
        }
        pos.x += 175;
        nb++;
        if (nb == 3) {
            pos.x = -260;
            pos.y -= 200;
            nb = 0;
        }
        tmp = tmp->next;
    }
    return 1;
}

int draw_skill_tree(rpg_t *rpg)
{
    if (rpg->gamestate != SKILL_TREE)
        return 0;
    draw_ui_tree(rpg);
    draw_tree(rpg);
    highlight_skill_tree(rpg);
    return 1;
}
