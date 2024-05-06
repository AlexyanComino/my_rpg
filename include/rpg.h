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

#define BUTTON_WIDTH 640
#define BUTTON_HEIGHT 338

#define WARRIOR_WIDTH 192
#define DEAD_WIDTH 128
#define WARRIOR_OFFSET WARRIOR_WIDTH * 5
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

#define DAMAGE_COLOR_PLAYER sfWhite
#define DAMAGE_COLOR_BLUE sfColor_fromRGB(28, 86, 255)
#define DAMAGE_COLOR_RED sfColor_fromRGB(255, 88, 65)
#define DAMAGE_COLOR_YELLOW sfColor_fromRGB(255, 215, 66)
#define DAMAGE_COLOR_PURPLE sfColor_fromRGB(183, 133, 255)
#define DAMAGE_COLOR_GREEN sfColor_fromRGB(176, 255, 87)
#define DAMAGE_COLOR_BAM sfWhite
#define DAMAGE_COLOR_CRITICAL sfColor_fromRGB(255, 61, 30)

#define CRIT_WIDTH 215
#define BAM_WIDTH 160

#define TILE_SCALE 2.1
#define TILE_SIZE 32 * TILE_SCALE

typedef enum color_entity_s {
    BLUE = 0,
    PURPLE,
    RED,
    YELLOW,
} color_entity_t;

typedef enum side_x_s {
    RIGHT = 0,
    LEFT,
} side_x_t;

typedef enum side_y_s {
    NONE = 0,
    DOWN,
    UP,
} side_y_t;

typedef enum state_entity_s {
    IDLE = 0,
    WALK,
    RUN,
    ST_ATT,
    ATTACK,
    DEAD,
    RIEN,
} state_entity_t;

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

typedef struct anim_s {
    sfTexture *texture;
    sfSprite *sprite;
    sfIntRect rect;
    my_clock_t *myclock;
} anim_t;

typedef struct death_s {
    anim_t *anim;
    int number_dead;
} death_t;

typedef struct zones_entity_s {
    sfIntRect hitbox;
    sfRectangleShape *rect_hitbox;
    sfIntRect hitbox_attack;
    sfRectangleShape *rect_hitbox_attack;
    unsigned int l_radius;
    sfCircleShape *l_circle;
    unsigned int m_radius;
    sfCircleShape *m_circle;
    bool m_detect;
    unsigned int s_radius;
    sfCircleShape *s_circle;
    bool s_detect;
} zones_entity_t;

typedef struct mark_s {
    anim_t *anim;
    sfVector2f pos;
    int is_display;
} mark_t;

