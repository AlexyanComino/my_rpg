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
    if (!strcmp(color, "N"))
        return BLACK;
    fprintf(stderr, "Error: Invalid color\n");
    return -1;
}

static attributes_t *get_attributes(char **infos)
{
    attributes_t *attributes = malloc(sizeof(attributes_t));

    attributes->max_health = atoi(infos[10]);
    attributes->health = attributes->max_health;
    attributes->attack = atoi(infos[11]);
    attributes->defense = atoi(infos[12]);
    attributes->speed = atoi(infos[13]);
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
    if (color == BLACK)
        return WITH_ALL;
    if (type == TNT || type == TORCH)
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

static float get_attack_cooldown(float cooldown)
{
    float bonus = (float)(rand() % 250) / 1000;
    int sign = rand() % 2;

    if (sign == 0)
        return cooldown + bonus;
    return cooldown - bonus;
}

static grade_type_t get_entity_grade(char *info)
{
    if (!strcmp(info, "E"))
        return ELITE;
    if (!strcmp(info, "B"))
        return BOSS;
    return SOLDAT;
}

common_entity_t *init_common(char **infos,
    entity_type_t type)
{
    common_entity_t *common = malloc(sizeof(common_entity_t));

    common->name = strdup(infos[1]);
    common->color = get_color(infos[2]);
    common->pos = (sfVector2f){atoi(infos[3]), atoi(infos[4])};
    common->init_pos = common->pos;
    common->anim = get_anim(type, common->color);
    common->state = IDLE;
    common->x = (rand() % 2 == 0) ? RIGHT : LEFT;
    common->y = NONE;
    common->grade_type = get_entity_grade(infos[5]);
    common->scale = atof(infos[6]);
    common->zones = init_entity_zones(infos, common->pos, type, common->scale);
    common->attributes = get_attributes(infos);
    common->death = init_death();
    common->faction = get_faction(common->color, type);
    common->faction_origin = common->faction;
    common->attack_cooldown = get_attack_cooldown(atof(infos[14]));
    init_common2(common, type);
    return common;
}
