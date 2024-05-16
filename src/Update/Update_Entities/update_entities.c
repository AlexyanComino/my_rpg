/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_entities
*/

#include "rpg.h"

static void update_entities_in_view(rpg_t *rpg)
{
    for (unsigned int i = 0; i < rpg->ent_size; i++) {
        if (entity_is_in_view(rpg, rpg->ent[i])) {
            rpg->ent[i]->in_view = true;
        } else {
            rpg->ent[i]->in_view = false;
        }
    }
}

static void change_player_index(rpg_t *rpg, unsigned int i, unsigned int j)
{
    if (i == rpg->player_index)
        rpg->player_index = j;
    else if (j == rpg->player_index)
        rpg->player_index = i;
}

static void update_ent2(rpg_t *rpg, unsigned int i, unsigned int j)
{
    entity_t *tmp = NULL;

    if (i == j)
        return;
    if (rpg->ent[i]->common->pos.y > rpg->ent[j]->common->pos.y) {
        change_player_index(rpg, i, j);
        tmp = rpg->ent[i];
        rpg->ent[i] = rpg->ent[j];
        rpg->ent[j] = tmp;
    }
}

static void update_ent(rpg_t *rpg)
{
    for (unsigned int i = 0; i < rpg->ent_size; i++) {
        for (unsigned int j = i + 1; j < rpg->ent_size; j++) {
            update_ent2(rpg, i, j);
        }
    }
}

void update_entities(rpg_t *rpg)
{
    update_entities_in_view(rpg);
    update_ent(rpg);
    for (unsigned int i = 0; i < rpg->ent_size; i++) {
        if (rpg->ent[i]->in_view) {
            rpg->ent[i]->updt(rpg, rpg->ent[i]);
        }
    }
}
