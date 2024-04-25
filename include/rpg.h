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
#define PLAYER_SPEED 300

// Warrior
#define WARRIOR_WIDTH 192
#define WARRIOR_OFFSET WARRIOR_WIDTH * 5
#define DEAD_WIDTH 128
#define MIN_WARRIOR_LENGTH 90
#define WARRIOR_MAX_DETECTION_RADIUS 600
#define WARRIOR_INTER_RADIUS 450
#define WARRIOR_EXCLAM_RADIUS 300
// Marks
#define EXCLAM_WIDTH 91
#define EXCLAM_HEIGHT 147
#define INTER_WIDTH 1015 / 14
#define INTER_HEIGHT 399 / 3
#define EXCLAM_COOLDOWN 0.5
#define INTER_INTERVAL 3.0
#define INTER_COOLDOWN 1.5
//

// Cooldowns
#define DEAD_COOLDOWN 10.0

#define PLAYER_NAME "Pablodrigo"

#define BASE_COLOR sfColor_fromRGB(146, 255, 250)
#define WARRIOR_HAS_BASE(warrior) (warrior->base != NULL)

#define DAMAGE_COLOR_PLAYER sfWhite
#define DAMAGE_COLOR_BLUE sfColor_fromRGB(102, 220, 255)
#define DAMAGE_COLOR_RED sfColor_fromRGB(255, 88, 65)
#define DAMAGE_COLOR_YELLOW sfColor_fromRGB(255, 215, 66)
#define DAMAGE_COLOR_PURPLE sfColor_fromRGB(183, 133, 255)
#define DAMAGE_COLOR_GREEN sfColor_fromRGB(176, 255, 87)
#define DAMAGE_COLOR_BAM sfWhite
#define DAMAGE_COLOR_CRITICAL sfColor_fromRGB(255, 61, 30)

#define CRIT_WIDTH 215
#define BAM_WIDTH 160
#define BAM_HEIGHT 200

#define TILE_SCALE 2
#define TILE_SIZE 32 * TILE_SCALE

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
    RUN,
    ST_ATT,
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
} anim_death_t;

typedef struct zones_warrior_s {
    sfIntRect hitbox;
    sfRectangleShape *rect_hitbox;
    sfIntRect hitbox_attack;
    sfRectangleShape *rect_hitbox_attack;
    unsigned int radius_max_detection;
    sfCircleShape *circle_max_detection;
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
    unsigned int radius;
} mark_t;

typedef enum faction {
    BLUE_TEAM = 0,
    RED_TEAM,
    PURPLE_TEAM,
    YELLOW_TEAM,
    GOBLIN_TEAM,
} faction_t;

typedef struct base_s {
    sfIntRect rect;
    sfRectangleShape *shape;
    bool come_back;
    sfVector2f *pattern_pos;
    int pattern_pos_index;
    sfCircleShape **pattern_pos_shapes;
    unsigned int max_pos_index;
    float cooldown;
    bool in_cooldown;
    my_clock_t *myclock;
} base_t;

typedef enum damage_text_state {
    NORMAL,
    CRITICAL,
    BAM,
    MISS,
} damage_text_state_t;

typedef struct effect_s {
    sfTexture *texture;
    sfSprite *sprite;
    sfIntRect rect;
    my_clock_t *myclock;
} effect_t;
typedef struct damage_text_s {
    sfText *text;
    sfText *text_shadow;
    sfFont *font;
    float size;
    sfVector2f pos;
    effect_t *effect;
    damage_text_state_t state;
    struct damage_text_s *next;
} damage_text_t;

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
    faction_t faction;
    my_clock_t *clock_cooldown_attack;
    float attack_cooldown;
    base_t *base;
    damage_text_t *damage_texts;
} warrior_t;

typedef struct restricted_s {
    sfTexture *texture;
    sfSprite *sprite;
    sfVector2f danger_pos;
    bool animation;
    bool in_base;
} restricted_t;

typedef struct interface_s {
    restricted_t *restricted;
} interface_t;
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
    float dt;
} win_t;

typedef struct collision_s {
    sfIntRect rect;
    sfVector2f *pos;
    // bool **coll_map;
    sfRectangleShape *shape;
    unsigned int size;
} collision_t;
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
    bool debug;
    menu_t *main_menu;
    menu_t *settings;
    state_t gamestate;
    interface_t *interface;
    collision_t *collision;
} rpg_t;

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
    warrior_t *player;
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

#include "../src/Init/init.h"
#include "../src/Display/display.h"
#include "../src/Event/event.h"
#include "../src/Destroy/destroy.h"
#include "../src/Update/update.h"
#include "../src/Lib/lib.h"
#include "../src/Animation/anim.h"
#include "../src/Menu/menu.h"
#include "../src/Defines/defines.h"
#include "singleton.h"
