/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** eff_entity_attack
*/

#include "rpg.h"


// Flottant entre 5 et 9
static float get_fire_duration(void)
{
    return ((float)rand() / RAND_MAX) * (4) + 5;
}

// Flottant entre 0.4 et 0.8
static float get_fire_cooldown(void)
{
    return ((float)rand() / RAND_MAX) * (4) / 10 + 4 / 10;
}

// Flottant entre 0.3 et 0.45 * attack
static unsigned int get_fire_damage(unsigned int attack)
{
    float mult = ((float)rand() / RAND_MAX) * (15) / 100 + 30 / 100;

    return (attack * mult);
}

void burn_entity(entity_t *target, unsigned int attack)
{
    target->common->fire->is_on_eff = true;
    target->common->fire->eff_duration = get_fire_duration();
    target->common->fire->eff_cooldown = get_fire_cooldown();
    target->common->fire->eff_damage = get_fire_damage(attack);
    sfClock_restart(target->common->fire->eff_clock->clock);
    sfClock_restart(target->common->fire->eff_damage_clock->clock);
}

// Flottant entre 10 et 18
static float get_poison_duration(void)
{
    return ((float)rand() / RAND_MAX) * (8) + 10;
}

// Flottant entre 1 et 2
static float get_poison_cooldown(void)
{
    return ((float)rand() / RAND_MAX) + 1;
}

// Flottant entre 0.15 et 0.25 * attack
static float get_poison_damage(unsigned int attack)
{
    float mult = ((float)rand() / RAND_MAX) * (10) / 100 + 15 / 100;

    return (attack * mult);
}

void poison_entity(entity_t *target, unsigned int attack)
{
    target->common->poison->is_on_eff = true;
    target->common->poison->eff_duration = get_poison_duration();
    target->common->poison->eff_cooldown = get_poison_cooldown();
    target->common->poison->eff_damage = get_poison_damage(attack);
    sfClock_restart(target->common->poison->eff_clock->clock);
    sfClock_restart(target->common->poison->eff_damage_clock->clock);
    sfSprite_setPosition(target->common->poison->eff_mark->anim->sprite,
        target->common->pos);
}
