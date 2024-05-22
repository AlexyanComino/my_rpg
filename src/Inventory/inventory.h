/*
** EPITECH PROJECT, 2024
** inventory_sys
** File description:
** inventory
*/

#pragma once
#include "item.h"
#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include "rpg.h"


#define WARRIOR_WIDTH 192

int remove_item(int id, slot_t *tmp);
int remove_gold(int gold);
int add_gold(int gold);
int add_item(void *item, int type, char *name);
int open_inventory(rpg_t *rpg);
void highlight_inventory(rpg_t *rpg, slot_t *tmp);
int click_inventory(rpg_t *rpg, slot_t *tmp);
int release_inventory(rpg_t *rpg, slot_t *tmp);
player_status_t *init_player_status(void);
sfSprite *init_sprite_from_file(char *texture);
int add_stuff(void *item, int type);
int add_stuff_from_type(rpg_t *rpg, char *name, int type);
int draw_stuff(sfRenderWindow *window);
int draw_item(sfRenderWindow *window, slot_t *tmp);

int manage_evt_inv(sfEvent event, rpg_t *rpg);
int display_inv(rpg_t *rpg);
int apply_stuff(rpg_t *rpg);
int unapply_stuff(slot_t *tmp);
