/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_lwarrior
*/

#include "rpg.h"

static void add_warrior(lwarrior_t **lwarrior, warrior_t *warrior)
{
    lwarrior_t *new = malloc(sizeof(lwarrior_t));
    lwarrior_t *tmp = *lwarrior;

    new->warrior = warrior;
    new->next = NULL;
    while (tmp && tmp->next)
        tmp = tmp->next;
    if (tmp)
        tmp->next = new;
    else
        *lwarrior = new;
}

static void set_player_attribute(warrior_t *warrior)
{
    warrior->attributes->max_health = 200;
    warrior->attributes->health = warrior->attributes->max_health;
    warrior->attributes->speed = PLAYER_SPEED;
    warrior->attributes->attack = 50;
    warrior->attributes->defense = 10;
}

lwarrior_t *init_lwarrior(void)
{
    lwarrior_t *lwarrior = NULL;
    warrior_t *warrior = NULL;

    warrior = init_warrior(BLUE, (sfVector2f){3120, 3202}, PLAYER_NAME);
    set_player_attribute(warrior);
    add_warrior(&lwarrior, warrior);
    warrior = init_warrior(BLUE, (sfVector2f){800, 400}, "Renaut");
    add_warrior(&lwarrior, warrior);
    warrior = init_warrior(BLUE, (sfVector2f){1000, 200}, "Sylvain");
    add_warrior(&lwarrior, warrior);
    warrior = init_warrior(PURPLE, (sfVector2f){1200, 600}, "RodrigoVioletto");
    warrior = init_warrior(PURPLE, (sfVector2f){2392, 2900}, "Enemy");
    add_warrior(&lwarrior, warrior);
    warrior = init_warrior(BLUE, (sfVector2f){1600, 2700}, "Ally");
    add_warrior(&lwarrior, warrior);
    return lwarrior;
}
