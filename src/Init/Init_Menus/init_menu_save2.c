/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_menu_save2
*/

#include "rpg.h"

void get_entity_save(save_button_t *new, int type)
{
    sfVector2f pos = sfRectangleShape_getPosition(new->rect_shape);
    char **infos = get_infos_save(type);

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

static char **get_infos2(int type, char **tab, char **infos)
{
    switch (type) {
    case TORCH:
        infos = split_string(tab[2], ";");
        break;
    case TNT:
        infos = split_string(tab[3], ";");
        break;
    }
    return infos;
}

char **get_infos_save(int type)
{
    char **tab = file_to_array(".entities.csv");
    char **infos = NULL;

    switch (type) {
    case WARRIOR:
        infos = split_string(tab[0], ";");
        break;
    case PAWN:
        infos = split_string(tab[1], ";");
        break;
    case ARCHER:
        infos = split_string(tab[4], ";");
        break;
    default:
        infos = get_infos2(type, tab, infos);
    }
    free_array(tab);
    return infos;
}
