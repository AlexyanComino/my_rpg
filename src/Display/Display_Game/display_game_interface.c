/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** display_game_interface
*/

#include "rpg.h"

static void display_restricted_text(rpg_t *rpg)
{
    restricted_t *restricted = rpg->interface->restricted;
    entity_t *player = get_player(rpg);

    if (!is_alive(player))
        return;
    sfRenderWindow_drawSprite(rpg->win->window, restricted->sprite, NULL);
}

static void display_health_bar_interface(rpg_t *rpg)
{
    display_round_rectangle(rpg->win->window,
        rpg->interface->health_bar->back);
    display_round_rectangle(rpg->win->window,
        rpg->interface->health_bar->front);
}

static void display_popup_item(rpg_t *rpg)
{
    popup_item_t *popup_item = rpg->interface->popup_item;

    if (popup_item->display != 0) {
        sfRenderWindow_drawSprite(rpg->win->window, popup_item->back_sprite,
            NULL);
        sfRenderWindow_drawSprite(rpg->win->window, popup_item->light_sprite,
            NULL);
        sfRenderWindow_drawSprite(rpg->win->window,
            popup_item->item_anim->sprite, NULL);
        sfRenderWindow_drawText(rpg->win->window,
            popup_item->title->text, NULL);
        sfRenderWindow_drawText(rpg->win->window, popup_item->item_description,
            NULL);
        sfRenderWindow_drawText(rpg->win->window, popup_item->rarity, NULL);
        sfRenderWindow_drawText(rpg->win->window, popup_item->skip_text, NULL);
    }
}

static void display_player_infos(rpg_t *rpg)
{
    player_infos_t *player_infos = rpg->interface->player_infos;

    sfRenderWindow_drawText(rpg->win->window, player_infos->player_text, NULL);
}

void display_command_help(rpg_t *rpg)
{
    command_list_t *tmp = rpg->interface->command_list;

    while (tmp != NULL) {
        sfRenderWindow_drawText(rpg->win->window, tmp->action, NULL);
        sfRenderWindow_drawSprite(rpg->win->window, tmp->sprite, NULL);
        tmp = tmp->next;
    }
}

void display_game_interface(rpg_t *rpg)
{
    display_restricted_text(rpg);
    display_health_bar_interface(rpg);
    display_popup_item(rpg);
    display_player_infos(rpg);
    display_command_help(rpg);
}
