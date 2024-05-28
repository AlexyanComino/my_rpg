/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_archer
*/

#include "rpg.h"

static archer_t *init_archer(char **infos, float scale)
{
    archer_t *archer = malloc(sizeof(archer_t));

    archer->arrows = NULL;
    archer->base = init_base(infos);
    archer->exclam = init_exclam(infos, scale);
    archer->inter = init_inter(infos, scale);
    return archer;
}

static spe_t *init_spe_archer(char **infos, float scale)
{
    spe_t *spe = malloc(sizeof(spe_t));

    spe->archer = init_archer(infos, scale);
    return spe;
}

entity_t *init_entity_archer(char **infos)
{
    entity_t *entity = malloc(sizeof(entity_t));

    entity->type = ARCHER;
    entity->common = init_common(infos, ARCHER);
    entity->spe = init_spe_archer(infos, entity->common->scale);
    entity->in_view = false;
    entity->updt = &update_archer;
    entity->disp = &display_archer;
    entity->anim = &anim_archer;
    entity->destroy = &destroy_entity_archer;
    entity->get_hitbox = &get_hitbox_archer;
    entity->get_hitbox_attack = &get_hitbox_attack_archer;
    entity->get_hitbox_foot = &get_hitbox_archer_foot;
    return entity;
}
