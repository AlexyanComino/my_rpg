/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_game
*/

#include "rpg.h"

static void check_game_is_win(rpg_t *rpg)
{
    for (unsigned int i = 0; i < rpg->ent_size; i++) {
        if (rpg->ent[i]->type != WARRIOR)
            continue;
        if (rpg->ent[i]->common->color == BLACK &&
            rpg->ent[i]->common->state == DEAD) {
            rpg->vict->is_win = true;
            rpg->vict->state = WAIT_EXTEND;
            sfClock_restart(rpg->vict->myclock->clock);
        }
    }
}

void update_game(rpg_t *rpg)
{
    update_quest_header(rpg);
    if (rpg->vict->is_win)
        return update_victory(rpg);
    check_game_is_win(rpg);
    manage_xp(rpg);
    update_game_interface(rpg);
    update_chests(rpg);
    update_entities(rpg);
    update_quests(rpg);
    update_decors_anim(rpg, intrect_is_in_real_view);
}
