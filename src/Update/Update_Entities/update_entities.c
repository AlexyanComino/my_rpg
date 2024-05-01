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

void update_entities(rpg_t *rpg)
{
    update_entities_in_view(rpg);
    for (unsigned int i = 0; i < rpg->ent_size; i++) {
        if (rpg->ent[i]->in_view) {
            rpg->ent[i]->updt(rpg, rpg->ent[i]);
        }
    }
}
