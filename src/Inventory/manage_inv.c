/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** manage_inv
*/

#include <stdio.h>
#include <stdlib.h>
#include "inventory.h"
#include "rpg.h"

sfSprite *init_sprite_from_file(char *texture)
{
    sfSprite *sprite = sfSprite_create();
    sfTexture *texture2 = sfTexture_createFromFile(texture, NULL);

    sfSprite_setTexture(sprite, texture2, sfTrue);
    return sprite;
}

int highlight_inventory(sfMouseMoveEvent event)
{
    sfFloatRect rect = {0, 0, 0, 0};
    slot_t *tmp = (*inventory())->slot;

    for (; tmp; tmp = tmp->next) {
        rect = sfSprite_getGlobalBounds(tmp->sprite);
        tmp->is_highlighted = (sfFloatRect_contains(&rect, event.x, event.y))
        ? 1 : 0;
        if (tmp->is_clicked == 1 && tmp->is_empty == 0 &&
        tmp->type == WEAPON) {
            sfSprite_setPosition((weapon_t *){tmp->item}->sprite,
            (sfVector2f){event.x - 10, event.y - 10});
            tmp->is_moved = 1;
        }
        if (tmp->is_clicked == 1 && tmp->is_empty == 0 && tmp->type == ARMOR) {
            sfSprite_setPosition((armor_t *){tmp->item}->sprite,
            (sfVector2f){event.x - 10, event.y - 10});
            tmp->is_moved = 1;
        }
    }
    return (0);
}

int click_inventory(sfMouseButtonEvent event)
{
    inventory_t *inv = *inventory();
    sfFloatRect rect = {0, 0, 0, 0};
    slot_t *tmp = inv->slot;

    for (; tmp; tmp = tmp->next) {
        rect = sfSprite_getGlobalBounds(tmp->sprite);
        tmp->is_clicked = (sfFloatRect_contains(&rect, event.x, event.y)) ?
        1 : 0;
    }
    return (0);
}

static int slot_click(slot_t *tmp, inventory_t *inv, sfMouseButtonEvent event)
{
    sfFloatRect rect = {0, 0, 0, 0};

    tmp->is_clicked = 0;
    for (slot_t *tmp2 = inv->slot; tmp2; tmp2 = tmp2->next) {
        rect = sfSprite_getGlobalBounds(tmp2->sprite);
        if (sfFloatRect_contains(&rect, event.x, event.y) &&
        tmp2->is_empty == 1) {
            tmp2->is_empty = 0;
            tmp2->type = tmp->type;
            tmp2->item = tmp->item;
            tmp->is_empty = 1;
            tmp->is_moved = 0;
            tmp->type = OTHER;
            tmp->item = NULL;
            break;
        }
    }
    tmp->is_moved = 0;
    return 0;
}

int release_inventory(sfMouseButtonEvent event)
{
    inventory_t *inv = *inventory();
    slot_t *tmp = inv->slot;

    for (; tmp; tmp = tmp->next) {
        if (tmp->is_clicked == 1)
            slot_click(tmp, inv, event);
    }
    return (0);
}

int manage_evt_inv(sfEvent event, rpg_t *rpg)
{
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyTab) {
        (*inventory())->is_open = !(*inventory())->is_open;
        rpg->gamestate = ((*inventory())->is_open == 1) ? INVENTORY : GAME;
    }
    if (event.type == sfEvtMouseMoved && (*inventory())->is_open)
        highlight_inventory(event.mouseMove);
    if (event.type == sfEvtMouseButtonPressed &&
    event.mouseButton.button == sfMouseLeft && (*inventory())->is_open)
        click_inventory(event.mouseButton);
    if (event.type == sfEvtMouseButtonReleased &&
    event.mouseButton.button == sfMouseLeft && (*inventory())->is_open)
        release_inventory(event.mouseButton);
    return 0;
}
