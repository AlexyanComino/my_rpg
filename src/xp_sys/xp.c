/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** xp
*/

#include "rpg.h"


int add_xp(int xp)
{
    (*inventory())->player_status->xp += xp;
    return 0;
}

int manage_xp(rpg_t *rpg)
{
    attributes_t *attribute = get_player(rpg)->common->attributes;
    player_status_t *player_status = (*inventory())->player_status;
    char *str = malloc(sizeof(char) * 10);

    if (player_status->xp >=
        player_status->max_xp) {
        player_status->xp = 0;
        player_status->max_xp *= 1.5;
        player_status->level += 1;
        player_status->skill_points += 1;
        player_status->max_hp += 10;
        player_status->hp =
        player_status->max_hp;
        player_status->attack += 5;
        player_status->defense += 5;
        player_status->speed += 5;
        attribute->max_health = player_status->max_hp;
        sprintf(str, "%d", player_status->max_hp);
        sfText_setString(player_status->t_hp, str);
        attribute->attack = player_status->attack;
        sprintf(str, "%d", player_status->attack);
        sfText_setString(player_status->t_attack, str);
        attribute->defense = player_status->defense;
        sprintf(str, "%d", player_status->defense);
        sfText_setString(player_status->t_defense, str);
        attribute->speed = player_status->speed;
        sprintf(str, "%d", player_status->speed);
        sfText_setString(player_status->t_speed, str);
        attribute->level = player_status->level;
        sprintf(str, "Lvl: %d", player_status->level);
        sfText_setString(player_status->t_level, str);
        attribute->xp = player_status->xp;
    }
    
    return 0;
}
