/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** destroy_entity2
*/

#include "rpg.h"


static void destroy_spe_torch(spe_t *spe)
{
    destroy_mark(spe->torch->exclam);
    free(spe->torch);
    free(spe);
}

void destroy_entity_torch(entity_t *entity)
{
    destroy_common(entity->common);
    destroy_spe_torch(entity->spe);
    free(entity);
}

static void destroy_tnt(tnt_t *tnt)
{
    destroy_anim(tnt->dyna->anim);
    free(tnt->dyna->points);
    free(tnt->dyna);
    free(tnt->curve->points);
    sfConvexShape_destroy(tnt->curve->curve_shape);
    free(tnt->curve);
    destroy_anim(tnt->explo->anim);
    sfCircleShape_destroy(tnt->explo->boom_circle);
    sfSprite_destroy(tnt->explo->cible);
    sfTexture_destroy(tnt->explo->cible_texture);
    free(tnt->explo);
    free(tnt);
}

static void destroy_spe_tnt(spe_t *spe)
{
    destroy_tnt(spe->tnt);
    free(spe);
}

void destroy_entity_tnt(entity_t *entity)
{
    destroy_common(entity->common);
    destroy_spe_tnt(entity->spe);
    free(entity);
}

static void destroy_spe_archer(spe_t *spe)
{
    destroy_arrows(spe->archer->arrows);
    destroy_base(spe->archer->base);
    destroy_mark(spe->archer->exclam);
    destroy_mark(spe->archer->inter);
    free(spe->archer);
    free(spe);
}

void destroy_entity_archer(entity_t *entity)
{
    destroy_common(entity->common);
    destroy_spe_archer(entity->spe);
    free(entity);
}
