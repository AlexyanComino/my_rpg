/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** display_menus
*/

#include "rpg.h"

static void display_background_menus(rpg_t *rpg)
{
    sfRenderWindow_drawSprite(
        rpg->win->window, rpg->map->ground_sprite, NULL);
    if (!sfKeyboard_isKeyPressed(sfKeyV))
        display_decors_ground(rpg, intrect_is_in_view_menu);
    sfRenderWindow_drawSprite(
        rpg->win->window, rpg->map->high_sprite, NULL);
    if (!sfKeyboard_isKeyPressed(sfKeyV))
        display_decors_high(rpg, intrect_is_in_view_menu);
}

void display_main_menu(rpg_t *rpg)
{
    button_t *tmp = rpg->main_menu->buttons;

    display_background_menus(rpg);
    display_anim_text(rpg, rpg->main_menu->title1);
    display_anim_text(rpg, rpg->main_menu->title2);
    while (tmp != NULL) {
        sfRenderWindow_drawText(rpg->win->window, tmp->shadow, NULL);
        sfRenderWindow_drawText(rpg->win->window, tmp->text, NULL);
        tmp = tmp->next;
    }
}

void display_settings(rpg_t *rpg)
{
    button_t *tmp = rpg->settings->buttons;

    display_background_menus(rpg);
    while (tmp != NULL) {
        sfRenderWindow_drawText(rpg->win->window, tmp->shadow, NULL);
        sfRenderWindow_drawText(rpg->win->window, tmp->text, NULL);
        tmp = tmp->next;
    }
    display_command_help(rpg);
}

static void draw_stats_save(rpg_t *rpg, save_button_t *tmp)
{
    sfRenderWindow_drawSprite(rpg->win->window, tmp->entity->common->
        anim->sprite, NULL);
    sfRenderWindow_drawText(rpg->win->window, tmp->hp, NULL);
    sfRenderWindow_drawText(rpg->win->window, tmp->attack, NULL);
    sfRenderWindow_drawText(rpg->win->window, tmp->defense, NULL);
    sfRenderWindow_drawText(rpg->win->window, tmp->speed, NULL);
}

static void draw_stats_sprites_save(rpg_t *rpg, save_button_t *tmp)
{
    if (rpg->win->window == NULL)
        return;
    if (tmp->pp_sprite == NULL) {
        return;
    }
    sfRenderWindow_drawSprite(rpg->win->window,
        tmp->pp_sprite, NULL);
    sfRenderWindow_drawSprite(rpg->win->window,
        tmp->hp_sprite, NULL);
    sfRenderWindow_drawSprite(rpg->win->window,
        tmp->attack_sprite, NULL);
    sfRenderWindow_drawSprite(rpg->win->window,
        tmp->defense_sprite, NULL);
    sfRenderWindow_drawSprite(rpg->win->window,
        tmp->speed_sprite, NULL);
}

void display_save_menu(rpg_t *rpg)
{
    save_button_t *tmp = rpg->save_menu->buttons;
    int i = 0;

    display_background_menus(rpg);
    for (; tmp != NULL; tmp = tmp->next) {
        if (strcmp(tmp->name, "Retour") == 0) {
            sfRenderWindow_drawText(rpg->win->window, tmp->text, NULL);
            continue;
        }
        sfRenderWindow_drawRectangleShape(rpg->win->window, tmp->rect_shape,
            NULL);
        sfRenderWindow_drawText(rpg->win->window, tmp->text, NULL);
        if (i < 3 && rpg->save[i] != NULL) {
            draw_stats_sprites_save(rpg, tmp);
            draw_stats_save(rpg, tmp);
        } else
            sfRenderWindow_drawText(rpg->win->window, tmp->new_txt, NULL);
        i++;
    }
    display_command_help(rpg);
}

static void draw_stats(rpg_t *rpg, select_button_t *tmp)
{
    sfRenderWindow_drawSprite(rpg->win->window, tmp->entity->common->
        anim->sprite, NULL);
    sfRenderWindow_drawText(rpg->win->window, tmp->text, NULL);
    sfRenderWindow_drawText(rpg->win->window, tmp->hp, NULL);
    sfRenderWindow_drawText(rpg->win->window, tmp->attack, NULL);
    sfRenderWindow_drawText(rpg->win->window, tmp->defense, NULL);
    sfRenderWindow_drawText(rpg->win->window, tmp->speed, NULL);
}

static void draw_stats_sprites(rpg_t *rpg, select_button_t *tmp)
{
    sfRenderWindow_drawSprite(rpg->win->window,
        tmp->pp_sprite, NULL);
    sfRenderWindow_drawSprite(rpg->win->window,
        tmp->hp_sprite, NULL);
    sfRenderWindow_drawSprite(rpg->win->window,
        tmp->attack_sprite, NULL);
    sfRenderWindow_drawSprite(rpg->win->window,
        tmp->defense_sprite, NULL);
    sfRenderWindow_drawSprite(rpg->win->window,
        tmp->speed_sprite, NULL);
}

void display_selector(rpg_t *rpg)
{
    select_button_t *tmp = rpg->selector->buttons;

    display_background_menus(rpg);
    for (; tmp != NULL; tmp = tmp->next) {
        if (strcmp(tmp->name, "Retour") == 0) {
            sfRenderWindow_drawText(rpg->win->window, tmp->text, NULL);
            continue;
        }
        sfRenderWindow_drawRectangleShape(rpg->win->window, tmp->rect_shape,
            NULL);
        draw_stats_sprites(rpg, tmp);
        draw_stats(rpg, tmp);
    }
    display_command_help(rpg);
}
