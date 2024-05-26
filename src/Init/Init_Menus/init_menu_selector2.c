/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_menu_selector2
*/

#include "rpg.h"

static char **get_infos(char *txt)
{
    char **tab = file_to_array(".entities.csv");
    char **infos = NULL;

    if (strcmp(txt, "WARRIOR") == 0)
        infos = split_string(tab[0], ";");
    if (strcmp(txt, "PAWN") == 0)
        infos = split_string(tab[1], ";");
    if (strcmp(txt, "ARCHER") == 0)
        infos = split_string(tab[4], ";");
    if (strcmp(txt, "TORCH") == 0)
        infos = split_string(tab[2], ";");
    if (strcmp(txt, "TNT") == 0)
        infos = split_string(tab[3], ";");
    free_array(tab);
    return infos;
}

void get_entity(select_button_t *new)
{
    sfVector2f pos = sfRectangleShape_getPosition(new->rect_shape);
    char **infos = get_infos(new->name);

    if (infos != NULL) {
        new->entity = init_entity(infos);
        sfSprite_setScale(new->entity->common->anim->sprite, (sfVector2f){3,
            3});
        sfSprite_setPosition(new->entity->common->anim->sprite,
            (sfVector2f){pos.x, pos.y + 250});
        return free_array(infos);
    }
    new->entity = NULL;
}

void get_attributes_select(char *txt, select_button_t *new)
{
    char **infos = get_infos(txt);

    new->attributes = malloc(sizeof(attributes_t));
    if (!strcmp(txt, "Retour")) {
        free(new->attributes);
        new->attributes = NULL;
    }
    if (infos != NULL) {
        new->attributes->health = atoi(infos[10]);
        new->attributes->attack = atoi(infos[11]);
        new->attributes->defense = atoi(infos[12]);
        new->attributes->speed = atoi(infos[13]);
        return free_array(infos);
    }
}
