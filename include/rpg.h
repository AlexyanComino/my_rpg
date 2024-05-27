/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** my
*/

#pragma once

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <limits.h>
#include <wchar.h>
#include <locale.h>

#define NUM_POINTS 30

#define WIDTH 1920
#define HEIGHT 1080

#define CHOICE_WIDTH 518
#define CHOICE_HEIGHT 101

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

// Pawn
#define PAWN_WIDTH 1152 / 6
#define PAWN_OFFSET PAWN_WIDTH * 5
#define MIN_PAWN_LENGTH 80


// Torch
#define TORCH_WIDTH 192
#define TORCH_IDLE_OFFSET TORCH_WIDTH * 6
#define TORCH_OFFSET TORCH_WIDTH * 5
#define MIN_TORCH_LENGTH 90

// Tnt
#define TNT_WIDTH 192
#define TNT_OFFSET TORCH_WIDTH * 5
#define TNT_OFFSET_ATTACK TORCH_WIDTH * 6
#define MIN_TNT_LENGTH 400
#define MAX_TNT_LENGTH 200

#define DYNA_WIDTH 64
#define DYNA_OFFSET DYNA_WIDTH * 5

#define EXPLO_WIDTH 192
#define EXPLO_OFFSET EXPLO_WIDTH * 8

#define CIBLE_WIDTH 300

// Archer
#define ARCHER_WIDTH 192
#define ARCHER_OFFSET ARCHER_WIDTH * 5
#define ARCHER_OFFSET_ATTACK ARCHER_WIDTH * 7

#define ARROW_WIDTH 64
#define ARROW_COOLDOWN 10
#define ARROW_HIT_ENTITY_COOLDOWN 5

#define MIN_ARCHER_LENGTH 400

// Marks
#define EXCLAM_WIDTH 91
#define EXCLAM_HEIGHT 147
#define INTER_WIDTH 1015 / 14
#define INTER_HEIGHT 399 / 3
#define EXCLAM_COOLDOWN 0.5
#define INTER_INTERVAL 3.0
#define INTER_COOLDOWN 1.5

#define STUN_WIDTH 1192 / 2
#define STUN_HEIGHT 13776 / 41

#define GOB_EXCLAM_WIDTH 1788 / 3
#define GOB_EXCLAM_HEIGHT 3696 / 11

#define FIRE_WIDTH 128
#define POISON_WIDTH 200
//

// Cooldowns
#define DEAD_COOLDOWN 10.0

#define BASE_COLOR sfColor_fromRGB(146, 255, 250)

#define DAMAGE_COLOR_PLAYER sfWhite
#define DAMAGE_COLOR_BLUE sfColor_fromRGB(28, 86, 255)
#define DAMAGE_COLOR_RED sfColor_fromRGB(255, 88, 65)
#define DAMAGE_COLOR_YELLOW sfColor_fromRGB(255, 215, 66)
#define DAMAGE_COLOR_PURPLE sfColor_fromRGB(183, 133, 255)
#define DAMAGE_COLOR_GREEN sfColor_fromRGB(53, 255, 53)
#define DAMAGE_COLOR_BAM sfWhite
#define DAMAGE_COLOR_CRITICAL sfColor_fromRGB(255, 61, 30)
#define DAMAGE_COLOR_FIRE sfColor_fromRGB(255, 157, 59)
#define DAMAGE_COLOR_POISON sfColor_fromRGB(94, 209, 43)

#define CRIT_WIDTH 215
#define BAM_WIDTH 160

#define TILE_SCALE 2.1
#define TILE_SIZE 32 * TILE_SCALE

// Items
#define ITEM_SIZE 128

// Minimap
#define MINIMAP_ARROW_WIDTH 373

#define MINIMAP_BACK_SIZE 224

// Map
#define MAP_HEIGHT 13301
#define MAP_WIDTH 13971
#define WATER_ANIM_WIDTH 928
#define WATER_ANIM_HEIGHT 608
#define WATER_ANIM_OFFSET 7424 / 7

// Chests
#define CHEST_WIDTH 192

// Loading
#define DOTS_WIDTH 400
#define DOTS_HEIGHT 300
#define TRANSI_WIDTH 1000
#define TRANSI_HEIGHT 563

