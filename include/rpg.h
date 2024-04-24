/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** my
*/

#pragma once

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <string.h>


#define WIDTH 1920
#define HEIGHT 1080
#define WARRIOR_WIDTH 192
#define DEAD_WIDTH 128
#define WARRIOR_OFFSET WARRIOR_WIDTH * 5
#define PLAYER_SPEED 300

// Marks
#define EXCLAM_WIDTH 91
#define EXCLAM_HEIGHT 147
#define INTER_WIDTH 1015 / 14
#define INTER_HEIGHT 399 / 3

//
#define IS_ALIVE(warrior) (warrior->state != DEAD && warrior->state != RIEN)

// Cooldowns
#define DEAD_COOLDOWN 10.0

#define PLAYER_NAME "Pablorigo"

typedef enum warrior_color {
    BLUE = 0,
    PURPLE,
    RED,
    YELLOW,
} color_warrior_t;

typedef enum warrior_x {
    RIGHT = 0,
    LEFT,
} x_warrior_t;

typedef enum warrior_y {
    NONE = 0,
    DOWN,
    UP,
} y_warrior_t;

typedef enum warrior_state {
    IDLE = 0,
    WALK,
    ATTACK,
    DEAD,
    RIEN,
} state_warrior_t;

typedef struct attributes_s {
    unsigned int max_health;
    int health;
    unsigned int attack;
    unsigned int defense;
    unsigned int speed;
} attributes_t;

typedef struct my_clock_s {
    sfClock *clock;
    sfTime time;
    float seconds;
} my_clock_t;

typedef struct anim_death_s {
    sfTexture *texture_dead;
    sfSprite *sprite_dead;
    sfIntRect rect_dead;
    my_clock_t *clock_dead;
    int number_dead;
    sfVector2f dead_pos;
} anim_death_t;

typedef struct zones_warrior_s {
    sfIntRect hitbox;
    sfRectangleShape *rect_hitbox;
    sfIntRect hitbox_attack;
    sfRectangleShape *rect_hitbox_attack;
    unsigned int radius_reset;
    sfCircleShape *circle_reset;
    sfVector2f circle_reset_pos;
} zones_warrior_t;

typedef struct mark_s {
    sfTexture *texture;
    sfSprite *sprite;
    sfVector2f pos;
    my_clock_t *myclock;
    sfIntRect rect;
    int is_display;
    bool is_detecting;
    sfCircleShape *circle;
    sfVector2f circle_pos;
    unsigned int radius;
} mark_t;

typedef struct warrior_s {
    char *name;
    sfTexture *texture;
    sfSprite *sprite;
    my_clock_t *myclock;
    sfIntRect rect;
    sfVector2f pos;
    color_warrior_t color;
    x_warrior_t x;
    y_warrior_t y;
    state_warrior_t state;
    int line_attack;
    int max_line_attack;
    zones_warrior_t *zones;
    attributes_t *attributes;
    anim_death_t *death;
    mark_t *exclam;
    mark_t *inter;
} warrior_t;

typedef struct lwarrior_s {
    warrior_t *warrior;
    struct lwarrior_s *next;
} lwarrior_t;

typedef enum {
    MAIN_MENU,
    GAME,
    PAUSE,
    SETTINGS,
    INVENTORY,
    END
} state_t;

typedef enum button_state {
    HOVERED,
    CLICKED,
    RELEASED,
    NOTHING
} button_state_t;

typedef struct button_s {
    char *name;
    sfSprite *sprite;
    sfTexture *texture;
    sfText *text;
    sfFont *font;
    sfIntRect rect;
    button_state_t state;
    void (*action)(void *rpg);
    struct button_s *next;
} button_t;

typedef struct menu_s {
    sfSprite *background;
    sfTexture *background_texture;
    button_t *buttons;
    sfIntRect rect;
    sfFont *font;
} menu_t;

typedef struct win_s {
    sfRenderWindow *window;
    sfView *view;
    unsigned int width;
    unsigned int height;
    unsigned int framerate;
    sfClock *clock;
} win_t;

typedef struct map_s {
    sfTexture *ground_texture;
    sfSprite *ground_sprite;
    sfTexture *high_texture;
    sfSprite *high_sprite;
} map_t;

typedef struct rpg_s {
    win_t *win;
    map_t *map;
    sfEvent event;
    lwarrior_t *lwarrior;
    warrior_t *player;
    bool debug;
    menu_t *main_menu;
    menu_t *settings;
    state_t gamestate;
} rpg_t;

#include "../src/Init/init.h"
#include "../src/Display/display.h"
#include "../src/Event/event.h"
#include "../src/Destroy/destroy.h"
#include "../src/Update/update.h"
#include "../src/Lib/lib.h"
#include "../src/Animation/anim.h"
#include "../src/Menu/menu.h"
#include "singleton.h"
