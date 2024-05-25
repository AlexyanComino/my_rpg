/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** damage_text
*/

#include "rpg.h"

void add_dmg_text(rpg_t *rpg, entity_t *entity, int attack,
    damage_text_state_t state)
{
    damage_text_t *new = init_damage_text(rpg, entity, attack, state);
    damage_text_t *tmp = entity->common->damage_texts;

    if (tmp == NULL) {
        entity->common->damage_texts = new;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

//
static void remove_damage_text(damage_text_t **damage_texts,
    damage_text_t *tmp)
{
    damage_text_t *prev = *damage_texts;

    if (prev == tmp) {
        *damage_texts = tmp->next;
        destroy_damage_text(tmp);
        return;
    }
    while (prev->next != tmp)
        prev = prev->next;
    prev->next = tmp->next;
    destroy_damage_text(tmp);
}

static void change_pos_and_alpha(damage_text_t *tmp, sfColor color)
{
    sfColor shadow_color = sfText_getOutlineColor(tmp->text);

    if (tmp->state != CRITICAL && tmp->state != BAM) {
        tmp->pos.y -= 1.5;
        sfText_setPosition(tmp->text, tmp->pos);
    }
    color.a -= 5;
    sfText_setColor(tmp->text, color);
    shadow_color.a -= 5;
    sfText_setOutlineColor(tmp->text, shadow_color);
}

void update_damage_texts(damage_text_t **damage_texts)
{
    damage_text_t *tmp = *damage_texts;
    damage_text_t *next = NULL;
    sfColor color;

    if (tmp == NULL)
        return;
    while (tmp != NULL) {
        next = tmp->next;
        color = sfText_getColor(tmp->text);
        if (color.a <= 0) {
            remove_damage_text(damage_texts, tmp);
            tmp = next;
            continue;
        }
        change_pos_and_alpha(tmp, color);
        tmp = next;
    }
}
