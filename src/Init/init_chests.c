/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_chests
*/

#include "rpg.h"

static enum item_type get_item_type(char *type)
{
    if (!strcmp(type, "WEAPON"))
        return WEAPON;
    if (!strcmp(type, "ARMOR"))
        return ARMOR;
    if (!strcmp(type, "POTION"))
        return POTION;
    return OTHER;
}

static char *get_chest_texture(char *name)
{
    if (!strcmp(name, "H"))
        return "assets/item/chest_horns.png";
    return "assets/item/chest.png";
}

static void init_chest2(chest_t *chest, char **infos)
{
    chest->item_name = strdup(infos[3]);
    chest->item_type = get_item_type(infos[4]);
    chest->is_interacted = false;
    chest->state = CLOSED;
    chest->is_recieved = false;
}

static chest_t *init_chest(char **infos)
{
    chest_t *chest = malloc(sizeof(chest_t));
    char *texture_path = get_chest_texture(infos[0]);

    chest->pos = (sfVector2f){atoi(infos[1]), atoi(infos[2])};
    chest->anim = init_anim(texture_path, CHEST_WIDTH, CHEST_WIDTH);
    sfSprite_setPosition(chest->anim->sprite, chest->pos);
    chest->rect = (sfIntRect){chest->pos.x - CHEST_WIDTH / 6,
        chest->pos.y - CHEST_WIDTH / 6, CHEST_WIDTH / 3, CHEST_WIDTH / 3};
    chest->shape = sfRectangleShape_create();
    sfRectangleShape_setSize(chest->shape, (sfVector2f){CHEST_WIDTH / 3,
        CHEST_WIDTH / 3});
    sfRectangleShape_setFillColor(chest->shape, sfTransparent);
    sfRectangleShape_setOutlineThickness(chest->shape, 1);
    sfRectangleShape_setOutlineColor(chest->shape, sfMagenta);
    sfRectangleShape_setOrigin(chest->shape, (sfVector2f){CHEST_WIDTH / 6,
        CHEST_WIDTH / 6});
    sfRectangleShape_setPosition(chest->shape, chest->pos);
    init_chest2(chest, infos);
    return chest;
}

chest_t **init_chests(unsigned int *size)
{
    char **tab = file_to_array(".chests.csv");
    char **infos = NULL;
    chest_t **chests = malloc(sizeof(chest_t *) * (tab_len(tab)) + 1);

    for (int i = 0; tab[i] != NULL; i++) {
        infos = split_string(tab[i], ";");
        chests[i] = init_chest(infos);
        (*size)++;
        free_array(infos);
    }
    free_array(tab);
    return chests;
}
