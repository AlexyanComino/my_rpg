/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_inventory
*/

#include "rpg.h"

static void create_slot_inventory(rpg_t *rpg, int size)
{
    for (int i = 0; i < 4; i++)
        add_stuff(create_armor(rpg, "Iron Chestplate"), ARMOR);
    for (int i = 0; i <= 4; i++)
        remove_item(i, (*inventory())->player_status->stuff);
    for (int i = 0; i < size; i++)
        add_item(create_weapon(rpg, "Iron Sword"), WEAPON, "Iron Sword");
    for (int i = 0; i <= size; i++)
        remove_item(i, (*inventory())->slot);
}

int init_inventory(rpg_t *rpg, int size)
{
    inventory_t *inv = malloc(sizeof(inventory_t));

    inv->is_open = 0;
    inv->gold = 0;
    inv->size = size;
    inv->slot = NULL;
    inv->quest = NULL;
    inv->scroll = 0;
    inv->scroll_max = 0;
    inv->sprite = init_sprite_from_file("assets/inventory/1.png");
    inv->player_status = init_player_status();
    inv->desc = init_text((sfVector2f){0, 0}, 30,
        sfColor_fromRGB(135, 195, 155), "");
    inv->desc_sprite = init_sprite_from_file("assets/inventory/desc_inv.png");
    sfSprite_setScale(inv->desc_sprite, (sfVector2f){1.3, 1.3});
    sfSprite_setScale(inv->sprite, (sfVector2f){2, 2});
    sfSprite_setPosition(inv->sprite, (sfVector2f){0, 80});
    *inventory() = inv;
    (*inventory())->quest = rpg->quests;
    create_slot_inventory(rpg, size);
    return (0);
}
