/*
** EPITECH PROJECT, 2024
** inventory_sys
** File description:
** gold
*/

#include <stdio.h>
#include <stdlib.h>
#include "inventory.h"
#include "item.h"

int add_gold(int gold)
{
    inventory_t *inv = *inventory();
    char *gold_str = malloc(sizeof(char) * 10);

    inv->gold += gold;
    sprintf(gold_str, "%d", inv->gold);
    sfText_setString(inv->player_status->t_gold, gold_str);
    return (0);
}

int remove_gold(int gold)
{
    inventory_t *inv = *inventory();
    char *gold_str = malloc(sizeof(char) * 10);

    inv->gold -= gold;
    sprintf(gold_str, "%d", inv->gold);
    sfText_setString(inv->player_status->t_gold, gold_str);
    return (0);
}
