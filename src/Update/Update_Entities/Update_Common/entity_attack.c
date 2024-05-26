/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** entity_attack
*/

#include "rpg.h"

void entity_is_dead(rpg_t *rpg, entity_t *entity)
{
    printf("Entity %s is dead\n", entity->common->name);
    entity->common->state = DEAD;
    entity->common->fire->is_on_eff = false;
    entity->common->stun->is_stunned = false;
    sfClock_restart(entity->common->death->anim->myclock->clock);
    play_music(rpg->sounds->death, 100);
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

static unsigned int get_attack(entity_t *entity, entity_t *target)
{
    int attack = entity->common->attributes->attack -
        target->common->attributes->defense;
    int quart = 0;
    int bonus_attack = 0;

    quart = (attack * 0.25);
    if (quart == -1)
        quart = 0;
    bonus_attack = rand() % (quart + 1);
    if (rand() % 2 == 0)
        attack += bonus_attack;
    else
        attack -= bonus_attack;
    if (attack < 0)
        attack = 0;
    return attack;
}

void decrease_health(rpg_t *rpg, entity_t *entity, entity_t *target)
{
    unsigned int attack = get_attack(entity, target);
    damage_text_state_t state = NORMAL;

    if (!is_player(rpg, target))
        check_special_attack(entity, target, &attack, &state);
    if (attack == 0)
        state = MISS;
    if (is_player(rpg, entity) &&
        entity->common->faction == target->common->faction)
        entity->common->faction = AGAINST_ALL;
    target->common->attributes->health -= attack;
    if (entity->type == TORCH)
        burn_entity(rpg, target, attack);
    if (is_player(rpg, entity) && sfKeyboard_isKeyPressed(sfKeyX))
        poison_entity(target, attack);
    add_dmg_text(rpg, target, attack, state);
    target->common->x = get_entity_side(target, entity->common->pos);
    if (target->common->attributes->health <= 0)
        entity_is_dead(rpg, target);
}

static void check_miss_attack(rpg_t *rpg, entity_t *entity, entity_t *enemy)
{
    if (entity->type == TNT) {
        if (get_distance(entity->spe->tnt->explo->boom_center,
            enemy->common->pos) <= 140)
            add_dmg_text(rpg, enemy, 0, MISS);
    } else {
        if (get_distance(entity->common->pos,
            enemy->common->pos) <= 190 * entity->common->scale)
            add_dmg_text(rpg, enemy, 0, MISS);
    }
}

void entity_attack(rpg_t *rpg, entity_t *entity)
{
    for (unsigned int i = 0; i < rpg->ent_size; i++) {
        if (!rpg->ent[i]->in_view || rpg->ent[i]->common->state == DEAD ||
            rpg->ent[i] == entity)
            continue;
        if (!is_player(rpg, entity) &&
            (entity->common->faction == rpg->ent[i]->common->faction ||
            rpg->ent[i]->common->faction == WITH_ALL))
            continue;
        if (entity_can_attack_target(rpg, entity, rpg->ent[i])) {
            touch(entity, rpg);
            decrease_health(rpg, entity, rpg->ent[i]);
        } else {
            which_entities(rpg, entity);
            check_miss_attack(rpg, entity, rpg->ent[i]);
        }
    }
    if (entity->type != TNT)
        entity->common->state = ATTACK;
}
