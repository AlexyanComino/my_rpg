/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** warrior_attack
*/

#include "rpg.h"

void update_attack_rect(warrior_t *warrior)
{
    if (warrior->y == NONE)
        warrior->rect.top = WARRIOR_WIDTH * 2;
    if (warrior->y == DOWN)
        warrior->rect.top = WARRIOR_WIDTH * 4;
    if (warrior->y == UP)
        warrior->rect.top = WARRIOR_WIDTH * 6;
}

static void warrior_is_dead(warrior_t *warrior)
{
    printf("Warrior %s is dead\n", warrior->name);
    warrior->state = DEAD;
    sfClock_restart(warrior->death->clock_dead->clock);
}

//
static void decrease_health(rpg_t *rpg, warrior_t *warrior, warrior_t *target)
{
    unsigned int max_attack = (warrior->attributes->attack -
        target->attributes->defense);
    unsigned int attack = rand() % max_attack;

    target->attributes->health -= attack;
    add_damage_text(rpg, target, attack);
    // printf("Warrior %s attack %s with -%d --> %d\n", warrior->name, target->name,
    //     attack, target->attributes->health);
    if (target->attributes->health <= 0)
        warrior_is_dead(target);
}

void warrior_attack(rpg_t *rpg, warrior_t *warrior)
{
    warrior_t *enemy = get_nearest_warrior(rpg, warrior);

    if (enemy == NULL)
        return;
    if (warrior_can_attack_target(warrior, enemy))
        decrease_health(rpg, warrior, enemy);
    else if (get_distance_between_pos(warrior->pos, enemy->pos) <= 200)
        add_damage_text(rpg, enemy, 0);
}
