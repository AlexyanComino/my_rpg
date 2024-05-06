/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_gobfire
*/

#include "rpg.h"

// static spe_t *init_spe_torch(char **infos)
// {
//     return NULL;
// }

entity_t *init_entity_torch(char **infos)
{
    entity_t *entity = malloc(sizeof(entity_t));

    entity->type = TORCH;
    entity->common = init_common(infos, TORCH);
    entity->spe = NULL;
    entity->in_view = false;
    entity->updt = &update_torch;
    entity->disp = &display_torch;
    entity->get_hitbox = &get_hitbox_torch;
    entity->get_hitbox_attack = &get_hitbox_attack_torch;
    return entity;
}
