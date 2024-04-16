/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** button
*/

#include "rpg.h"

bool is_button_clicked(struct button_s *button, sfMouseButtonEvent *event)
{
    sfVector2f mouse_pos = {(float) event->x, (float) event->y};
    sfFloatRect rect_bounds = sfSprite_getGlobalBounds(button->sprite);

    if (event->type == sfEvtMouseButtonPressed) {
        if (sfFloatRect_contains(&rect_bounds, mouse_pos.x, mouse_pos.y)) {
            button->state = CLICKED;
            return true;
        }
    }
    button->state = NONE;
    return false;
}

bool is_button_hovered(struct button_s *button, sfMouseMoveEvent *event)
{
    sfVector2f mouse_pos = {(float) event->x, (float) event->y};
    sfFloatRect rect_bounds = sfSprite_getGlobalBounds(button->sprite);

    if (button->state == CLICKED || button->state == RELEASED) {
        return true;
    }
    if (sfFloatRect_contains(&rect_bounds, mouse_pos.x, mouse_pos.y)) {
        button->state = HOVERED;
        return true;
    } else {
        button->state = NONE;
        return false;
    }
}

bool is_button_released(struct button_s *button, sfMouseButtonEvent *event)
{
    sfVector2f mouse_pos = {(float) event->x, (float) event->y};
    sfFloatRect rect_bounds = sfSprite_getGlobalBounds(button->sprite);

    if (event->type == sfEvtMouseButtonReleased) {
        if (sfFloatRect_contains(&rect_bounds, mouse_pos.x, mouse_pos.y)) {
            button->state = RELEASED;
            return true;
        }
    }
    button->state = NONE;
    return false;
}