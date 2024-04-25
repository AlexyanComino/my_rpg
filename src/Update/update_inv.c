/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_inv
*/

#include "rpg.h"
#include "singleton.h"


static int update_slot(void)
{
    int x = 0;
    int y = 0;
    inventory_t *inv = (*inventory());

    sfSprite_setPosition(inv->sprite, (sfVector2f){(*view_pos()).x - 960,
        (*view_pos()).y - 450});
    for (slot_t *tmp = inv->slot; tmp; tmp = tmp->next) {
        sfSprite_setPosition(tmp->sprite,
        (sfVector2f){(*view_pos()).x - 770 + x, (*view_pos()).y + y});
        sfSprite_setPosition(tmp->highlight,
        (sfVector2f){(*view_pos()).x - 785 + x, (*view_pos()).y - 17 + y});
        x += 100;
        if (x > 400) {
            y += 100;
            x = 0;
        }
    }
    return 0;
}

static int update_stuff(void)
{
    int x = 0;
    int y = 0;
    inventory_t *inv = (*inventory());

    for (slot_t *tmp = inv->player_status->stuff; tmp; tmp = tmp->next) {
        sfSprite_setPosition(tmp->sprite,
        (sfVector2f){(*view_pos()).x - 595 + x, (*view_pos()).y - 150});
        sfSprite_setPosition(tmp->highlight,
        (sfVector2f){(*view_pos()).x - 611 + x, (*view_pos()).y - 167});
        x += 75;
        if (x > 400) {
            y += 75;
            x = 0;
        }
    }
    return 0;
}

static void update_player_status(void)
{
    inventory_t *inv = (*inventory());

    sfSprite_setPosition(inv->player_status->s_attack,
    (sfVector2f){(*view_pos()).x - 420, (*view_pos()).y - 280});
    sfText_setPosition(inv->player_status->t_attack,
    (sfVector2f){(*view_pos()).x - 370, (*view_pos()).y - 280});
    sfSprite_setPosition(inv->player_status->s_hp,
    (sfVector2f){(*view_pos()).x - 575, (*view_pos()).y - 280});
    sfText_setPosition(inv->player_status->t_hp,
    (sfVector2f){(*view_pos()).x - 520, (*view_pos()).y - 280});
    sfSprite_setPosition(inv->player_status->s_speed,
    (sfVector2f){(*view_pos()).x - 420, (*view_pos()).y - 220});
    sfText_setPosition(inv->player_status->t_speed,
    (sfVector2f){(*view_pos()).x - 370, (*view_pos()).y - 220});
    sfSprite_setPosition(inv->player_status->s_def,
    (sfVector2f){(*view_pos()).x - 575, (*view_pos()).y - 220});
}

static void update_player_stat(void)
{
    inventory_t *inv = (*inventory());

    sfText_setPosition(inv->player_status->t_defense,
    (sfVector2f){(*view_pos()).x - 520, (*view_pos()).y - 220});
    sfSprite_setPosition(inv->player_status->s_gold,
    (sfVector2f){(*view_pos()).x - 375, (*view_pos()).y - 70});
    sfText_setPosition(inv->player_status->t_gold,
    (sfVector2f){(*view_pos()).x - 320, (*view_pos()).y - 70});
    sfText_setPosition(inv->player_status->t_level,
    (sfVector2f){(*view_pos()).x - 755, (*view_pos()).y - 70});
    sfSprite_setPosition(inv->player_status->pp,
    (sfVector2f){(*view_pos()).x - 780, (*view_pos()).y - 105});
    sfSprite_setPosition(inv->player_status->player->sprite,
    (sfVector2f){(*view_pos()).x - 702, (*view_pos()).y - 175});
}

int update_inv(rpg_t *rpg)
{
    if (rpg->gamestate == INVENTORY) {
        update_slot();
        update_stuff();
        update_player_status();
        update_player_stat();
        open_inventory(rpg);
    }
    return 0;
}
