/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** entity_stun
*/

#include "rpg.h"

static void stun_enemy(entity_t *enemy)
{
    enemy->common->stun->is_stunned = true;
    printf("Enemy %s is stunned\n", enemy->common->name);
    sfClock_restart(enemy->common->stun->stun_mark->anim->myclock->clock);
    sfClock_restart(enemy->common->stun->stun_clock->clock);
}

void entity_stun(rpg_t *rpg, entity_t *entity)
{
    entity_t *enemy = get_nearest_entity(rpg, entity, true);

    if (enemy == NULL)
        return;
    if (entity_can_attack_target(rpg, entity, enemy))
        stun_enemy(enemy);
    entity->common->state = WORK;
}
