/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** destroy_entity
*/

#include "rpg.h"

static void destroy_warrior(warrior_t *warrior)
{
    destroy_base(warrior->base);
    destroy_mark(warrior->exclam);
    destroy_mark(warrior->inter);
    free(warrior);
}

static void destroy_spe_warrior(spe_t *spe)
{
    destroy_warrior(spe->warrior);
    free(spe);
}

void destroy_entity_warrior(entity_t *entity)
{
    destroy_common(entity->common);
    destroy_spe_warrior(entity->spe);
    free(entity);
}

static void destroy_spe_pawn(spe_t *spe)
{
    free(spe->pawn);
    free(spe);
}

void destroy_entity_pawn(entity_t *entity)
{
    destroy_common(entity->common);
    entity->common = NULL;
    destroy_spe_pawn(entity->spe);
    entity->spe = NULL;
    free(entity);
}
