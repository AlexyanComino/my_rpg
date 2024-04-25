/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_pnj_warrior
*/

#include "rpg.h"

static bool warrior_can_attack(warrior_t *warrior, warrior_t *target)
{
    update_clock_seconds(warrior->clock_cooldown_attack);
    if (warrior->clock_cooldown_attack->seconds > warrior->attack_cooldown) {
        if ((warrior->state == IDLE || warrior->state == WALK ||
            warrior->state == RUN) &&
            warrior_can_attack_target(warrior, target) &&
            is_alive(target)) {
            return true;
        }
    }
    return false;
}

void update_pnj_warrior(rpg_t *rpg, warrior_t *tmp)
{
    warrior_t *enemy = get_nearest_warrior(rpg, tmp);

    if (not_attacking(tmp))
        update_warrior_pos(rpg, tmp, enemy);
    if (enemy == NULL)
        return;
    update_warrior_detection(rpg, tmp, enemy);
    if (warrior_can_attack(tmp, enemy)) {
        tmp->state = ST_ATT;
        tmp->rect.left = 0;
        update_attack_rect(tmp);
    } else if (!is_alive(enemy)) {
        tmp->state = IDLE;
    }
}
