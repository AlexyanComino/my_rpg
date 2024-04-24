/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** display_warriors
*/

#include "rpg.h"

static void draw_circles_hitbox(rpg_t *rpg, warrior_t *warrior)
{
    sfRenderWindow_drawCircleShape(rpg->win->window,
        warrior->exclam->circle, NULL);
    sfRenderWindow_drawCircleShape(rpg->win->window,
        warrior->inter->circle, NULL);
    sfRenderWindow_drawCircleShape(rpg->win->window,
        warrior->zones->circle_max_detection, NULL);
}

static void display_damage_texts(rpg_t *rpg, warrior_t *warrior)
{
    damage_text_t *tmp = warrior->damage_texts;

    while (tmp) {
        if (tmp->effect != NULL) {
            sfRenderWindow_drawSprite(rpg->win->window,
                tmp->effect->sprite, NULL);
        }
        sfRenderWindow_drawText(rpg->win->window, tmp->text_shadow, NULL);
        sfRenderWindow_drawText(rpg->win->window, tmp->text, NULL);
        tmp = tmp->next;
    }
}

static void display_pattern_pos_shapes(rpg_t *rpg, warrior_t *warrior)
{
    int i = 0;

    while (warrior->base->pattern_pos[i].x != -1 &&
        warrior->base->pattern_pos[i].y != -1) {
        sfRenderWindow_drawCircleShape(rpg->win->window,
            warrior->base->pattern_pos_shapes[i], NULL);
        i++;
    }
}

static void display_debug_warrior(rpg_t *rpg, warrior_t *player,
    warrior_t *warrior)
{
    sfRenderWindow_drawRectangleShape(rpg->win->window,
        warrior->zones->rect_hitbox, NULL);
    sfRenderWindow_drawRectangleShape(rpg->win->window,
        warrior->zones->rect_hitbox_attack, NULL);
    if (warrior != player)
        draw_circles_hitbox(rpg, warrior);
    if (warrior->base != NULL) {
        sfRenderWindow_drawRectangleShape(rpg->win->window,
        warrior->base->shape, NULL);
        display_pattern_pos_shapes(rpg, warrior);
    }
}

static void display_alive_warrior(rpg_t *rpg, warrior_t *warrior)
{
    warrior_t *player = rpg->lwarrior->warrior;

    sfRenderWindow_drawSprite(rpg->win->window, warrior->sprite, NULL);
    if (warrior->exclam->is_display)
        sfRenderWindow_drawSprite(rpg->win->window, warrior->exclam->sprite,
            NULL);
    if (warrior->inter->is_display)
        sfRenderWindow_drawSprite(rpg->win->window, warrior->inter->sprite,
            NULL);
    if (rpg->debug)
        display_debug_warrior(rpg, player, warrior);
}

static void display_warrior(rpg_t *rpg, warrior_t *warrior)
{
    if (warrior->state == DEAD)
        sfRenderWindow_drawSprite(rpg->win->window,
        warrior->death->sprite_dead, NULL);
    else {
        display_alive_warrior(rpg, warrior);
    }
}

void display_warriors(rpg_t *rpg)
{
    lwarrior_t *tmp = rpg->lwarrior->next;

    while (tmp) {
        if (tmp->warrior->state != RIEN)
            display_warrior(rpg, tmp->warrior);
        tmp = tmp->next;
    }
    display_warrior(rpg, rpg->lwarrior->warrior);
    tmp = rpg->lwarrior->next;
    while (tmp) {
        if (tmp->warrior->state != RIEN) {
            display_damage_texts(rpg, tmp->warrior);
        }
        tmp = tmp->next;
    }
    display_damage_texts(rpg, rpg->lwarrior->warrior);
}
