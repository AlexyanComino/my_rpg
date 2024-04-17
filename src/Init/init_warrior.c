/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_warrior
*/

#include "rpg.h"

static sfTexture *get_warrior_texture(color_warrior_t color)
{
    sfTexture *texture = NULL;

    if (color == BLUE)
        texture = sfTexture_createFromFile("assets/Warrior_Blue.png", NULL);
    else
        texture = sfTexture_createFromFile("assets/Warrior_Purple.png", NULL);
    return texture;
}

static sfRectangleShape *init_rect_hitbox(sfIntRect hitbox, sfColor color)
{
    sfRectangleShape *rect_hitbox = sfRectangleShape_create();

    sfRectangleShape_setSize(rect_hitbox, (sfVector2f){hitbox.width,
        hitbox.height});
    sfRectangleShape_setPosition(rect_hitbox, (sfVector2f){hitbox.left,
        hitbox.top});
    sfRectangleShape_setFillColor(rect_hitbox, sfTransparent);
    sfRectangleShape_setOutlineColor(rect_hitbox, color);
    sfRectangleShape_setOutlineThickness(rect_hitbox, 1);
    return rect_hitbox;
}

static unsigned int get_max_health(color_warrior_t color)
{
    if (color == BLUE)
        return 100;
    else
        return 150;
}

static attributes_t *get_attributes(color_warrior_t color)
{
    attributes_t *attributes = malloc(sizeof(attributes_t));

    attributes->max_health = get_max_health(color);
    attributes->health = attributes->max_health;
    attributes->speed = 100;
    attributes->attack = 25;
    attributes->defense = 0;
    return attributes;
}

my_clock_t *init_my_clock(void)
{
    my_clock_t *myclock = malloc(sizeof(my_clock_t));

    myclock->clock = sfClock_create();
    myclock->time = (sfTime){0};
    myclock->seconds = 0;
    return myclock;
}

static anim_death_t *init_death(warrior_t *warrior)
{
    anim_death_t *death = malloc(sizeof(anim_death_t));

    death->clock_dead = init_my_clock();
    death->texture_dead = sfTexture_createFromFile("assets/Dead.png", NULL);
    death->sprite_dead = sfSprite_create();
    sfSprite_setTexture(death->sprite_dead, death->texture_dead, sfTrue);
    death->rect_dead = (sfIntRect){0, 0, DEAD_WIDTH, DEAD_WIDTH};
    sfSprite_setTextureRect(death->sprite_dead, death->rect_dead);
    death->dead_pos = (sfVector2f) {warrior->pos.x + WARRIOR_WIDTH / 2 -
        DEAD_WIDTH / 2, warrior->pos.y + WARRIOR_WIDTH / 2 - DEAD_WIDTH / 2};
    death->number_dead = 0;
    return death;
}

static void init_circle_reset(zones_warrior_t *zones, warrior_t *warrior)
{
    zones->circle_reset = sfCircleShape_create();
    zones->radius_reset = 700;
    sfCircleShape_setRadius(zones->circle_reset, zones->radius_reset);
    sfCircleShape_setFillColor(zones->circle_reset, sfTransparent);
    sfCircleShape_setOutlineColor(zones->circle_reset, sfWhite);
    sfCircleShape_setOutlineThickness(zones->circle_reset, 1);
    sfCircleShape_setOrigin(zones->circle_reset, (sfVector2f)
        {zones->radius_reset, zones->radius_reset});
    zones->circle_reset_pos = (sfVector2f){warrior->pos.x + WARRIOR_WIDTH / 3 +
        WARRIOR_WIDTH / 6, warrior->pos.y + WARRIOR_WIDTH / 3 +
        WARRIOR_WIDTH / 6};
}

static zones_warrior_t *init_zones(warrior_t *warrior)
{
    zones_warrior_t *zones = malloc(sizeof(zones_warrior_t));

    zones->hitbox = get_hitbox_warrior(warrior->pos, warrior->x);
    zones->rect_hitbox = init_rect_hitbox(zones->hitbox, sfBlue);
    zones->hitbox_attack = get_hitbox_attack(warrior->pos, warrior->x,
        warrior->y);
    zones->rect_hitbox_attack = init_rect_hitbox(zones->hitbox_attack,
        sfRed);
    init_circle_reset(zones, warrior);
    return zones;
}

void init_warrior2(warrior_t *warrior)
{
    warrior->zones = init_zones(warrior);
    warrior->attributes = get_attributes(warrior->color);
    sfSprite_setPosition(warrior->sprite, warrior->pos);
    sfSprite_setTextureRect(warrior->sprite, warrior->rect);
    warrior->death = init_death(warrior);
    warrior->exclam = init_exclam(warrior);
    warrior->inter = init_inter(warrior);
}

warrior_t *init_warrior(color_warrior_t color, sfVector2f pos, char *name)
{
    warrior_t *warrior = malloc(sizeof(warrior_t));

    warrior->name = strdup(name);
    warrior->texture = get_warrior_texture(color);
    warrior->sprite = sfSprite_create();
    sfSprite_setTexture(warrior->sprite, warrior->texture, sfTrue);
    warrior->myclock = init_my_clock();
    warrior->rect = (sfIntRect){0, 0, WARRIOR_WIDTH, WARRIOR_WIDTH};
    warrior->color = color;
    warrior->pos = pos;
    warrior->state = IDLE;
    warrior->max_line_attack = 0;
    warrior->line_attack = 0;
    warrior->x = (rand() % 2 == 0) ? RIGHT : LEFT;
    warrior->y = NONE;
    init_warrior2(warrior);
    return warrior;
}