typedef enum faction {
    BLUE_TEAM = 0,
    RED_TEAM,
    PURPLE_TEAM,
    YELLOW_TEAM,
    GOBLIN_TEAM,
    AGAINST_ALL,
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

typedef struct damage_text_s {
    sfText *text;
    sfFont *font;
    float size;
    sfVector2f pos;
    anim_t *effect;
    damage_text_state_t state;
    struct damage_text_s *next;
} damage_text_t;

typedef struct common_entity_s {
    char *name;
    anim_t *anim;
    sfVector2f pos;
    color_entity_t color;
    state_entity_t state;
    side_x_t x;
    side_y_t y;
    zones_entity_t *zones;
    attributes_t *attributes;
    death_t *death;
    faction_t faction;
    faction_t faction_origin;
    my_clock_t *clock_cooldown_attack;
    float attack_cooldown;
    damage_text_t *damage_texts;
} common_entity_t;

typedef struct warrior_s {
    int line_attack;
    int max_line_attack;
    mark_t *exclam;
    mark_t *inter;
    base_t *base;
} warrior_t;

typedef struct goblin_s {
} goblin_t;

typedef union spe_s {
    warrior_t *warrior;
    goblin_t *goblin;
} spe_t;

typedef enum entity_type_s {
    WARRIOR,
    GOBLIN,
} entity_type_t;

typedef struct entity_s {
    spe_t *spe;
    common_entity_t *common;
    entity_type_t type;
    bool in_view;
    void (*updt)(void *rpg, struct entity_s *entity);
    void (*disp)(void *rpg, struct entity_s *entity);
    sfIntRect (*get_hitbox)(sfVector2f pos);
    sfIntRect (*get_hitbox_attack)(sfVector2f pos, side_x_t x, side_y_t y);
} entity_t;

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

typedef enum quest_type {
    KILL,
    TALK,
    GATHER,
    MOVE
} quest_type_t;

typedef struct quest_s {
    char *name;
    char *description;
    int reward;
    int xp;
    char *objective;
    bool is_done;
    bool is_active;
    bool is_displayed;
    quest_type_t type;
    sfSprite *sprite;
    sfText *name_s;
    sfText *desc_s;
    struct quest_s *next;
} quest_t;

typedef struct all_quests_s {
    char *proprietary;
    quest_t *quest;
    entity_t *entity;
    struct all_quests_s *next;
} all_quests_t;

typedef enum {
    MAIN_MENU,
    GAME,
    PAUSE,
    SETTINGS,
    SAVE_MENU,
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
    sfTexture *texture;
    sfText *text;
    sfFont *font;
    sfRectangleShape *rect_shape;
    sfIntRect rect;
    button_state_t state;
    void (*action)(void *rpg);
    struct button_s *next;
} button_t;

typedef struct menu_s {
    sfSprite *background;
    sfTexture *background_texture;
    my_clock_t *myclock;
    button_t *buttons;
    sfIntRect bg_rect;
    sfText *text;
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
    sfRectangleShape *shape;
    unsigned int size;
} collision_t;
typedef struct map_s {
    sfTexture *ground_texture;
    sfSprite *ground_sprite;
    sfTexture *high_texture;
    sfSprite *high_sprite;
} map_t;

typedef struct slot_s {
    int is_empty;
    int id;
    int is_active;
    int type;
    int access;
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
    entity_t *player;
    sfSprite *pp;
    slot_t *stuff;
} player_status_t;

typedef struct inventory_s {
    int gold;
    int size;
    int is_open;
    quest_t *quest;
    slot_t *slot;
    sfSprite *sprite;
    player_status_t *player_status;
} inventory_t;

enum item_type {
    WEAPON,
    ARMOR,
    POTION,
    QUEST,
    KEY,
    OTHER,
    ALL
};

typedef struct line_of_sight_data_s {
    sfVector2f start;
    sfVector2f end;
    int dx;
    int dy;
    int sx;
    int sy;
    int err;
    int e2;
    int sample_interval;
    int sample_counter;
} line_of_sight_data_t;

typedef struct rpg_s {
    win_t *win;
    map_t *map;
    sfEvent event;
    entity_t **ent;
    unsigned int ent_size;
    bool debug;
    menu_t *main_menu;
    menu_t *save_menu;
    menu_t *settings;
    state_t gamestate;
    all_quests_t *quests;
    sfText *quest_text;
    sfText *quest_desc;
    sfText *quest_info;
    interface_t *interface;
    collision_t *collision;
    inventory_t *inventory;
} rpg_t;

#include "../src/Init/init.h"
#include "../src/Display/display.h"
#include "../src/Menu/menu.h"
#include "../src/Event/event.h"
#include "../src/Destroy/destroy.h"
#include "../src/Update/update.h"
#include "../src/Lib/lib.h"
#include "../src/Animation/anim.h"
#include "../src/Quests/quests.h"
#include "../src/Defines/defines.h"
#include "../src/Update/Update_Warrior/update_warrior.h"
#include "../src/Update/Update_Entities/update_entities.h"
#include "../src/Init/Init_Entities/init_entities.h"
#include "../src/Init/Init_Entities/Init_Warrior/init_warrior.h"
#include "../src/Init/Init_Entities/Init_Common/init_common.h"
#include "../src/Lib/Entity_Tools/entity_lib.h"
#include "singleton.h"