#define RESPAWN_TIME 180

typedef struct rpg_s rpg_t;
typedef struct entity_s entity_t;
typedef enum color_entity_s {
    BLUE = 0,
    PURPLE,
    RED,
    YELLOW,
    BLACK,
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
    ST_WORK,
    WORK,
    IDLE_CARRY,
    MOVE_CARRY,
    DEAD,
    INTERACT,
    RIEN,
} state_entity_t;

typedef struct attributes_s {
    unsigned int max_health;
    int health;
    unsigned int attack;
    unsigned int defense;
    unsigned int speed;
    unsigned int xp;
    unsigned int level;
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
    sfIntRect hitbox_foot;
    sfRectangleShape *rect_hitbox_foot;
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
    WITH_ALL,
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
    FIRE_TEXT,
    POISON_TEXT,
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

typedef struct stun_s {
    bool is_stunned;
    mark_t *stun_mark;
    my_clock_t *stun_clock;
    float stun_time;
} stun_t;

typedef struct eff_s {
    bool is_on_eff;
    mark_t *eff_mark;
    my_clock_t *eff_clock;
    float eff_duration;
    float eff_cooldown;
    my_clock_t *eff_damage_clock;
    int eff_damage;
} eff_t;

typedef struct round_rectangle_t {
    sfRectangleShape *rect_w;
    sfRectangleShape *rect_h;
    sfCircleShape *circle;
    sfVector2f circle_pos[4];
    sfVector2f size;
    sfVector2f init_size;
    int r;
    int init_r;
    sfVector2f pos;
} round_rectangle_t;

typedef struct health_bar_s {
    round_rectangle_t *back;
    round_rectangle_t *front;
    int diff_y;
} health_bar_t;


typedef enum arrow_state {
    FLY_ARROW,
    HIT_ARROW,
} arrow_state_t;

typedef enum arrow_dir_s {
    UP_ARROW,
    UP_LEFT_ARROW,
    UP_RIGHT_ARROW,
    DOWN_ARROW,
    DOWN_LEFT_ARROW,
    DOWN_RIGHT_ARROW,
    LEFT_ARROW,
    RIGHT_ARROW,
} arrow_dir_t;

typedef struct arrows_s {
    anim_t *anim;
    sfVector2f pos;
    sfVector2f dir;
    sfVector2f end;
    sfVertex vertices[2];
    arrow_state_t state;
    my_clock_t *myclock;
    int arrow_index;
    sfVector2f diff_center;
    struct arrows_s *next;
} arrows_t;

typedef enum grade_type_s {
    SOLDAT_QUEST,
    SOLDAT,
    ELITE,
    BOSS,
} grade_type_t;

typedef struct anim_sprite_s {
    sfSprite *sprite;
    sfTexture *texture;
    float scale_min;
    float scale_max;
    int scale_dir;
    float speed;
    float init_scale;
} anim_sprite_t;

typedef struct common_entity_s {
    char *name;
    sfText *name_text;
    anim_t *anim;
    sfVector2f pos;
    sfVector2f init_pos;
    color_entity_t color;
    state_entity_t state;
    float scale;
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
    stun_t *stun;
    eff_t *fire;
    eff_t *poison;
    health_bar_t *health_bar;
    arrows_t *arrows_hit;
    bool is_fleeing;
    grade_type_t grade_type;
    anim_sprite_t *grade_icon;
} common_entity_t;

typedef struct warrior_s {
    int line_attack;
    int max_line_attack;
    mark_t *exclam;
    mark_t *inter;
    base_t *base;
} warrior_t;

typedef enum pawn_job_s {
    CUT,
    WORKING,
    CARRY,
    NO_JOB,
} pawn_job_t;

typedef enum item_pawn_type_s {
    WOOD,
    MEAT,
    GOLD,
    NO_ITEM,
} item_pawn_type_t;

typedef struct item_pawn_s {
    char *name;
    item_pawn_type_t type;
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f *pos;
    int quantity;
    int *index_rev_scale;
} item_pawn_t;

typedef struct carry_s {
    sfVector2f obj_pos;
    bool is_carrying;
    item_pawn_type_t item_type;
    item_pawn_t *item;
} carry_t;

typedef struct pawn_s {
    pawn_job_t job;
    sfVector2f job_pos;
    my_clock_t *myclock;
    float job_cooldown;
    side_x_t job_side;
    carry_t *carry;
} pawn_t;

typedef struct torch_s {
    mark_t *exclam;
} torch_t;

typedef struct curve_s {
    sfVector2f *points;
    sfConvexShape *curve_shape;
    side_x_t x;
    side_y_t y;
    int nb_points;
} curve_t;

typedef struct dyna_s {
    anim_t *anim;
    float dyna_angle;
    sfVector2f pos;
    bool is_launched;
    sfVector2f *points;
    int index;
    side_x_t side;
} dyna_t;

typedef struct explo_s {
    anim_t *anim;
    sfCircleShape *boom_circle;
    int radius;
    sfVector2f boom_center;
    sfSprite *cible;
    sfTexture *cible_texture;
} explo_t;

typedef struct tnt_s {
    dyna_t *dyna;
    bool is_launched;
    curve_t *curve;
    bool is_exploded;
    explo_t *explo;
} tnt_t;

typedef struct archer_s {
    arrows_t *arrows;
    arrow_dir_t arrow_dir;
    base_t *base;
    mark_t *exclam;
    mark_t *inter;
} archer_t;

typedef union spe_s {
    warrior_t *warrior;
    pawn_t *pawn;
    torch_t *torch;
    tnt_t *tnt;
    archer_t *archer;
} spe_t;

typedef enum entity_type_s {
    WARRIOR,
    PAWN,
    TORCH,
    TNT,
    ARCHER,
} entity_type_t;

typedef struct entity_s {
    spe_t *spe;
    common_entity_t *common;
    entity_type_t type;
    bool in_view;
    void (*updt)(rpg_t *rpg, entity_t *entity);
    void (*disp)(rpg_t *rpg, entity_t *entity);
    void (*destroy)(entity_t *entity);
    void (*anim)(rpg_t *rpg, entity_t *entity);
    sfIntRect (*get_hitbox)(sfVector2f pos, float scale);
    sfIntRect (*get_hitbox_attack)(sfVector2f pos, side_x_t x, side_y_t y,
        float scale);
    sfIntRect (*get_hitbox_foot)(sfVector2f pos, float scale);
} entity_t;

typedef struct restricted_s {
    sfTexture *texture;
    sfSprite *sprite;
    sfVector2f danger_pos;
    bool animation;
    bool in_base;
} restricted_t;

typedef struct anim_text_s {
    sfText *text;
    sfText *shadow;
    float scale_min;
    float scale_max;
    int scale_dir;
    float speed;
    bool has_shadow;
} anim_text_t;

typedef struct popup_item_s {
    sfSprite *back_sprite;
    sfTexture *back_texture;
    sfSprite *light_sprite;
    sfTexture *light_texture;
    float light_angle;
    sfFont *font;
    anim_text_t *title;
    anim_sprite_t *item_anim;
    sfText *item_description;
    sfText *rarity;
    sfText *skip_text;
    int display;
} popup_item_t;

typedef struct player_infos_s {
    sfText *player_text;
    sfFont *font;
} player_infos_t;

typedef struct command_list_s {
    sfText *action;
    sfSprite *sprite;
    sfTexture *texture;
    struct command_list_s *next;
} command_list_t;

typedef struct interface_s {
    restricted_t *restricted;
    health_bar_t *health_bar;
    popup_item_t *popup_item;
    player_infos_t *player_infos;
    command_list_t *command_list;
} interface_t;

typedef enum quest_type {
    KILL,
    TALK,
    GATHER,
    MOVE
} quest_type_t;

typedef struct dialog_s {
    char *txt;
    struct dialog_s *next;
} dialog_t;

typedef struct quest_s {
    char *name;
    char *description;
    int reward;
    int xp;
    char *objective;
    bool is_done;
    bool is_active;
    bool is_displayed;
    bool is_last;
    quest_type_t type;
    dialog_t *dialog;
    sfSprite *sprite;
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
    SELECTOR,
    INVENTORY,
    MAP,
    SKILL_TREE,
    LOADING,
    END,
    CREDITS,
} state_t;

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
    char *name;
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
    int skill_points;
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

typedef enum button_state {
    HOVERED,
    CLICKED,
    RELEASED,
    NOTHING
} button_state_t;

typedef struct button_s {
    char *name;
    sfTexture *texture;
    sfSprite *sprite;
    sfText *text;
    sfText *shadow;
    sfFont *font;
    sfColor color;
    sfColor click_color;
    sfRectangleShape *rect_shape;
    sfIntRect rect;
    button_state_t state;
    attributes_t *attributes;
    void (*action)(void *rpg);
    struct button_s *next;
} button_t;

typedef struct menu_s {
    button_t *buttons;
    anim_text_t *title1;
    anim_text_t *title2;
    sfFont *font;
} menu_t;

typedef struct save_s {
    sfVector2f pos;
    attributes_t *attributes;
    int type;
    slot_t *slot;
    slot_t *stuff;
    all_quests_t *quests;
} save_t;

typedef struct save_button_s {
    char *name;
    entity_t *entity;
    sfText *text;
    sfText *new_txt;
    sfText *hp;
    sfText *attack;
    sfText *defense;
    sfText *speed;
    sfFont *font;
    sfTexture *pp_texture;
    sfSprite *pp_sprite;
    sfTexture *hp_texture;
    sfSprite *hp_sprite;
    sfTexture *attack_texture;
    sfSprite *attack_sprite;
    sfTexture *defense_texture;
    sfSprite *defense_sprite;
    sfTexture *speed_texture;
    sfSprite *speed_sprite;
    sfRectangleShape *rect_shape;
    sfIntRect rect;
    button_state_t state;
    attributes_t *attributes;
    void (*action)(void *rpg);
    struct save_button_s *next;
} save_button_t;

typedef struct save_menu_s {
    save_button_t *buttons;
    sfText *text;
    sfFont *font;
} save_menu_t;

typedef struct select_button_s {
    char *name;
    entity_t *entity;
    sfText *text;
    sfText *hp;
    sfText *attack;
    sfText *defense;
    sfText *speed;
    sfFont *font;
    sfTexture *pp_texture;
    sfSprite *pp_sprite;
    sfTexture *hp_texture;
    sfSprite *hp_sprite;
    sfTexture *attack_texture;
    sfSprite *attack_sprite;
    sfTexture *defense_texture;
    sfSprite *defense_sprite;
    sfTexture *speed_texture;
    sfSprite *speed_sprite;
    sfRectangleShape *rect_shape;
    sfIntRect rect;
    button_state_t state;
    attributes_t *attributes;
    void (*action)(void *rpg);
    struct select_button_s *next;
} select_button_t;

typedef struct select_menu_s {
    select_button_t *buttons;
    sfText *text;
    sfFont *font;
} select_menu_t;

typedef struct win_s {
    sfRenderWindow *window;
    sfView *view_menu;
    sfView *view;
    sfVector2f mouse_pos;
    unsigned int width;
    unsigned int height;
    unsigned int framerate;
    sfClock *clock;
    float dt;
    float zoom;
    sfVector2f view_pos;
    sfVector2f view_menu_move;
} win_t;

typedef struct region_s {
    sfVector2f *pos;
    unsigned int size;
    sfIntRect rect;
} region_t;

typedef struct collision_s {
    sfIntRect rect;
    unsigned int rows;
    unsigned int cols;
    region_t ***regions;
    sfRectangleShape *shape;
    sfRectangleShape *region_shape;
    unsigned int size;
} collision_t;
typedef struct map_s {
    sfTexture *ground_texture;
    sfSprite *ground_sprite;
    sfTexture *high_texture;
    sfSprite *high_sprite;
} map_t;

enum item_type {
    WEAPON,
    ARMOR,
    POTION,
    QUEST,
    KEY,
    OTHER,
    ALL
};

typedef struct inventory_s {
    int gold;
    int size;
    int is_open;
    all_quests_t *quest;
    int scroll;
    int scroll_max;
    sfText *desc;
    sfSprite *desc_sprite;
    slot_t *slot;
    sfSprite *sprite;
    player_status_t *player_status;
} inventory_t;


typedef struct weapon_s {
    char *name;
    int damage;
    int is_equipped;
    sfSprite *sprite;
} weapon_t;

enum armor_type {
    HELMET,
    CHESTPLATE,
    BOOTS
};

typedef struct armor_s {
    int defense;
    int speed;
    int armor_type;
    int is_equipped;
    char *name;
    int endurance;
    sfSprite *sprite;
} armor_t;

typedef enum {
    Q_START,
    Q_END,
    Q_HIDDEN
} quest_state_t;

typedef struct quest_header_s {
    sfText *text;
    sfFont *font;
    sfText *done;
    sfRectangleShape *rect;
    sfRectangleShape *rect2;
    quest_state_t state;
    my_clock_t *myclock;
} quest_header_t;

typedef struct text_box_s {
    sfSprite *box;
    sfTexture *box_texture;
    sfText *npc_name;
    sfText *npc_text;
    sfFont *font;
    sfClock *clock;
    button_t *choice;
    entity_t *entity;
    dialog_t *dialog;
    char *str;
    char *displayed_str;
    bool is_displayed;
    bool is_fully_displayed;
    int len;
    bool has_choice;
    all_quests_t *all_quests;
    quest_t *quest;
} text_box_t;

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

typedef struct {
    map_t *map;
    int loaded;
} shared_data_t;

typedef struct {
    entity_t **entities;
    unsigned int nb_entities;
    int loaded;
} shared_data2_t;

typedef struct minimap_s {
    sfView *view;
    sfVector2f pos;
    bool is_drag;
    float zoom;
    sfTexture *arrow_texture;
    sfSprite *arrow_sprite;
    float rotation;
    sfRectangleShape *rect;
    float size;
    sfTexture *blur_texture;
    sfSprite *blur;
    sfTexture *back_texture;
    sfSprite *back;
    sfFont *font;
    sfText **texts;
    int nb_texts;
} minimap_t;

typedef enum decor_type {
    GROUND,
    HIGH,
} decor_type_t;

typedef struct decor_anim_s {
    anim_t *anim;
    sfVector2f pos;
    int width;
    int height;
    float speed;
    int nb_rows;
    int nb_cols;
    sfIntRect rect;
    sfRectangleShape *shape;
    decor_type_t type;
} decor_anim_t;

typedef enum chest_state_s {
    CLOSED,
    OPENING,
    OPENED,
    CLOSING,
} chest_state_t;

typedef struct chest_s {
    anim_t *anim;
    sfVector2f pos;
    chest_state_t state;
    sfIntRect rect;
    sfRectangleShape *shape;
    enum item_type item_type;
    char *item_name;
    bool is_interacted;
    bool is_recieved;
} chest_t;

typedef enum rarity_s {
    COMMON,
    UNCOMMON,
    RARE,
    EPIC,
    LEGENDARY,
} rarity_t;

typedef struct item_s {
    char *name;
    char *texture_path;
    char *description;
    rarity_t rarity;
    enum item_type type;
    int damage;
    int defense;
    int speed;
    int endurance;
    enum armor_type armor_type;
} item_t;

typedef struct sounds_s {
    sfMusic* sword;
    sfMusic* arrow;
    sfMusic* attack_fire;
    sfMusic* attack_sword;
    sfMusic* burn;
    sfMusic* explosion;
    sfMusic* hammer;
    sfMusic* click;
    sfMusic* death;
    sfMusic* quest;
    sfMusic* items;
    sfMusic* intro;
    sfMusic* loop;
    sfMusic* open;
    sfMusic* close;
    sfMusic* attack;
    my_clock_t *myclock;
} sounds_t;

typedef struct skill_s skill_t;

typedef struct box_s {
    int hitbox_x;
    int hitbox_y;
    float scale;
} box_t;

typedef struct continue_s {
    bool is_arrived;
    bool move_text;
    sfVector2f text_pos;
    anim_text_t *anim_text;
} continue_t;

typedef struct transition_s {
    anim_t *anim;
    bool displayed;
    void (*callback)(rpg_t *rpg);
} transition_t;

typedef struct loading_s {
    anim_text_t *title1;
    anim_text_t *title2;
    anim_t *load;
    int is_loaded;
    my_clock_t *myclock;
    continue_t *cont;
    sfFont *font;
} loading_t;

typedef struct end_menu_s {
    anim_text_t *title1;
    anim_text_t *title2;
    button_t *buttons;
} end_menu_t;

typedef struct modes_s {
    bool debug;
    bool keynote_mode;
    bool k;
    bool plus;
} modes_t;

typedef struct pause_menu_s {
    anim_text_t *title;
    button_t *buttons;
    sfTexture *back_texture;
    sfSprite *back_sprite;
    sfFont *font;
} pause_menu_t;

typedef enum enum_vict {
    EXTEND_VIEW,
    WAIT_EXTEND,
    REDUCE_VIEW,
    WAIT_REDUCE,
    MOVE_TEXT,
} vict_state_t;

typedef struct vict_s {
    bool is_win;
    vict_state_t state;
    sfText *text;
    sfFont *font;
    sfVector2f text_pos;
    float size;
    float thickness;
    my_clock_t *myclock;
} vict_t;

typedef struct text_list_s {
    sfText *text;
    sfVector2f pos;
    struct text_list_s *next;
} text_list_t;
typedef struct credits_s {
    text_list_t *texts;
    sfFont *font;
} credits_t;

typedef struct comp_s {
    bool fire;
    bool poison;
} comp_t;

typedef struct rpg_s {
    win_t *win;
    map_t *map;
    minimap_t *minimap;
    sfEvent event;
    modes_t *modes;
    entity_t **ent;
    unsigned int ent_size;
    menu_t *main_menu;
    save_menu_t *save_menu;
    menu_t *settings;
    select_menu_t *selector;
    state_t gamestate;
    all_quests_t *quests;
    quest_header_t *quest_header;
    text_box_t *text_box;
    interface_t *interface;
    collision_t *collision;
    inventory_t *inventory;
    pthread_t thread;
    pthread_t thread2;
    shared_data_t *shared_data;
    shared_data2_t *shared_data2;
    int shm_fd1;
    int shm_fd2;
    unsigned int player_index;
    decor_anim_t **decors;
    unsigned int decors_size;
    chest_t **chests;
    unsigned int chests_size;
    item_t **items;
    unsigned int items_size;
    sounds_t *sounds;
    save_t **save;
    int save_index;
    float volume;
    skill_t *skill_tree;
    loading_t *loading;
    transition_t *transition;
    end_menu_t *end_menu;
    pause_menu_t *pause_menu;
    vict_t *vict;
    credits_t *credits;
    comp_t *comp;
} rpg_t;

#include "../src/xp_sys/xp.h"
#include "../src/skill_tree/skill_tree.h"
#include "../src/Init/init.h"
#include "../src/Display/Display_entities/display_entities.h"
#include "../src/Display/display.h"
#include "../src/Display/Display_Game/display_game.h"
#include "../src/Menu/menu.h"
#include "../src/Event/event.h"
#include "../src/Destroy/destroy.h"
#include "../src/Update/update.h"
#include "../src/Lib/lib.h"
#include "../src/Animation/anim.h"
#include "../src/Defines/defines.h"
#include "../src/Update/Update_Entities/Update_Warrior/update_warrior.h"
#include "../src/Update/Update_Entities/Update_Pawn/update_pawn.h"
#include "../src/Update/Update_Entities/Update_Torch/update_torch.h"
#include "../src/Update/Update_Entities/Update_Tnt/update_tnt.h"
#include "../src/Update/Update_Entities/Update_Archer/update_archer.h"
#include "../src/Update/Update_Entities/Update_Common/update_common.h"
#include "../src/Update/Update_Entities/update_entities.h"
#include "../src/Update/Update_Game/update_game.h"

#include "../src/Init/Init_Entities/init_entities.h"
#include "../src/Init/Init_Entities/Init_Warrior/init_warrior.h"
#include "../src/Init/Init_Entities/Init_Pawn/init_pawn.h"
#include "../src/Init/Init_Entities/Init_Torch/init_torch.h"
#include "../src/Init/Init_Entities/Init_Tnt/init_tnt.h"
#include "../src/Init/Init_Entities/Init_Archer/init_archer.h"
#include "../src/Init/Init_Entities/Init_Common/init_common.h"
#include "../src/Init/Init_Menus/init_menus.h"
#include "../src/Init/Init_Interface/init_interface.h"
#include "../src/Lib/Entity_Tools/entity_lib.h"
#include "../src/Sounds/sounds.h"
#include "singleton.h"
