/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_common
*/

#include "rpg.h"

static color_entity_t get_color(char *color)
{
    if (!strcmp(color, "B"))
        return BLUE;
    if (!strcmp(color, "P"))
        return PURPLE;
    if (!strcmp(color, "R"))
        return RED;
    if (!strcmp(color, "Y"))
        return YELLOW;
    return -1;
}

static attributes_t *get_attributes(char **infos)
{
    attributes_t *attributes = malloc(sizeof(attributes_t));

    attributes->max_health = atoi(infos[8]);
    attributes->health = attributes->max_health;
    attributes->attack = atoi(infos[9]);
    attributes->defense = atoi(infos[10]);
    attributes->speed = atoi(infos[11]);
    return attributes;
}

static death_t *init_death(void)
{
    death_t *death = malloc(sizeof(death_t));

    death->anim = init_anim("assets/Entities/Effects/Dead.png", DEAD_WIDTH,
        DEAD_WIDTH);
    death->number_dead = 0;
    return death;
}

static faction_t get_faction(color_entity_t color, entity_type_t type)
{
    if (type == TORCH)
        return GOBLIN_TEAM;
    if (color == BLUE)
        return BLUE_TEAM;
    if (color == PURPLE)
        return PURPLE_TEAM;
    if (color == RED)
        return RED_TEAM;
    if (color == YELLOW)
        return YELLOW_TEAM;
    return GOBLIN_TEAM;
}

static float get_attack_cooldown(void)
{
    return (float)(rand() % 75 + 75) / 100;
}

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

common_entity_t *init_common(char **infos, entity_type_t type)
{
    common_entity_t *common = malloc(sizeof(common_entity_t));

    common->name = strdup(infos[1]);
    common->color = get_color(infos[2]);
    common->pos = (sfVector2f){atoi(infos[3]), atoi(infos[4])};
    common->anim = get_anim(type, common->color);
    common->state = IDLE;
    common->x = (rand() % 2 == 0) ? RIGHT : LEFT;
    common->y = NONE;
    common->zones = init_entity_zones(infos, common->pos, type);
    common->attributes = get_attributes(infos);
    common->death = init_death();
    common->faction = get_faction(common->color, type);
    common->faction_origin = common->faction;
    common->clock_cooldown_attack = init_my_clock();
    common->attack_cooldown = get_attack_cooldown();
    common->damage_texts = NULL;
    common->stun = init_stun();
    return common;
}
