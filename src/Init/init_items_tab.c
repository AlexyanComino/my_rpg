/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_items_tab
*/

#include "rpg.h"

static void init_item_values(item_t *item)
{
    item->name = NULL;
    item->rarity = COMMON;
    item->texture_path = NULL;
    item->description = NULL;
    item->damage = 0;
    item->type = OTHER;
    item->defense = 0;
    item->speed = 0;
    item->endurance = 0;
    item->armor_type = 0;
}

static rarity_t get_rarity_item(char *inf)
{
    if (!strcmp(inf, "C"))
        return COMMON;
    if (!strcmp(inf, "U"))
        return UNCOMMON;
    if (!strcmp(inf, "R"))
        return RARE;
    if (!strcmp(inf, "E"))
        return EPIC;
    if (!strcmp(inf, "L"))
        return LEGENDARY;
    fprintf(stderr, "Error: item rarity not found\n");
    return COMMON;
}

static item_t *init_item_weapon(char **infos)
{
    item_t *item = malloc(sizeof(item_t));

    init_item_values(item);
    item->type = WEAPON;
    item->rarity = get_rarity_item(infos[1]);
    item->name = strdup(infos[2]);
    item->texture_path = strdup(infos[3]);
    item->description = strdup(infos[4]);
    item->damage = atoi(infos[5]);
    return item;
}

static item_t *init_item_armor(char **infos)
{
    item_t *item = malloc(sizeof(item_t));

    init_item_values(item);
    item->type = ARMOR;
    item->rarity = get_rarity_item(infos[1]);
    item->name = strdup(infos[2]);
    item->texture_path = strdup(infos[3]);
    item->description = strdup(infos[4]);
    item->defense = atoi(infos[5]);
    item->speed = atoi(infos[6]);
    item->endurance = atoi(infos[7]);
    item->armor_type = atoi(infos[8]);
    return item;
}

static item_t *init_item_potion(char **infos)
{
    item_t *item = malloc(sizeof(item_t));

    init_item_values(item);
    item->type = POTION;
    item->rarity = get_rarity_item(infos[1]);
    item->name = strdup(infos[2]);
    item->texture_path = strdup(infos[3]);
    item->description = strdup(infos[4]);
    return item;
}

static item_t *init_item(char **infos)
{
    if (!strcmp(infos[0], "W"))
        return init_item_weapon(infos);
    if (!strcmp(infos[0], "A"))
        return init_item_armor(infos);
    if (!strcmp(infos[0], "P"))
        return init_item_potion(infos);
    fprintf(stderr, "Error: item type not found\n");
    return NULL;
}

item_t **init_items_tab(unsigned int *size)
{
    char **tab = file_to_array(".items.csv");
    char **infos = NULL;
    item_t **items = malloc(sizeof(item_t *) * (tab_len(tab)) + 1);

    for (int i = 0; tab[i] != NULL; i++) {
        infos = split_string(tab[i], ";");
        items[i] = init_item(infos);
        (*size)++;
        free_array(infos);
    }
    free_array(tab);
    return items;
}
