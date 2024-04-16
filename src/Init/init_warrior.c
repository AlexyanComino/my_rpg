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
    return attributes;
}

static my_clock_t *init_my_clock(void)
{
    my_clock_t *myclock = malloc(sizeof(my_clock_t));

    myclock->clock = sfClock_create();
    myclock->time = (sfTime){0};
    myclock->seconds = 0;
    return myclock;
}

static void init_dead(warrior_t *warrior)
{
    sfVector2f dead_pos;

    warrior->clock_dead = init_my_clock();
    warrior->texture_dead = sfTexture_createFromFile("assets/Dead.png", NULL);
    warrior->sprite_dead = sfSprite_create();
    sfSprite_setTexture(warrior->sprite_dead, warrior->texture_dead, sfTrue);
    warrior->rect_dead = (sfIntRect){0, 0, DEAD_WIDTH, DEAD_WIDTH};
    sfSprite_setTextureRect(warrior->sprite_dead, warrior->rect_dead);
    dead_pos = (sfVector2f) {warrior->pos.x + WARRIOR_WIDTH / 2 -
        DEAD_WIDTH / 2, warrior->pos.y + WARRIOR_WIDTH / 2 - DEAD_WIDTH / 2};
    sfSprite_setPosition(warrior->sprite_dead, dead_pos);
    warrior->number_dead = 0;
}

void init_warrior2(warrior_t *warrior)
{
    warrior->hitbox = get_hitbox_warrior(warrior->pos, warrior->x);
    warrior->rect_hitbox = init_rect_hitbox(warrior->hitbox, sfBlue);
    warrior->hitbox_attack = get_hitbox_attack(warrior->pos, warrior->x,
        warrior->y);
    warrior->rect_hitbox_attack = init_rect_hitbox(warrior->hitbox_attack,
        sfRed);
    warrior->attributes = get_attributes(warrior->color);
    sfSprite_setPosition(warrior->sprite, warrior->pos);
    sfSprite_setTextureRect(warrior->sprite, warrior->rect);
    init_dead(warrior);
}

warrior_t *init_warrior(color_warrior_t color, sfVector2f pos)
{
    warrior_t *warrior = malloc(sizeof(warrior_t));

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
    warrior->x = RIGHT;
    warrior->y = NONE;
    init_warrior2(warrior);
    return warrior;
}
