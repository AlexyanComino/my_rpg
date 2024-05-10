/*
** EPITECH PROJECT, 2024
** inventory_sys
** File description:
** inventory
*/

#include <stdio.h>
#include <stdlib.h>
#include "inventory.h"
#include "item.h"
#include "rpg.h"

int init_inventory(int size)
{
    inventory_t *inv = malloc(sizeof(inventory_t));

    inv->is_open = 0;
    inv->gold = 0;
    inv->size = size;
    inv->slot = NULL;
    inv->quest = NULL;
    inv->scroll = 0;
    inv->scroll_max = 0;
    inv->sprite = init_sprite_from_file("assets/inventory/1.png");
    inv->player_status = init_player_status();
    sfSprite_setScale(inv->sprite, (sfVector2f){2, 2});
    sfSprite_setPosition(inv->sprite, (sfVector2f){0, 80});
    *inventory() = inv;
    for (int i = 0; i < 4; i++)
        add_stuff(create_armor(10, 10, 1, 10), ARMOR);
    for (int i = 0; i <= 4; i++)
        remove_item(i, (*inventory())->player_status->stuff);
    return (0);
}

static slot_t *setup_slot(slot_t *slot, sfVector2f pos, int type, void *item)
{
    slot->is_empty = 0;
    slot->is_highlighted = 0;
    slot->is_clicked = 0;
    slot->is_moved = 0;
    slot->is_active = 0;
    slot->type = type;
    slot->item = item;
    slot->sprite = init_sprite_from_file("assets/inventory/6.png");
    slot->highlight = init_sprite_from_file("assets/inventory/5.png");
    sfSprite_setPosition(slot->sprite, pos);
    sfSprite_setScale(slot->sprite, (sfVector2f){2, 2});
    sfSprite_setPosition(slot->highlight,
    (sfVector2f){pos.x - 15, pos.y - 17});
    sfSprite_setScale(slot->highlight, (sfVector2f){6, 6});
    return slot;
}

