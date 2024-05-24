/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** destroyRpg
*/

#include "rpg.h"

static void destroy_anim_text(anim_text_t *anim_text)
{
    sfText_destroy(anim_text->text);
    if (anim_text->has_shadow)
        sfText_destroy(anim_text->shadow);
    free(anim_text);
}

static void destroy_menu(menu_t *menu)
{
    button_t *tmp = menu->buttons;
    button_t *next = NULL;

    while (tmp) {
        next = tmp->next;
        sfText_destroy(tmp->text);
        sfRectangleShape_destroy(tmp->rect_shape);
        sfFont_destroy(tmp->font);
        free(tmp);
        tmp = next;
    }
    if (menu->title1) {
        destroy_anim_text(menu->title1);
        destroy_anim_text(menu->title2);
    }
    sfFont_destroy(menu->font);
    free(menu);
}

static void destroy_menus(rpg_t *rpg)
{
    destroy_menu(rpg->main_menu);
    destroy_menu(rpg->settings);
}

static void destroy_quests(rpg_t *rpg)
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

void destroy(rpg_t *rpg)
{
    destroy_menus(rpg);
    destroy_quests(rpg);
    destroy_ent(rpg->ent, rpg->ent_size);
    sfClock_destroy(rpg->win->clock);
    sfView_destroy(rpg->win->view);
    sfRenderWindow_destroy(rpg->win->window);
    munmap(rpg->shared_data, sizeof(shared_data_t));
    shm_unlink("/shared_memory");
    free(rpg->win);
    free(rpg);
}
