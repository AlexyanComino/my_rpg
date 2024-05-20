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

void highlight_inventory(sfMouseMoveEvent event, slot_t *tmp)
{
    sfFloatRect rect = {0, 0, 0, 0};

    for (; tmp; tmp = tmp->next) {
        rect = sfSprite_getGlobalBounds(tmp->sprite);
        tmp->is_highlighted = (sfFloatRect_contains(&rect,
        event.x + (*view_pos()).x - 1920 / 2,
        event.y + (*view_pos()).y - 1080 / 2)) ? 1 : 0;
        if (tmp->is_clicked && tmp->is_empty == 0 && tmp->type == WEAPON) {
            sfSprite_setPosition((weapon_t *){tmp->item}->sprite,
            (sfVector2f){event.x - 15 + (*view_pos()).x - 1920 / 2,
            event.y - 15 + (*view_pos()).y - 1080 / 2});
            tmp->is_moved = 1;
        }
        if (tmp->is_clicked && tmp->is_empty == 0 && tmp->type == ARMOR) {
            sfSprite_setPosition((armor_t *){tmp->item}->sprite,
            (sfVector2f){event.x + (*view_pos()).x - 1920 / 2,
            event.y + (*view_pos()).y - 1080 / 2});
            tmp->is_moved = 1;
        }
    }
}

int click_inventory(sfMouseButtonEvent event, slot_t *tmp)
{
    sfFloatRect rect = {0, 0, 0, 0};

    for (; tmp; tmp = tmp->next) {
        rect = sfSprite_getGlobalBounds(tmp->sprite);
        tmp->is_clicked = (sfFloatRect_contains(&rect,
        event.x + (*view_pos()).x - 1920 / 2,
        event.y + (*view_pos()).y - 1080 / 2))
        ? 1 : 0;
    }
    return (0);
}

static void replace_slot_item(slot_t *tmp, slot_t *tmp2)
{
    tmp2->type = tmp->type;
    tmp2->item = tmp->item;
    tmp->name = tmp2->name;
    tmp2->name = NULL;
}

static void slot_click(slot_t *tmp, slot_t *tmp2, sfMouseButtonEvent event)
{
    sfFloatRect rect = {0, 0, 0, 0};

    for (; tmp2; tmp2 = tmp2->next) {
        rect = sfSprite_getGlobalBounds(tmp2->sprite);
        if (sfFloatRect_contains(&rect, event.x + (*view_pos()).x - 1920 / 2,
        event.y + (*view_pos()).y - 1080 / 2) && tmp2->is_empty == 1 &&
        (tmp2->access == ALL || tmp->type == tmp2->access)) {
            tmp2->is_empty = 0;
            tmp2->is_active = 0;
            replace_slot_item(tmp, tmp2);
            unapply_stuff(tmp);
            tmp->is_empty = 1;
            tmp->is_moved = 0;
            tmp->is_active = 0;
            tmp->type = OTHER;
            tmp->item = NULL;
            break;
        }
    }
}

int release_inventory(sfMouseButtonEvent event, slot_t *tmp)
{
    for (; tmp; tmp = tmp->next) {
        if (tmp->is_clicked == 1) {
            tmp->is_clicked = 0;
            slot_click(tmp, (*inventory())->slot, event);
            slot_click(tmp, (*inventory())->player_status->stuff, event);
            tmp->is_moved = 0;
        }
    }
    return (0);
}

static void inv_is_open(rpg_t *rpg)
{
    (*inventory())->is_open = !(*inventory())->is_open;
    rpg->gamestate = ((*inventory())->is_open == 1) ? INVENTORY : GAME;
    scroll_quest(&(*inventory())->scroll, &(*inventory())->scroll_max);
}

int manage_evt_inv(sfEvent event, rpg_t *rpg)
{
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyTab)
        inv_is_open(rpg);
    if (event.type == sfEvtMouseMoved && (*inventory())->is_open) {
        highlight_inventory(event.mouseMove, (*inventory())->slot);
        highlight_inventory(event.mouseMove,
        (*inventory())->player_status->stuff);
    }
    if (event.type == sfEvtMouseButtonPressed &&
    event.mouseButton.button == sfMouseLeft && (*inventory())->is_open) {
        click_inventory(event.mouseButton, (*inventory())->slot);
        click_inventory(event.mouseButton,
        (*inventory())->player_status->stuff);
    }
    if (event.type == sfEvtMouseButtonReleased &&
    event.mouseButton.button == sfMouseLeft && (*inventory())->is_open) {
        release_inventory(event.mouseButton, (*inventory())->slot);
        release_inventory(event.mouseButton,
        (*inventory())->player_status->stuff);
    }
    return 0;
}
