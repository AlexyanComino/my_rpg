/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** actions2
*/

#include "rpg.h"

void selector(rpg_t *rpg)
{
    rpg->gamestate = SELECTOR;
    sfSprite_setOrigin(rpg->inventory->player_status->pp,
        (sfVector2f){40, 8});
    sfSprite_setOrigin(rpg->inventory->player_status->s_hp,
        (sfVector2f){16, 16});
    sfSprite_setOrigin(rpg->inventory->player_status->s_attack,
        (sfVector2f){16, 16});
    sfSprite_setOrigin(rpg->inventory->player_status->s_def,
        (sfVector2f){16, 16});
    sfSprite_setOrigin(rpg->inventory->player_status->s_speed,
        (sfVector2f){16, 16});
    setup_command_help_menu(rpg);
}
