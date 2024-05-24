/*
** EPITECH PROJECT, 2024
** inventory_sys
** File description:
** draw_desc
*/

#include <stdio.h>
#include <stdlib.h>
#include "inventory.h"
#include "item.h"
#include "rpg.h"

static void draw_desc_logo_armor
(inventory_t *inv, sfVector2f pos, char *str, slot_t *tmp)
{
    sfSprite_setPosition(inv->player_status->s_def,
    (sfVector2f){pos.x + 100, pos.y + 140});
    sprintf(str, "%d", (armor_t *){tmp->item}->defense);
    sfText_setString(inv->desc, str);
}

static void item_desc_inv
(slot_t *tmp, sfRenderWindow *window, sfVector2f pos, char *str)
{
    inventory_t *inv = (*inventory());

    sfText_setPosition(inv->desc, (sfVector2f){pos.x + 155, pos.y + 140});
    if (tmp->type == WEAPON) {
        sfSprite_setPosition(inv->player_status->s_attack,
        (sfVector2f){pos.x + 100, pos.y + 140});
        sprintf(str, "%d", (weapon_t *){tmp->item}->damage);
        sfText_setString(inv->desc, str);
        sfRenderWindow_drawText(window, inv->desc, NULL);
        sfText_setString(inv->desc, (weapon_t *){tmp->item}->name);
        sfRenderWindow_drawSprite(window, inv->player_status->s_attack, NULL);
    }
    if (tmp->type == ARMOR) {
        draw_desc_logo_armor(inv, pos, str, tmp);
        sfRenderWindow_drawText(window, inv->desc, NULL);
        sfText_setString(inv->desc, (armor_t *){tmp->item}->name);
        sfRenderWindow_drawSprite(window, inv->player_status->s_def, NULL);
    }
}

static sfVector2f draw_item_desc(sfRenderWindow *window, sfVector2f pos,
    slot_t *tmp, char *str)
{
    if (tmp->is_highlighted && tmp->is_empty == 0) {
        pos = sfSprite_getPosition((*inventory())->desc_sprite);
        sfRenderWindow_drawSprite(window, (*inventory())->desc_sprite, NULL);
        item_desc_inv(tmp, window, pos, str);
        sfText_setOrigin((*inventory())->desc, (sfVector2f)
        {sfText_getGlobalBounds((*inventory())->desc).width / 2, 0});
        sfText_setPosition((*inventory())->desc, (sfVector2f)
        {pos.x + 145, pos.y + 80});
        sfRenderWindow_drawText(window, (*inventory())->desc, NULL);
        sfText_setOrigin((*inventory())->desc, (sfVector2f){0, 0});
    }
    return pos;
}

void draw_desc(sfRenderWindow *window)
{
    sfVector2f pos = {180, 500};
    char *str = malloc(sizeof(char) * 10);

    for (slot_t *tmp = (*inventory())->slot; tmp; tmp = tmp->next) {
        pos = draw_item_desc(window, pos, tmp, str);
    }
    for (slot_t *tmp = (*inventory())->player_status->stuff; tmp;
    tmp = tmp->next) {
        pos = draw_item_desc(window, pos, tmp, str);
    }
}
