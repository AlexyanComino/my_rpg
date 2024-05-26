/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** move_view_menu
*/

#include "rpg.h"

static void move_menu(menu_t *menu, sfVector2f move)
{
    button_t *tmp = menu->buttons;

    if (menu->title1 != NULL && menu->title2 != NULL) {
        sfText_move(menu->title1->text, move);
        sfText_move(menu->title1->shadow, move);
        sfText_move(menu->title2->text, move);
        sfText_move(menu->title2->shadow, move);
    }
    while (tmp != NULL) {
        sfText_move(tmp->text, move);
        sfText_move(tmp->shadow, move);
        tmp = tmp->next;
    }
}

static void move_save_menu(rpg_t *rpg, sfVector2f move)
{
    save_button_t *tmp = rpg->save_menu->buttons;

    while (tmp != NULL) {
        sfText_move(tmp->text, move);
        sfRectangleShape_move(tmp->rect_shape, move);
        sfText_move(tmp->new_txt, move);
        tmp = tmp->next;
    }
}

static void move_select_menu(rpg_t *rpg, sfVector2f move)
{
    select_button_t *tmp = rpg->selector->buttons;

    while (tmp != NULL) {
        sfText_move(tmp->text, move);
        sfRectangleShape_move(tmp->rect_shape, move);
        if (tmp->entity != NULL) {
            sfSprite_move(tmp->entity->common->anim->sprite, move);
            sfText_move(tmp->hp, move);
            sfText_move(tmp->attack, move);
            sfText_move(tmp->defense, move);
            sfText_move(tmp->speed, move);
            sfSprite_move(tmp->pp_sprite, move);
            sfSprite_move(tmp->hp_sprite, move);
            sfSprite_move(tmp->attack_sprite, move);
            sfSprite_move(tmp->defense_sprite, move);
            sfSprite_move(tmp->speed_sprite, move);
        }
        tmp = tmp->next;
    }
}

static void move_command_help(rpg_t *rpg, sfVector2f move)
{
    command_list_t *tmp = rpg->interface->command_list;

    while (tmp != NULL) {
        sfSprite_move(tmp->sprite, move);
        sfText_move(tmp->action, move);
        tmp = tmp->next;
    }
}

static void move_menus(rpg_t *rpg)
{
    sfVector2f move = (sfVector2f){rpg->win->view_menu_move.x * rpg->win->dt,
        rpg->win->view_menu_move.y * rpg->win->dt};

    move_menu(rpg->main_menu, move);
    move_menu(rpg->settings, move);
    move_save_menu(rpg, move);
    move_select_menu(rpg, move);
    move_command_help(rpg, move);
    sfSprite_move(rpg->transition->anim->sprite, move);
}

void move_view_menu(rpg_t *rpg)
{
    rpg->win->view_pos.x += rpg->win->view_menu_move.x * rpg->win->dt;
    if (rpg->win->view_pos.x < 4300) {
        rpg->win->view_pos.x = 4300;
        rpg->win->view_menu_move.x *= -1;
    } else if (rpg->win->view_pos.x > 5400) {
        rpg->win->view_pos.x = 5400;
        rpg->win->view_menu_move.x *= -1;
    }
    sfView_setCenter(rpg->win->view_menu, rpg->win->view_pos);
    move_menus(rpg);
    sfRenderWindow_setView(rpg->win->window, rpg->win->view_menu);
}
