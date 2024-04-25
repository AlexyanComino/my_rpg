/*
** EPITECH PROJECT, 2024
** inventory_sys
** File description:
** player_status
*/

#include <stdio.h>
#include <stdlib.h>
#include "inventory.h"
#include "item.h"

sfText *init_text(sfVector2f pos, int size, sfColor color, char *val)
{
    sfText *text = sfText_create();

    sfText_setFont(text,
    sfFont_createFromFile("assets/fonts/m6x11plus.ttf"));
    sfText_setCharacterSize(text, size);
    sfText_setPosition(text, pos);
    sfText_setFillColor(text, color);
    sfText_setString(text, val);
    return (text);
}

static int setup_value(player_status_t *player_status)
{
    player_status->hp = 100;
    player_status->max_hp = 100;
    player_status->attack = 10;
    player_status->defense = 10;
    player_status->speed = 10;
    player_status->level = 1;
    player_status->xp = 0;
    player_status->max_xp = 100;
    player_status->gold = 0;
    return 0;
}

static void setup_sprite(player_status_t *player_status)
{
    player_status->s_gold =
    init_sprite_from_file("assets/item/Misc/Golden Coin.png");
    sfSprite_setPosition(player_status->s_gold, (sfVector2f){550, 430});
    sfSprite_setScale(player_status->s_gold, (sfVector2f){1.5, 1.5});
    player_status->s_hp =
    init_sprite_from_file("assets/item/Misc/Heart.png");
    sfSprite_setScale(player_status->s_hp, (sfVector2f){1.5, 1.5});
    sfSprite_setPosition(player_status->s_hp, (sfVector2f){400, 240});
    player_status->s_attack =
    init_sprite_from_file("assets/item/Weapon & Tool/Iron Sword.png");
    sfSprite_setScale(player_status->s_attack, (sfVector2f){1.5, 1.5});
    sfSprite_setPosition(player_status->s_attack, (sfVector2f){550, 240});
    player_status->s_def =
    init_sprite_from_file("assets/item/Weapon & Tool/Iron Shield.png");
    sfSprite_setScale(player_status->s_def, (sfVector2f){1.5, 1.5});
    sfSprite_setPosition(player_status->s_def, (sfVector2f){400, 300});
    player_status->s_speed =
    init_sprite_from_file("assets/item/Equipment/Leather Boot.png");
    sfSprite_setScale(player_status->s_speed, (sfVector2f){1.5, 1.5});
    sfSprite_setPosition(player_status->s_speed, (sfVector2f){550, 300});
}

static int setup_text(player_status_t *player_status)
{
    player_status->t_gold = init_text((sfVector2f){610, 430}, 40,
    sfColor_fromRGB(135, 195, 155), "0");
    player_status->t_hp = init_text((sfVector2f){460, 235}, 40,
    sfColor_fromRGB(135, 195, 155), "100");
    player_status->t_attack = init_text((sfVector2f){610, 235}, 40,
    sfColor_fromRGB(135, 195, 155), "10");
    player_status->t_defense = init_text((sfVector2f){460, 295}, 40,
    sfColor_fromRGB(135, 195, 155), "10");
    player_status->t_speed = init_text((sfVector2f){610, 295}, 40,
    sfColor_fromRGB(135, 195, 155), "10");
    player_status->t_level = init_text((sfVector2f){210, 435}, 40,
    sfColor_fromRGB(135, 195, 155), "{Lvl} : 1");
    return 0;
}

player_status_t *init_player_status(void)
{
    player_status_t *player_status = malloc(sizeof(player_status_t));

    setup_value(player_status);
    setup_sprite(player_status);
    setup_text(player_status);
    player_status->player = init_warrior(BLUE, (sfVector2f){0, 0},
        "Inventory");
    sfSprite_setScale(player_status->player->sprite, (sfVector2f){1.3, 1.3});
    player_status->pp = init_sprite_from_file("assets/inventory/19.png");
    sfSprite_setScale(player_status->pp, (sfVector2f){2, 2});
    sfSprite_setPosition(player_status->pp, (sfVector2f){180, 410});
    player_status->stuff = NULL;
    return (player_status);
}
