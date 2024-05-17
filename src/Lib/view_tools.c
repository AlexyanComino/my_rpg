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

    if (hitbox.left + hitbox.width < view_pos.x - view_size.x ||
        hitbox.left > view_pos.x + view_size.x ||
        hitbox.top + hitbox.height < view_pos.y - view_size.y ||
        hitbox.top > view_pos.y + view_size.y)
        return (false);
    return (true);
}

bool entity_is_in_view(rpg_t *rpg, entity_t *entity)
{
    return intrect_is_in_view(rpg, entity->common->zones->hitbox);
}
