/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** event
*/

#include "rpg.h"

static void event_pause(rpg_t *rpg)
{
    menu_button_event(rpg, rpg->pause_menu->buttons);
    if (rpg->event.key.type == sfEvtKeyPressed && rpg->event.key.code ==
        sfKeyEscape) {
        rpg->gamestate = GAME;
        setup_command_help_in_game(rpg);
    }
}

static void event_states2(rpg_t *rpg)
{
    if (rpg->gamestate == GAME)
        event_game(rpg);
    if (rpg->gamestate == GAME || rpg->gamestate == INVENTORY)
        manage_evt_inv(rpg->event, rpg);
    if (rpg->gamestate == GAME || rpg->gamestate == SKILL_TREE)
        manage_skill_tree(rpg);
}

static void event_states(rpg_t *rpg)
{
    if (rpg->gamestate == LOADING)
        return event_loading(rpg);
    if (rpg->gamestate == MAP)
        return event_map(rpg);
    if (rpg->gamestate == SELECTOR)
        return slct_button_event(rpg, rpg->selector->buttons);
    if (rpg->gamestate == SAVE_MENU)
        return save_button_event(rpg, rpg->save_menu->buttons);
    if (rpg->gamestate == SETTINGS)
        return menu_button_event(rpg, rpg->settings->buttons);
    if (rpg->gamestate == MAIN_MENU)
        return menu_button_event(rpg, rpg->main_menu->buttons);
    if (rpg->gamestate == END)
        return menu_button_event(rpg, rpg->end_menu->buttons);
    if (rpg->gamestate == PAUSE)
        return event_pause(rpg);
    event_states2(rpg);
}

static sfVector2f get_view_pos(rpg_t *rpg)
{
    if (rpg->gamestate == GAME || rpg->gamestate == INVENTORY ||
        rpg->gamestate == MAP || rpg->gamestate == PAUSE ||
        rpg->gamestate == SKILL_TREE)
        return get_player(rpg)->common->pos;
    else if (rpg->gamestate == END)
        return (sfVector2f){WIDTH / 2, HEIGHT / 2};
    else
        return rpg->win->view_pos;
    return (sfVector2f){0, 0};
}

static void update_mouse_pos(rpg_t *rpg)
{
    sfVector2f old_mouse_pos = {rpg->event.mouseMove.x, rpg->event.mouseMove.y};
    sfVector2f view_pos = get_view_pos(rpg);
    sfVector2u window_size = sfRenderWindow_getSize(rpg->win->window);

    rpg->win->mouse_pos = (sfVector2f){
        (float)view_pos.x - (float)WIDTH / 2 * rpg->win->zoom +
            (float)old_mouse_pos.x / ((float)window_size.x /
            (float)WIDTH) * rpg->win->zoom,
        (float)view_pos.y - (float)HEIGHT / 2 * rpg->win->zoom +
            (float)old_mouse_pos.y / ((float)window_size.y /
            (float)HEIGHT) * rpg->win->zoom};
    sfSprite_setPosition(rpg->mouse->sprite, rpg->win->mouse_pos);
}

static void move_cursor_joystick(rpg_t *rpg)
{
    float Xaxis = sfJoystick_getAxisPosition(0, sfJoystickY);
    float Yaxis = sfJoystick_getAxisPosition(0, sfJoystickX);
    rpg->dx = Xaxis * 0.2;
    rpg->dy = Yaxis * 0.2;
}

static void joystick_move(rpg_t *rpg)
{
    if (rpg->gamestate == MAIN_MENU || rpg->gamestate == SETTINGS ||
        rpg->gamestate == SELECTOR || rpg->gamestate == SAVE_MENU ||
        rpg->gamestate == PAUSE || rpg->gamestate == END ||
        rpg->gamestate == INVENTORY || rpg->gamestate == SKILL_TREE) {
        move_cursor_joystick(rpg);
    } else {
        rpg->win->mouse_pos = get_player(rpg)->common->pos;
        sfSprite_setPosition(rpg->mouse->sprite, rpg->win->mouse_pos);
    }
}

void event(rpg_t *rpg)
{
    sfTime elapsed_time = sfClock_getElapsedTime(rpg->win->clock);
    char *str = malloc(sizeof(char) * 150);

    rpg->win->dt = sfTime_asSeconds(elapsed_time);
    sfClock_restart(rpg->win->clock);
    while (sfRenderWindow_pollEvent(rpg->win->window, &rpg->event)) {
        sprintf(str, "Joystick button: %d", rpg->event.joystickButton.button);
        sfText_setString(rpg->txt, str);
        if (rpg->event.joystickButton.button == 6)
            sfRenderWindow_close(rpg->win->window);
        if (rpg->event.type == sfEvtJoystickMoved) {
            joystick_move(rpg);
        }
        if (rpg->event.type == sfEvtMouseMoved)
            update_mouse_pos(rpg);
        if ((rpg->event.type == sfEvtMouseButtonPressed &&
            rpg->event.mouseButton.button == sfMouseRight))
            printf("Mouse pos: %d;%d\n", (int)rpg->win->mouse_pos.x,
            (int)rpg->win->mouse_pos.y);
        if (rpg->event.type == sfEvtClosed)
            sfRenderWindow_close(rpg->win->window);
        event_states(rpg);
    }
    if (rpg->gamestate == GAME)
        player_move_event(rpg);
}
