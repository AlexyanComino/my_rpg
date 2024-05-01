/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** display_entities
*/

#include "rpg.h"

static void display_damage_texts(rpg_t *rpg, damage_text_t *damage_texts)
{
    damage_text_t *tmp = damage_texts;

    if (tmp == NULL)
        return;
    while (tmp) {
        if (tmp->effect != NULL) {
            sfRenderWindow_drawSprite(rpg->win->window,
                tmp->effect->sprite, NULL);
        }
        sfRenderWindow_drawText(rpg->win->window, tmp->text, NULL);
        tmp = tmp->next;
    }
}

void display_entities(rpg_t *rpg)
{
    for (unsigned int i = 1; i < rpg->ent_size; i++) {
        if (rpg->ent[i]->in_view) {
            rpg->ent[i]->disp(rpg, rpg->ent[i]);
        }
    }
    rpg->ent[0]->disp(rpg, rpg->ent[0]);
    for (unsigned int i = 1; i < rpg->ent_size; i++) {
        if (rpg->ent[i]->in_view) {
            display_damage_texts(rpg, rpg->ent[i]->common->damage_texts);
        }
    }
    display_damage_texts(rpg, rpg->ent[0]->common->damage_texts);
}
