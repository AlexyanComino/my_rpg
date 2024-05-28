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

static eff_t *init_fire(entity_type_t type, float scale)
{
    eff_t *fire = malloc(sizeof(eff_t));
    float new_scale = get_fire_scale(type) * scale;

    fire->eff_mark = init_mark("assets/Entities/Effects/Fire.png",
        FIRE_WIDTH, FIRE_WIDTH);
    sfSprite_setScale(fire->eff_mark->anim->sprite,
        (sfVector2f){new_scale, new_scale});
    fire->is_on_eff = false;
    fire->eff_duration = 3;
    fire->eff_cooldown = 0.75;
    fire->eff_clock = init_my_clock();
    fire->eff_damage_clock = init_my_clock();
    fire->eff_damage = 1;
    return fire;
}

static sfText *init_name_text(char *str, sfColor color, bool is_boss)
{
    sfText *text = sfText_create();
    char *font_path = (is_boss) ? "assets/fonts/BreatheFireIii-PKLOB.ttf" :
        "assets/fonts/Say Comic.ttf";
    sfFont *font = sfFont_createFromFile(font_path);
    sfFloatRect text_rect;
    float size = (is_boss) ? 80 : 17;
    float outline_size = (is_boss) ? 3 : 1;

    sfText_setString(text, str);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, size);
    text_rect = sfText_getGlobalBounds(text);
    sfText_setFillColor(text, color);
    sfText_setOutlineColor(text, sfBlack);
    sfText_setOutlineThickness(text, outline_size);
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

static eff_t *init_poison(float scale)
{
    eff_t *poison = malloc(sizeof(eff_t));

    poison->eff_mark = init_mark("assets/Entities/Effects/Poison.png",
        POISON_WIDTH, POISON_WIDTH);
    sfSprite_setScale(poison->eff_mark->anim->sprite,
        (sfVector2f){0.8 * scale, 0.8 * scale});
    poison->is_on_eff = false;
    poison->eff_duration = 5;
    poison->eff_cooldown = 1.25;
    poison->eff_clock = init_my_clock();
    poison->eff_damage_clock = init_my_clock();
    poison->eff_damage = 1;
    return poison;
}

static anim_sprite_t *init_grade_icon(common_entity_t *common)
{
    char *texture = (common->grade_type == ELITE) ?
        "assets/Entities/Elite.png" : "assets/Entities/boss.png";
    float scale = (common->grade_type == ELITE) ? 0.25 : 0.08;

    scale *= common->scale;
    return init_anim_sprite(texture, 0.04, 0.00035, scale);
}

void init_common2(common_entity_t *common, entity_type_t type)
{
    common->damage_texts = NULL;
    common->clock_cooldown_attack = init_my_clock();
    common->stun = init_stun();
    common->fire = init_fire(type, common->scale);
    if (common->grade_type != BOSS) {
        common->health_bar = init_health_bar(type, common->scale);
        common->name_text = init_name_text(common->name,
            get_color_name_text(common->color, type), false);
    } else {
        common->health_bar = init_health_bar_boss();
        common->name_text = init_name_text(common->name, sfWhite, true);
    }
    common->arrows_hit = NULL;
    common->is_fleeing = false;
    common->poison = init_poison(common->scale);
    if (common->grade_type != SOLDAT)
        common->grade_icon = init_grade_icon(common);
    else
        common->grade_icon = NULL;
}
