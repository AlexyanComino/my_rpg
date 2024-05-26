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

static void destroy_carry(carry_t *carry)
{
    item_pawn_t *tmp = NULL;

    if (carry == NULL)
        return;
    if (carry->item != NULL) {
        tmp = carry->item;
        free(tmp->name);
        sfSprite_destroy(tmp->sprite);
        sfTexture_destroy(tmp->texture);
        free(tmp->index_rev_scale);
        free(tmp);
    }
    free(carry);
}

static void destroy_pawn(pawn_t *pawn)
{
    if (pawn->job == CARRY)
        destroy_carry(pawn->carry);
    pawn->carry = NULL;
    free(pawn);
}

static void destroy_spe_pawn(spe_t *spe)
{
    destroy_pawn(spe->pawn);
    spe->pawn = NULL;
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
