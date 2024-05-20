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
    slot->access = (slot->id == 1) ? WEAPON : slot->access;
    slot->access = (slot->id == 2) ? ARMOR : slot->access;
    slot->access = (slot->id == 3) ? POTION : slot->access;
    slot->access = (slot->id == 4) ? OTHER : slot->access;
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

    tmp = (*inventory())->player_status->stuff;
    slot->id = *id;
    slot = setup_stuff(slot, pos, type, item);
    slot->next = NULL;
    pos.x += 75;
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

static int update_stat_print(slot_t *tmp)
{
    char *str = malloc(sizeof(char) * 10);

    if (tmp->is_empty == 0 && tmp->type == WEAPON && tmp->is_active == 0) {
        (*inventory())->player_status->attack +=
        (weapon_t *){tmp->item}->damage;
        sprintf(str, "%d", (*inventory())->player_status->attack);
        sfText_setString((*inventory())->player_status->t_attack, str);
        tmp->is_active = 1;
    }
    if (tmp->is_empty == 0 && tmp->type == ARMOR && tmp->is_active == 0) {
        (*inventory())->player_status->defense +=
        (armor_t *){tmp->item}->defense;
        sprintf(str, "%d", (*inventory())->player_status->defense);
        sfText_setString((*inventory())->player_status->t_defense, str);
        tmp->is_active = 1;
    }
    free(str);
    return 0;
}

int apply_stuff(rpg_t *rpg)
{
    slot_t *tmp = (*inventory())->player_status->stuff;
    attributes_t *attribute = get_player(rpg)->common->attributes;

    for (; tmp; tmp = tmp->next)
        update_stat_print(tmp);
    attribute->attack = (*inventory())->player_status->attack;
    attribute->defense = (*inventory())->player_status->defense;
    return 0;
}

int unapply_stuff(slot_t *tmp)
{
    char *str = malloc(sizeof(char) * 10);

    if (tmp->is_empty == 0 && tmp->type == WEAPON && tmp->is_active == 1) {
        (*inventory())->player_status->attack -=
        (weapon_t *){tmp->item}->damage;
        sprintf(str, "%d", (*inventory())->player_status->attack);
        sfText_setString((*inventory())->player_status->t_attack, str);
        tmp->is_active = 0;
    }
    if (tmp->is_empty == 0 && tmp->type == ARMOR && tmp->is_active == 1) {
        (*inventory())->player_status->defense -=
        (armor_t *){tmp->item}->defense;
        sprintf(str, "%d", (*inventory())->player_status->defense);
        sfText_setString((*inventory())->player_status->t_defense, str);
        tmp->is_active = 0;
    }
    free(str);
    return 0;
}
