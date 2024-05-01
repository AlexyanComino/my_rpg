/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** entity_attack
*/

#include "rpg.h"

static void entity_is_dead(entity_t *entity)
{
    printf("Entity %s is dead\n", entity->common->name);
    entity->common->state = DEAD;
    sfClock_restart(entity->common->death->anim->myclock->clock);
}

//
static void check_special_attack(entity_t *entity, entity_t *target,
    unsigned int *attack, damage_text_state_t *state)
{
    if (!entity_look_at_enemy(target, entity) &&
        !target->common->zones->s_detect) {
        *attack *= 4;
        if ((int)(target->common->attributes->health - *attack) <= 0)
            *state = BAM;
        else
            *state = CRITICAL;
    }
}

static void decrease_health(rpg_t *rpg, entity_t *entity, entity_t *target)
{
    unsigned int max_attack = (entity->common->attributes->attack -
        target->common->attributes->defense);
    unsigned int attack = rand() % max_attack;
    damage_text_state_t state = NORMAL;

    if (!is_player(rpg, target))
        check_special_attack(entity, target, &attack, &state);
    if (attack == 0)
        state = MISS;
    target->common->attributes->health -= attack;
    if (entity->common->faction == target->common->faction)
        entity->common->faction = AGAINST_ALL;
    add_dmg_text(rpg, target, attack, state);
    if (target->common->attributes->health <= 0)
        entity_is_dead(target);
}

void entity_attack(rpg_t *rpg, entity_t *entity)
{
    entity_t *enemy = get_nearest_entity(rpg, entity, true);

    if (enemy == NULL)
        return;
    if (entity_can_attack_target(entity, enemy))
        decrease_health(rpg, entity, enemy);
    else if (get_distance_between_pos(entity->common->pos,
        enemy->common->pos) <= 200)
        add_dmg_text(rpg, enemy, 0, MISS);
    entity->common->state = ATTACK;
}