static int manage_slot(slot_t *tmp, void *item, int type, int *id)
{
    slot_t *slot = malloc(sizeof(slot_t));
    static sfVector2f pos = {180, 500};
    int start = 180;

    tmp = (*inventory())->slot;
    slot->id = *id;
    slot = setup_slot(slot, pos, type, item);
    slot->access = ALL;
    slot->next = NULL;
    pos.x = (*id % 5 == 0) ? start : pos.x + 100;
    pos.y += (*id % 5 == 0) ? 100 : 0;
    *id += 1;
    if ((*inventory())->slot == NULL) {
        (*inventory())->slot = slot;
        return (1);
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = slot;
    return (1);
}

int add_item(void *item, int type)
{
    slot_t *tmp = (*inventory())->slot;
    int empty_id = -1;
    static int id = 1;

    for (; tmp; tmp = tmp->next) {
        if (tmp->is_empty == 1) {
            empty_id = tmp->id;
            break;
        }
    }
    if (empty_id == -1 && id > (*inventory())->size)
        return (0);
    if (empty_id == -1)
        if (manage_slot(tmp, item, type, &id) == 1)
            return (0);
    tmp->is_empty = 0;
    tmp->type = type;
    tmp->item = item;
    return (0);
}

int remove_item(int id, slot_t *tmp)
{
    while (tmp != NULL) {
        if (tmp->id == id) {
            tmp->is_empty = 1;
            tmp->item = NULL;
            tmp->type = OTHER;
            return (0);
        }
        tmp = tmp->next;
    }
    return (0);
}

static int draw_inventory_ui(sfRenderWindow *window, inventory_t *inv)
{
    sfRenderWindow_drawSprite(window, inv->sprite, NULL);
    sfRenderWindow_drawSprite(window, inv->player_status->pp, NULL);
    sfRenderWindow_drawSprite(window, inv->player_status->s_gold, NULL);
    sfRenderWindow_drawSprite(window, inv->player_status->s_hp, NULL);
    sfRenderWindow_drawSprite(window, inv->player_status->s_attack, NULL);
    sfRenderWindow_drawSprite(window, inv->player_status->s_def, NULL);
    sfRenderWindow_drawSprite(window, inv->player_status->s_speed, NULL);
    sfRenderWindow_drawText(window, inv->player_status->t_gold, NULL);
    sfRenderWindow_drawText(window, inv->player_status->t_hp, NULL);
    sfRenderWindow_drawText(window, inv->player_status->t_attack, NULL);
    sfRenderWindow_drawText(window, inv->player_status->t_defense, NULL);
    sfRenderWindow_drawText(window, inv->player_status->t_speed, NULL);
    sfRenderWindow_drawText(window, inv->player_status->t_level, NULL);
    return (0);
}

int draw_item(sfRenderWindow *window, slot_t *tmp)
{
    if (tmp->is_empty == 0 && tmp->type == WEAPON && tmp->is_moved == 0) {
        sfRenderWindow_drawSprite(window,
        (weapon_t *){tmp->item}->sprite, NULL);
        sfSprite_setPosition((weapon_t *){tmp->item}->sprite, (sfVector2f)
        {sfSprite_getPosition(tmp->sprite).x + 8,
        sfSprite_getPosition(tmp->sprite).y + 9});
    }
    if (tmp->is_empty == 0 && tmp->type == ARMOR && tmp->is_moved == 0) {
        sfRenderWindow_drawSprite(window,
        (armor_t *){tmp->item}->sprite, NULL);
        sfSprite_setPosition((armor_t *){tmp->item}->sprite, (sfVector2f)
        {sfSprite_getPosition(tmp->sprite).x + 8,
        sfSprite_getPosition(tmp->sprite).y + 9});
    }
    if (tmp->is_highlighted == 1)
        sfRenderWindow_drawSprite(window, tmp->highlight, NULL);
    return 0;
}

static void update_cursor_inv(sfRenderWindow *window)
{
    for (slot_t *tmp = (*inventory())->player_status->stuff; tmp;
    tmp = tmp->next) {
        if (tmp->is_empty == 0 && tmp->type == WEAPON && tmp->is_moved == 1) {
            sfRenderWindow_drawSprite(window,
            (weapon_t *){tmp->item}->sprite, NULL);
        }
        if (tmp->is_empty == 0 && tmp->type == ARMOR && tmp->is_moved == 1) {
            sfRenderWindow_drawSprite(window,
            (armor_t *){tmp->item}->sprite, NULL);
        }
    }
}

static int draw_slot(sfRenderWindow *window)
{
    for (slot_t *tmp = (*inventory())->slot; tmp; tmp = tmp->next) {
        sfRenderWindow_drawSprite(window, tmp->sprite, NULL);
        draw_item(window, tmp);
    }
    for (slot_t *tmp = (*inventory())->slot; tmp; tmp = tmp->next) {
        if (tmp->is_empty == 0 && tmp->type == WEAPON && tmp->is_moved == 1) {
            sfRenderWindow_drawSprite(window,
            (weapon_t *){tmp->item}->sprite, NULL);
        }
        if (tmp->is_empty == 0 && tmp->type == ARMOR && tmp->is_moved == 1) {
            sfRenderWindow_drawSprite(window,
            (armor_t *){tmp->item}->sprite, NULL);
        }
    }
    update_cursor_inv(window);
    return (0);
}

int open_inventory(rpg_t *rpg)
{
    if ((*inventory())->is_open == 1) {
        draw_inventory_ui(rpg->win->window, *inventory());
        draw_stuff(rpg->win->window);
        draw_slot(rpg->win->window);
        display_warrior(rpg, (*inventory())->player_status->player);
    }
    if ((*inventory())->is_open == 0) {
        for (slot_t *tmp = (*inventory())->slot; tmp; tmp = tmp->next)
            tmp->is_moved = (tmp->is_moved == 1) ? 0 : tmp->is_moved;
    }
    return (0);
}
