/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** stuff
*/

#include <stdio.h>
#include <stdlib.h>
#include "inventory.h"
#include "item.h"
#include "rpg.h"

static slot_t *setup_stuff(slot_t *slot, sfVector2f pos, int type, void *item)
{
    slot->is_empty = 0;
    slot->is_highlighted = 0;
    slot->is_clicked = 0;
    slot->is_moved = 0;
    slot->type = type;
    slot->item = item;
    slot->sprite = init_sprite_from_file("assets/inventory/item_hold.png");
    slot->highlight = init_sprite_from_file("assets/inventory/5.png");
    sfSprite_setPosition(slot->sprite, pos);
    sfSprite_setScale(slot->sprite, (sfVector2f){2, 2});
    sfSprite_setPosition(slot->highlight,
    (sfVector2f){pos.x - 15, pos.y - 17});
    sfSprite_setScale(slot->highlight, (sfVector2f){6, 6});
    return slot;
}

static int manage_stuff(slot_t *tmp, void *item, int type, int *id)
{
    slot_t *slot = malloc(sizeof(slot_t));
    static sfVector2f pos = {380, 370};
    int start = 180;

    tmp = (*inventory())->player_status->stuff;
    slot->id = *id;
    slot = setup_stuff(slot, pos, type, item);
    slot->next = NULL;
    pos.x = (*id % 5 == 0) ? start : pos.x + 75;
    pos.y += (*id % 5 == 0) ? 100 : 0;
    *id += 1;
    if ((*inventory())->player_status->stuff == NULL) {
        (*inventory())->player_status->stuff = slot;
        return (1);
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = slot;
    return (1);
}

int add_stuff(void *item, int type)
{
    slot_t *tmp = (*inventory())->player_status->stuff;
    int empty_id = -1;
    static int id = 1;

    for (; tmp; tmp = tmp->next) {
        if (tmp->is_empty == 1) {
            empty_id = tmp->id;
            break;
        }
    }
    if (empty_id == -1 && id > 4)
        return (0);
    if (empty_id == -1)
        if (manage_stuff(tmp, item, type, &id) == 1)
            return (0);
    tmp->is_empty = 0;
    tmp->type = type;
    tmp->item = item;
    return (0);
}

int draw_stuff(sfRenderWindow *window)
{
    slot_t *tmp = (*inventory())->player_status->stuff;

    for (; tmp; tmp = tmp->next) {
        sfRenderWindow_drawSprite(window, tmp->sprite, NULL);
        draw_item(window, tmp);
        if (tmp->is_empty == 0 && tmp->type == WEAPON)
            sfRenderWindow_drawSprite(window,
            (weapon_t *){tmp->item}->sprite, NULL);
        if (tmp->is_empty == 0 && tmp->type == ARMOR)
            sfRenderWindow_drawSprite(window,
            (armor_t *){tmp->item}->sprite, NULL);
        if (tmp->is_highlighted == 1)
            sfRenderWindow_drawSprite(window, tmp->highlight, NULL);
    }
    return 0;
}
