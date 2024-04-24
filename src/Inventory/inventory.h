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


#define WARRIOR_WIDTH 192
enum item_type {
    WEAPON,
    ARMOR,
    POTION,
    QUEST,
    KEY,
    OTHER
};

typedef struct slot_s {
    int is_empty;
    int id;
    int type;
    int is_highlighted;
    int is_clicked;
    int is_moved;
    void *item;
    struct slot_s *next;
    sfSprite *highlight;
    sfSprite *sprite;
} slot_t;


typedef struct player_status_s {
    int hp;
    int max_hp;
    int attack;
    int attack_max;
    int defense;
    int defense_max;
    int speed;
    int speed_max;
    int level;
    int xp;
    int max_xp;
    int gold;
    sfText *t_hp;
    sfText *t_attack;
    sfText *t_defense;
    sfText *t_speed;
    sfText *t_level;
    sfText *t_gold;
    sfSprite *s_level;
    sfSprite *s_def;
    sfSprite *s_speed;
    sfSprite *s_attack;
    sfSprite *s_hp;
    sfSprite *s_gold;
    sfSprite *player;
    sfSprite *pp;
    slot_t *stuff;
} player_status_t;

typedef struct inventory_s {
    int gold;
    int size;
    int is_open;
    slot_t *slot;
    sfSprite *sprite;
    player_status_t *player_status;
} inventory_t;

int init_inventory(int size);
int remove_item(int id, slot_t *tmp);
int remove_gold(int gold);
int add_gold(int gold);
int add_item(void *item, int type);
int open_inventory(sfRenderWindow *window);
void highlight_inventory(sfMouseMoveEvent event, slot_t *tmp);
int click_inventory(sfMouseButtonEvent event, slot_t *tmp);
int release_inventory(sfMouseButtonEvent event, slot_t *tmp);
player_status_t *init_player_status(void);
sfSprite *init_sprite_from_file(char *texture);
int add_stuff(void *item, int type);
int draw_stuff(sfRenderWindow *window);
int draw_item(sfRenderWindow *window, slot_t *tmp);

#include "rpg.h"

int manage_evt_inv(sfEvent event, rpg_t *rpg);
int update_inv(rpg_t *rpg);
