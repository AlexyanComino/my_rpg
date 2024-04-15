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

    while (sfRenderWindow_isOpen(rpg->win->window)) {
        event(rpg);
        display_all(rpg);
    }
    destroy_rpg(rpg);
    return 0;
}
