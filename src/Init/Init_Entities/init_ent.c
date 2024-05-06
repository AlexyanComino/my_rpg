/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_ent
*/

#include "rpg.h"


my_clock_t *init_my_clock(void)
{
    my_clock_t *myclock = malloc(sizeof(my_clock_t));

    myclock->clock = sfClock_create();
    myclock->time = (sfTime){0};
    myclock->seconds = 0;
    return myclock;
}

anim_t *init_anim(char *texture_path, int width, int height)
{
    anim_t *anim = malloc(sizeof(anim_t));

    anim->texture = sfTexture_createFromFile(texture_path, NULL);
    anim->sprite = sfSprite_create();
    sfSprite_setTexture(anim->sprite, anim->texture, sfTrue);
    anim->rect = (sfIntRect){0, 0, width, height};
    sfSprite_setTextureRect(anim->sprite, anim->rect);
    sfSprite_setOrigin(anim->sprite, (sfVector2f){width / 2, height / 2});
    anim->myclock = init_my_clock();
    return anim;
}

static int tab_len(char **tab)
{
    int i = 0;

    for (; tab[i] != NULL; i++);
    return i;
}

static entity_t *init_entity(char **infos)
{
    if (!strcmp(infos[0], "W"))
        return init_entity_warrior(infos);
    fprintf(stderr, "Error: invalid entity type\n");
    return NULL;
}

entity_t **init_ent(unsigned int *size)
{
    char **tab = file_to_array(".entities.csv");
    char **infos = NULL;
    entity_t **ent = malloc(sizeof(entity_t *) * (tab_len(tab)));

    for (int i = 1; tab[i] != NULL; i++) {
        infos = split_string(tab[i], ";");
        ent[i - 1] = init_entity(infos);
        (*size)++;
        free_array(infos);
    }
    free_array(tab);
    return ent;
}
