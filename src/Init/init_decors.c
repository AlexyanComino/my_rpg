/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_decors
*/

#include "rpg.h"

static void init_decor_anim2(decor_anim_t *decor)
{
    decor->shape = sfRectangleShape_create();
    sfRectangleShape_setSize(decor->shape, (sfVector2f){decor->width *
        TILE_SCALE, decor->height * TILE_SCALE});
    sfRectangleShape_setFillColor(decor->shape, sfTransparent);
    sfRectangleShape_setOutlineThickness(decor->shape, 1);
    sfRectangleShape_setOutlineColor(decor->shape, sfMagenta);
    sfRectangleShape_setPosition(decor->shape, decor->pos);
}

static decor_anim_t *init_decor_anim(char **infos)
{
    decor_anim_t *decor = malloc(sizeof(decor_anim_t));
    sfVector2f scale = {TILE_SCALE * atoi(infos[9]),
        TILE_SCALE * atoi(infos[9])};

    decor->type = (!strcmp(infos[0], "G")) ? GROUND : HIGH;
    decor->anim = init_anim(infos[1], atoi(infos[2]), atoi(infos[3]));
    decor->width = atoi(infos[2]);
    decor->height = atoi(infos[3]);
    decor->speed = atof(infos[4]);
    decor->nb_cols = atoi(infos[5]) - 1;
    decor->nb_rows = atoi(infos[6]) - 1;
    decor->pos = (sfVector2f){atoi(infos[7]), atoi(infos[8])};
    sfSprite_setPosition(decor->anim->sprite, decor->pos);
    sfSprite_setScale(decor->anim->sprite, scale);
    decor->rect = (sfIntRect){decor->pos.x, decor->pos.y,
        decor->width * TILE_SCALE, decor->height * TILE_SCALE};
    init_decor_anim2(decor);
    return decor;
}

decor_anim_t **init_decors(unsigned int *size)
{
    char **tab = file_to_array(".decors.csv");
    char **infos = NULL;
    decor_anim_t **decors = malloc(sizeof(decor_anim_t *) *
        (tab_len(tab)) + 1);

    for (int i = 0; tab[i] != NULL; i++) {
        infos = split_string(tab[i], ";");
        decors[i] = init_decor_anim(infos);
        (*size)++;
        free_array(infos);
    }
    free_array(tab);
    return decors;
}
