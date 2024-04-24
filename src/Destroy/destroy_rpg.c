/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** destroyRpg
*/

#include "rpg.h"


static void destroy_menu(menu_t *menu)
{
    button_t *tmp = menu->buttons;
    button_t *next = NULL;

    sfTexture_destroy(menu->background_texture);
    sfSprite_destroy(menu->background);
    if (menu->myclock != NULL)
    sfClock_destroy(menu->myclock->clock);
    while (tmp) {
        next = tmp->next;
        sfText_destroy(tmp->text);
        sfRectangleShape_destroy(tmp->rect_shape);
        sfFont_destroy(tmp->font);
        free(tmp);
        tmp = next;
    }
    if (menu->text != NULL)
        sfText_destroy(menu->text);
    sfFont_destroy(menu->font);
    free(menu);
}

void destroy_menus(rpg_t *rpg)
{
    destroy_menu(rpg->main_menu);
    destroy_menu(rpg->save_menu);
    destroy_menu(rpg->settings);
}

void destroy_quests(rpg_t *rpg)
{
    all_quests_t *tmp = rpg->quests;
    all_quests_t *next = NULL;
    quest_t *quest = NULL;
    quest_t *next_quest = NULL;

    while (tmp) {
        next = tmp->next;
        free(tmp->proprietary);
        quest = tmp->quest;
        while (quest) {
            next_quest = quest->next;
            free(quest->name);
            free(quest->description);
            free(quest);
            quest = next_quest;
        }
        free(tmp);
        tmp = next;
    }
}

static void destroy_mark(mark_t *mark)
{
    sfTexture_destroy(mark->texture);
    sfSprite_destroy(mark->sprite);
    sfClock_destroy(mark->myclock->clock);
    free(mark->myclock);
    sfCircleShape_destroy(mark->circle);
    free(mark);
}

void destroy_warrior(warrior_t *warrior)
{
    free(warrior->name);
    sfTexture_destroy(warrior->texture);
    sfSprite_destroy(warrior->sprite);
    sfRectangleShape_destroy(warrior->zones->rect_hitbox);
    sfRectangleShape_destroy(warrior->zones->rect_hitbox_attack);
    sfCircleShape_destroy(warrior->zones->circle_reset);
    free(warrior->zones);
    free(warrior->attributes);
    sfTexture_destroy(warrior->death->texture_dead);
    sfSprite_destroy(warrior->death->sprite_dead);
    sfClock_destroy(warrior->death->clock_dead->clock);
    free(warrior->death->clock_dead);
    free(warrior->death);
    destroy_mark(warrior->exclam);
    destroy_mark(warrior->inter);
    sfClock_destroy(warrior->myclock->clock);
    free(warrior->myclock);
    free(warrior);
}

void destroy_warriors(lwarrior_t *lwarrior)
{
    lwarrior_t *tmp = lwarrior;
    lwarrior_t *next = NULL;

    while (tmp) {
        next = tmp->next;
        destroy_warrior(tmp->warrior);
        free(tmp);
        tmp = next;
    }
}

void destroy_rpg(rpg_t *rpg)
{
    destroy_menus(rpg);
    destroy_quests(rpg);
    sfText_destroy(rpg->quest_text);
    sfText_destroy(rpg->quest_desc);
    sfText_destroy(rpg->quest_info);
    destroy_warriors(rpg->lwarrior);
    sfClock_destroy(rpg->win->clock);
    sfView_destroy(rpg->win->view);
    sfRenderWindow_destroy(rpg->win->window);
    free(rpg->win);
    free(rpg);
}
