/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** destroy_ent
*/

#include "rpg.h"


void destroy_mark(mark_t *mark)
{
    destroy_anim(mark->anim);
    free(mark);
}

void destroy_my_clock(my_clock_t *clock)
{
    if (clock == NULL)
        return;
    if (clock->clock != NULL)
        sfClock_destroy(clock->clock);
    free(clock);
}

void destroy_base(base_t *base)
{
    if (base == NULL)
        return;
    sfRectangleShape_destroy(base->shape);
    for (int i = 0; base->pattern_pos[i].x != -1; i++)
        sfCircleShape_destroy(base->pattern_pos_shapes[i]);
    free(base->pattern_pos);
    free(base->pattern_pos_shapes);
    destroy_my_clock(base->myclock);
    free(base);
}

void destroy_ent(entity_t **ent, unsigned int size)
{
    for (unsigned int i = 0; i < size; i++)
        ent[i]->destroy(ent[i]);
    free(ent);
}
