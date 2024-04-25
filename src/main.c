/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** main
*/

#include "rpg.h"

int main(void)
{
    rpg_t *rpg = init_rpg();

    init_inventory(15);
    for (int i = 0; i < 15; i++)
        add_item(create_weapon(10), WEAPON);
    for (int i = 0; i < 15; i++)
        remove_item(i, (*inventory())->slot);
    while (sfRenderWindow_isOpen(rpg->win->window)) {
        event(rpg);
        update_all(rpg);
        display_all(rpg);
    }
    destroy_rpg(rpg);
    return 0;
}
