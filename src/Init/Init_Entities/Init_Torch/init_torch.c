/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_gobfire
*/

#include "rpg.h"

static mark_t *init_gob_exclam(char **infos)
{
    mark_t *exclam = malloc(sizeof(mark_t));

    exclam->anim = init_anim("assets/Entities/Effects/gob_exclam.png",
        GOB_EXCLAM_WIDTH, GOB_EXCLAM_HEIGHT);
    sfSprite_setScale(exclam->anim->sprite, (sfVector2f){0.5, 0.5});
    exclam->pos = (sfVector2f){atoi(infos[3]), atoi(infos[4])};
    exclam->is_display = 0;
    return exclam;
}

static torch_t *init_torch(char **infos)
{
    torch_t *torch = malloc(sizeof(torch_t));

    torch->exclam = init_gob_exclam(infos);
    return torch;
}

static spe_t *init_spe_torch(char **infos)
{
    spe_t *spe = malloc(sizeof(spe_t));

    spe->torch = init_torch(infos);
    return spe;
}

entity_t *init_entity_torch(char **infos)
{
    entity_t *entity = malloc(sizeof(entity_t));

    entity->type = TORCH;
    entity->common = init_common(infos, TORCH);
    entity->spe = init_spe_torch(infos);
    entity->in_view = false;
    entity->updt = &update_torch;
    entity->disp = &display_torch;
    entity->anim = &anim_torch;
    entity->destroy = &destroy_entity_torch;
    entity->get_hitbox = &get_hitbox_torch;
    entity->get_hitbox_attack = &get_hitbox_attack_torch;
    entity->get_hitbox_foot = &get_hitbox_torch_foot;
    return entity;
}
