/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** select_button
*/

#include "rpg.h"

bool is_s_button_clicked(struct save_button_s *button, rpg_t *rpg)
{
    sfFloatRect rect_bounds = sfRectangleShape_getGlobalBounds(
        button->rect_shape);

    if (rpg->event.type == sfEvtMouseButtonPressed) {
        if (sfFloatRect_contains(&rect_bounds, rpg->win->mouse_pos.x,
            rpg->win->mouse_pos.y)) {
            play_music(rpg->sounds->click, 100 * rpg->volume);
            button->state = CLICKED;
            return true;
        }
    }
    button->state = NOTHING;
    return false;
}

bool is_s_button_hovered(struct save_button_s *button, rpg_t *rpg)
{
    sfFloatRect rect_bounds = sfRectangleShape_getGlobalBounds(
        button->rect_shape);

    if (button->state == CLICKED || button->state == RELEASED) {
        return true;
    }
    if (sfFloatRect_contains(&rect_bounds, rpg->win->mouse_pos.x,
        rpg->win->mouse_pos.y)) {
        button->state = HOVERED;
        return true;
    } else {
        button->state = NOTHING;
        return false;
    }
}

bool is_s_button_released(struct save_button_s *button, rpg_t *rpg)
{
    sfFloatRect rect_bounds = sfRectangleShape_getGlobalBounds(
        button->rect_shape);

    if (rpg->event.type == sfEvtMouseButtonReleased) {
        if (sfFloatRect_contains(&rect_bounds, rpg->win->mouse_pos.x,
            rpg->win->mouse_pos.y)) {
            button->state = RELEASED;
            return true;
        }
    }
    button->state = NOTHING;
    return false;
}
