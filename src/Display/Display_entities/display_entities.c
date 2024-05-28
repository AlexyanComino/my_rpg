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
    for (unsigned int i = 0; i < rpg->ent_size; i++) {
        if (rpg->ent[i]->in_view) {
            rpg->ent[i]->disp(rpg, rpg->ent[i]);
        }
    }
    for (unsigned int i = 0; i < rpg->ent_size; i++) {
        if (rpg->ent[i]->in_view) {
            display_damage_texts(rpg, rpg->ent[i]->common->damage_texts);
        }
    }
}

static void display_grade_icon(rpg_t *rpg, entity_t *entity)
{
    if (entity->common->grade_type != SOLDAT)
        sfRenderWindow_drawSprite(rpg->win->window,
            entity->common->grade_icon->sprite, NULL);
}

void display_high_entities(rpg_t *rpg)
{
    entity_t *entity = NULL;

    for (unsigned int i = 0; i < rpg->ent_size; i++) {
        entity = rpg->ent[i];
        if (!entity->in_view || !is_alive(entity))
            continue;
        display_grade_icon(rpg, entity);
        if (entity->type == TORCH && entity->spe->torch->exclam->is_display == 1)
        sfRenderWindow_drawSprite(rpg->win->window,
            entity->spe->torch->exclam->anim->sprite, NULL);
    }
}
