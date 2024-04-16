/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** tools
*/

#include "rpg.h"

// Vérifie si un guerrier est dans la vue de la caméra
bool is_warrior_in_view(rpg_t *rpg, warrior_t *warrior)
{
    sfView* view = rpg->win->view;
    sfRenderWindow* window = rpg->win->window;
    sfFloatRect view_rect = sfView_getViewport(view);
    sfFloatRect warrior_rect = sfSprite_getGlobalBounds(warrior->sprite);
    sfVector2u window_size = sfRenderWindow_getSize(window);
    sfFloatRect win_rect = {view_rect.left, view_rect.top, view_rect.width *
    window_size.x, view_rect.height * window_size.y};

    if (sfFloatRect_intersects(&win_rect, &warrior_rect, NULL))
        return (true);
    return (false);
}
