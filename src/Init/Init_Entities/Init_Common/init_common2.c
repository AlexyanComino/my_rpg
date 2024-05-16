/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_common2
*/

#include "rpg.h"

static mark_t *init_mark(char *path, int width, int height)
{
    mark_t *mark = malloc(sizeof(mark_t));

    mark->anim = init_anim(path, width, height);
    mark->is_display = 0;
    return mark;
}

static stun_t *init_stun(void)
{
    stun_t *stun = malloc(sizeof(stun_t));

    stun->stun_mark = init_mark("assets/Entities/Effects/stun.png",
        STUN_WIDTH, STUN_HEIGHT);
    sfSprite_setScale(stun->stun_mark->anim->sprite, (sfVector2f){0.4, 0.4});
    stun->is_stunned = false;
    stun->stun_time = 2;
    stun->stun_clock = init_my_clock();
    return stun;
}

static float get_fire_scale(entity_type_t type)
{
    if (type == WARRIOR)
        return 1.2;
    if (type == PAWN)
        return 0.9;
    return 1;
}

static fire_t *init_fire(entity_type_t type)
{
    fire_t *fire = malloc(sizeof(fire_t));
    float scale = get_fire_scale(type);

    fire->fire_mark = init_mark("assets/Entities/Effects/Fire.png",
        FIRE_WIDTH, FIRE_WIDTH);
    sfSprite_setScale(fire->fire_mark->anim->sprite,
        (sfVector2f){scale, scale});
    fire->is_on_fire = false;
    fire->burn_time = 2;
    fire->fire_clock = init_my_clock();
    fire->fire_damage_clock = init_my_clock();
    fire->fire_damage = 1;
    return fire;
}

static sfVector2f get_back_health_bar_size(entity_type_t type)
{
    type = type;
    return (sfVector2f){76, 16};
}

static sfVector2f get_front_health_bar_size(entity_type_t type)
{
    type = type;
    return (sfVector2f){70, 10};
}

static health_bar_t *init_health_bar(entity_type_t type)
{
    health_bar_t *health_bar = malloc(sizeof(health_bar_t));
    sfVector2f back_size = get_back_health_bar_size(type);
    sfVector2f front_size = get_front_health_bar_size(type);

    health_bar->back = init_round_rectangle((sfVector2f){0, 0}, 7,
        back_size, sfBlack);
    health_bar->front = init_round_rectangle((sfVector2f){0, 0}, 5,
        front_size, sfGreen);
    health_bar->diff_y = 40;
    return health_bar;
}

static sfText *init_name_text(char *str, int size, sfColor color)
{
    sfText *text = sfText_create();
    sfFont *font = sfFont_createFromFile("assets/fonts/Say Comic.ttf");
    sfFloatRect text_rect;

    sfText_setString(text, str);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, size);
    text_rect = sfText_getGlobalBounds(text);
    sfText_setFillColor(text, color);
    sfText_setOutlineColor(text, sfBlack);
    sfText_setOutlineThickness(text, 1);
    sfText_setOrigin(text, (sfVector2f){text_rect.width / 2,
        text_rect.height / 2});
    return text;
}

static sfColor get_color_name_text(color_entity_t color, entity_type_t type)
{
    if (type == TNT || type == TORCH)
        return sfColor_fromRGB(118, 255, 45);
    if (color == BLUE)
        return sfColor_fromRGB(93, 223, 255);
    if (color == PURPLE)
        return sfColor_fromRGB(172, 106, 255);
    if (color == RED)
        return sfColor_fromRGB(255, 103, 103);
    if (color == YELLOW)
        return sfColor_fromRGB(255, 224, 30);
    return sfWhite;
}

void init_common2(common_entity_t *common, entity_type_t type)
{
    common->stun = init_stun();
    common->fire = init_fire(type);
    common->health_bar = init_health_bar(type);
    common->name_text = init_name_text(common->name, 17, get_color_name_text(
        common->color, type));
    common->arrows_hit = NULL;
    common->is_fleeing = false;
}
