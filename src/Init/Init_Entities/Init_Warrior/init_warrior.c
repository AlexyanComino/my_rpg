/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_warrior
*/

#include "rpg.h"

mark_t *init_exclam(char **infos, float scale)
{
    mark_t *exclam = malloc(sizeof(mark_t));

    exclam->anim = init_anim("assets/Entities/Effects/exclam_anim.png",
        EXCLAM_WIDTH, EXCLAM_HEIGHT);
    exclam->pos = (sfVector2f){atoi(infos[3]), atoi(infos[4])};
    exclam->is_display = 0;
    sfSprite_setScale(exclam->anim->sprite, (sfVector2f){scale, scale});
    return exclam;
}

mark_t *init_inter(char **infos, float scale)
{
    mark_t *inter = malloc(sizeof(mark_t));

    inter->anim = init_anim("assets/Entities/Effects/inter_anim.png",
        INTER_WIDTH, INTER_HEIGHT);
    inter->pos = (sfVector2f){atoi(infos[3]), atoi(infos[4])};
    inter->is_display = 0;
    sfSprite_setScale(inter->anim->sprite, (sfVector2f){scale, scale});
    return inter;
}

static warrior_t *init_warrior(char **infos, float scale)
{
    warrior_t *warrior = malloc(sizeof(warrior_t));

    warrior->line_attack = 0;
    warrior->max_line_attack = 0;
    warrior->exclam = init_exclam(infos, scale);
    warrior->inter = init_inter(infos, scale);
    warrior->base = init_base(infos);
    return warrior;
}

static spe_t *init_spe_warrior(char **infos, float scale)
{
    spe_t *spe = malloc(sizeof(spe_t));

    spe->warrior = init_warrior(infos, scale);
    return spe;
}

entity_t *init_entity_warrior(char **infos)
{
    entity_t *entity = malloc(sizeof(entity_t));

    entity->type = WARRIOR;
    entity->common = init_common(infos, WARRIOR);
    entity->spe = init_spe_warrior(infos, entity->common->scale);
    entity->updt = &update_warrior;
    entity->disp = &display_warrior;
    entity->destroy = &destroy_entity_warrior;
    entity->anim = &anim_warrior;
    entity->get_hitbox = &get_hitbox_warrior;
    entity->get_hitbox_attack = &get_warrior_hitbox_attack;
    entity->get_hitbox_foot = &get_hitbox_warrior_foot;
    entity->in_view = false;
    return entity;
}
