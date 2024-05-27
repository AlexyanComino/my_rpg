/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** button
*/

#include "rpg.h"

bool is_button_clicked(struct button_s *button, rpg_t *rpg)
{
    sfFloatRect rect_bounds = sfText_getGlobalBounds(button->text);

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

bool is_button_hovered(struct button_s *button, rpg_t *rpg)
{
    sfFloatRect rect_bounds = sfText_getGlobalBounds(button->text);

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

bool is_button_released(struct button_s *button, rpg_t *rpg)
{
    sfFloatRect rect_bounds = sfText_getGlobalBounds(button->text);

    if (rpg->event.type == sfEvtMouseButtonReleased) {
        if (sfFloatRect_contains(&rect_bounds, rpg->win->mouse_pos.x,
            rpg->win->mouse_pos.y)) {
            button->state = RELEASED;
            return true;
        }
    }
    return false;
}
