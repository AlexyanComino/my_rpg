/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_pnj_warrior
*/

#include "rpg.h"

void update_pnj_warrior(rpg_t *rpg, entity_t *tmp)
{
    entity_t *enemy = get_nearest_entity(rpg, tmp, false);

    if (is_stunned(tmp))
        return;
    if (!is_attacking(tmp))
        update_warrior_pos(rpg, tmp, enemy);
    if (enemy == NULL)
        return;
    update_warrior_marks(tmp);
    if (entity_can_attack(rpg, tmp, enemy)) {
        tmp->common->state = ST_ATT;
        init_entity_action(tmp);
    } else if (!is_alive(enemy)) {
        tmp->common->state = IDLE;
    }
}
