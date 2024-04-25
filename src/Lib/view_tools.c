/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** view_tools
*/

#include "rpg.h"

bool intrect_is_in_view(rpg_t *rpg, sfIntRect hitbox)
{
    sfVector2f view_pos = sfView_getCenter(rpg->win->view);
    sfVector2f view_size = sfView_getSize(rpg->win->view);

    if (hitbox.left + hitbox.width < view_pos.x - view_size.x / 2 ||
        hitbox.left > view_pos.x + view_size.x / 2 ||
        hitbox.top + hitbox.height < view_pos.y - view_size.y / 2 ||
        hitbox.top > view_pos.y + view_size.y / 2)
        return (false);
    return (true);
}

bool warrior_is_in_view(rpg_t *rpg, warrior_t *warrior)
{
    return intrect_is_in_view(rpg, warrior->zones->hitbox);
}
