/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** event_loading
*/

#include "rpg.h"

static void launch_menu(rpg_t *rpg)
{
    rpg->gamestate = MAIN_MENU;
    sfView_setCenter(rpg->win->view_menu, rpg->win->view_pos);
    sfView_zoom(rpg->win->view_menu, rpg->win->zoom);
    sfRenderWindow_setView(rpg->win->window, rpg->win->view_menu);
    pthread_join(rpg->thread, NULL);
    if (rpg->shared_data->loaded)
        rpg->map = rpg->shared_data->map;
    sfSprite_setPosition(rpg->transition->anim->sprite, rpg->win->view_pos);
    sfSprite_setScale(rpg->transition->anim->sprite, (sfVector2f){4, 4});
}

void event_loading(rpg_t *rpg)
{
    sfKeyCode key = rpg->event.key.code;

    if (rpg->loading->is_loaded && key == sfKeySpace &&
        !rpg->transition->displayed) {
        launch_transition(rpg, &launch_menu);
    }
}
