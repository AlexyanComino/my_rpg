/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_archer
*/

#include "rpg.h"

static archer_t *init_archer(char **infos)
{
    archer_t *archer = malloc(sizeof(archer_t));

    archer->arrows = NULL;
    archer->base = init_base(infos);
    return archer;
}

static spe_t *init_spe_archer(char **infos)
{
    spe_t *spe = malloc(sizeof(spe_t));

    spe->archer = init_archer(infos);
    return spe;
}

entity_t *init_entity_archer(char **infos)
{
    entity_t *entity = malloc(sizeof(entity_t));

    entity->type = ARCHER;
    entity->common = init_common(infos, ARCHER);
    entity->spe = init_spe_archer(infos);
    entity->in_view = false;
    entity->updt = &update_archer;
    entity->disp = &display_archer;
    entity->get_hitbox = &get_hitbox_archer;
    entity->get_hitbox_attack = &get_hitbox_attack_archer;
    entity->get_hitbox_foot = &get_hitbox_archer_foot;
    return entity;
}
