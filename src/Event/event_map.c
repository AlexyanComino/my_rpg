/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** event_minimap
*/

#include "rpg.h"

static void update_text_cities_size(rpg_t *rpg, float zoom)
{
    rpg->minimap->texts_size *= zoom;
    rpg->minimap->texts_thickness *= zoom;
    for (int i = 0; i < rpg->minimap->nb_texts; i++) {
        sfText_setCharacterSize(rpg->minimap->texts[i],
            rpg->minimap->texts_size);
        sfText_setOrigin(rpg->minimap->texts[i], (sfVector2f)
            {sfText_getLocalBounds(rpg->minimap->texts[i]).width / 2,
            sfText_getLocalBounds(rpg->minimap->texts[i]).height / 2});
        sfText_setOutlineThickness(rpg->minimap->texts[i],
            rpg->minimap->texts_thickness);
    }
}

static void add_zoom_minimap(rpg_t *rpg)
{
    if (rpg->minimap->zoom < 5)
        return;
    rpg->minimap->zoom *= 0.9;
    sfView_zoom(rpg->minimap->view, 0.9);
    update_text_cities_size(rpg, 0.9);
}

static void sub_zoom_minimap(rpg_t *rpg)
{
    if (rpg->minimap->zoom > 500)
        return;
    rpg->minimap->zoom *= 1.1;
    if (is_valid_minimap_view_pos(rpg->minimap,
        sfView_getCenter(rpg->minimap->view))) {
        sfView_zoom(rpg->minimap->view, 1.1);
        update_text_cities_size(rpg, 1.1);
    } else
        rpg->minimap->zoom /= 1.1;
}

static void move_view_minimap(rpg_t *rpg, sfVector2f diff)
{
    sfVector2f view_pos = sfView_getCenter(rpg->minimap->view);
    sfVector2f new_pos = {view_pos.x + diff.x, view_pos.y + diff.y};

    if (is_valid_minimap_view_pos(rpg->minimap, new_pos))
        sfView_move(rpg->minimap->view, diff);
}

static void event_map_keypressed(rpg_t *rpg)
{
    sfKeyCode key = rpg->event.key.code;

    if (key == sfKeyAdd)
        add_zoom_minimap(rpg);
    if (key == sfKeySubtract)
        sub_zoom_minimap(rpg);
    if (key == sfKeyUp)
        move_view_minimap(rpg, (sfVector2f){0, -100});
    if (key == sfKeyDown)
        move_view_minimap(rpg, (sfVector2f){0, 100});
    if (key == sfKeyLeft)
        move_view_minimap(rpg, (sfVector2f){-100, 0});
    if (key == sfKeyRight)
        move_view_minimap(rpg, (sfVector2f){100, 0});
    if (key == sfKeyT) {
        rpg->gamestate = GAME;
        setup_command_help_in_game(rpg);
    }
}

static bool mouse_on_minimap(rpg_t *rpg, sfVector2f mouse_pos)
{
    minimap_t *minimap = rpg->minimap;
    sfVector2f center = {WIDTH / 2, HEIGHT / 2};
    sfIntRect rect = {center.x - minimap->size / 2, center.y -
        minimap->size / 2, minimap->size, minimap->size};

    return sfIntRect_contains(&rect, mouse_pos.x, mouse_pos.y);
}

static void event_map_mousepressed_released(rpg_t *rpg)
{
    sfMouseButton button = rpg->event.mouseButton.button;
    sfVector2f mouse_pos = {rpg->event.mouseButton.x,
        rpg->event.mouseButton.y};

    if (button == sfMouseRight)
        rpg->gamestate = GAME;
    if (!mouse_on_minimap(rpg, mouse_pos) || button != sfMouseLeft) {
        rpg->minimap->is_drag = false;
        return;
    }
    if (rpg->event.type == sfEvtMouseButtonReleased)
        rpg->minimap->is_drag = false;
    if (rpg->event.type == sfEvtMouseButtonPressed) {
        rpg->minimap->is_drag = true;
        rpg->minimap->pos = (sfVector2f){rpg->event.mouseButton.x,
            rpg->event.mouseButton.y};
    }
}

static void event_map_mousemoved(rpg_t *rpg)
{
    minimap_t *minimap = rpg->minimap;
    sfVector2f view_pos;
    sfVector2f diff;
    sfVector2f new_pos;
    sfVector2f mouse_pos = {rpg->event.mouseMove.x, rpg->event.mouseMove.y};

    if (!mouse_on_minimap(rpg, mouse_pos) || !rpg->minimap->is_drag)
        return;
    view_pos = sfView_getCenter(minimap->view);
    diff = (sfVector2f){(minimap->pos.x - rpg->event.mouseMove.x) * 5,
        (minimap->pos.y - rpg->event.mouseMove.y) * 5};
    new_pos = (sfVector2f){view_pos.x + diff.x, view_pos.y + diff.y};
    if (is_valid_minimap_view_pos(minimap, new_pos)) {
        sfView_setCenter(minimap->view, new_pos);
        minimap->pos = (sfVector2f){rpg->event.mouseMove.x,
            rpg->event.mouseMove.y};
    }
    minimap->pos = (sfVector2f){rpg->event.mouseMove.x,
        rpg->event.mouseMove.y};
}

static void event_map_mousewheel(rpg_t *rpg)
{
    if (rpg->event.mouseWheelScroll.delta > 0)
        add_zoom_minimap(rpg);
    if (rpg->event.mouseWheelScroll.delta < 0)
        sub_zoom_minimap(rpg);
}

void event_map(rpg_t *rpg)
{
    if (rpg->event.type == sfEvtKeyPressed)
        return event_map_keypressed(rpg);
    if (rpg->event.type == sfEvtMouseButtonPressed ||
        rpg->event.type == sfEvtMouseButtonReleased)
        return event_map_mousepressed_released(rpg);
    if (rpg->event.type == sfEvtMouseMoved)
        return event_map_mousemoved(rpg);
    if (rpg->event.type == sfEvtMouseWheelScrolled)
        return event_map_mousewheel(rpg);
}
