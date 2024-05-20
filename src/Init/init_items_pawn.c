/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_items
*/

#include "rpg.h"

static int get_quantity(item_pawn_type_t item_type)
{
    if (item_type == WOOD)
        return 3;
    if (item_type == MEAT)
        return 1;
    if (item_type == GOLD)
        return 2;
    return 0;
}

static char *get_item_texture_path(item_pawn_type_t item_type)
{
    char *texture_paths[3] = {
        "assets/item/W_Idle_(NoShadow).png",
        "assets/item/M_Idle_(NoShadow).png",
        "assets/item/G_Idle_(NoShadow).png"
    };
    int item_index = 0;

    if (item_type == WOOD)
        item_index = 0;
    if (item_type == MEAT)
        item_index = 1;
    if (item_type == GOLD)
        item_index = 2;
    return strdup(texture_paths[item_index]);
}

static sfVector2f *get_items_pos(item_pawn_t *item)
{
    sfVector2f *pos = malloc(sizeof(sfVector2f) * item->quantity);
    int quantity = item->quantity;

    if (quantity == 1) {
        pos[0] = (sfVector2f){-3, -50};
        return pos;
    }
    if (quantity == 2) {
        pos[0] = (sfVector2f){-5, -53};
        pos[1] = (sfVector2f){15, -53};
        return pos;
    }
    if (quantity == 3) {
        pos[0] = (sfVector2f){-7, -53};
        pos[1] = (sfVector2f){7, -53};
        pos[2] = (sfVector2f){0, -66};
        return pos;
    }
    return NULL;
}

static int *get_index_rev_scale(item_pawn_t *item)
{
    int *index_rev_scale = malloc(sizeof(int) * item->quantity);
    item_pawn_type_t item_type = item->type;

    if (item_type == WOOD) {
        index_rev_scale[0] = 0;
        index_rev_scale[1] = 0;
        index_rev_scale[2] = 0;
    }
    if (item_type == GOLD) {
        index_rev_scale[0] = 0;
        index_rev_scale[1] = 1;
    }
    if (item_type == MEAT)
        index_rev_scale[0] = 0;
    return index_rev_scale;
}

item_pawn_t *init_item_pawn(item_pawn_type_t item_type)
{
    item_pawn_t *item = malloc(sizeof(item_pawn_t));
    char *texture_path = get_item_texture_path(item_type);

    item->type = item_type;
    item->quantity = get_quantity(item_type);
    item->texture = sfTexture_createFromFile(texture_path, NULL);
    item->sprite = sfSprite_create();
    sfSprite_setTexture(item->sprite, item->texture, sfTrue);
    sfSprite_setOrigin(item->sprite, (sfVector2f){ITEM_SIZE / 2,
        ITEM_SIZE / 2});
    item->pos = get_items_pos(item);
    item->index_rev_scale = get_index_rev_scale(item);
    return item;
}
