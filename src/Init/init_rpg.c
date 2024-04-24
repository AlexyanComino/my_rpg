/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_rpg
*/

#include "rpg.h"

static win_t *init_win(unsigned int width, unsigned int height)
{
    win_t *win = malloc(sizeof(win_t));
    sfVideoMode mode = {width, height, 32};

    win->window = sfRenderWindow_create(mode, "My_RPG", sfFullscreen, NULL);
    win->view = sfView_createFromRect((sfFloatRect){0, 0, width, height});
    sfView_setViewport(win->view, (sfFloatRect){0, 0, 1, 1});
    sfRenderWindow_setView(win->window, win->view);
    win->width = width;
    win->height = height;
    win->framerate = 60;
    win->clock = sfClock_create();
    sfRenderWindow_setFramerateLimit(win->window, win->framerate);
    return win;
}

void print_quests(quest_t *quest)
{
    quest_t *tmp = quest;

    while (tmp != NULL) {
        printf("Name: %s\n", tmp->name);
        printf("Description: %s\n", tmp->description);
        printf("Reward: %d\n", tmp->reward);
        printf("Xp: %d\n", tmp->xp);
        tmp = tmp->next;
    }
}

void print_all_quests(all_quests_t *quests)
{
    all_quests_t *tmp = quests;

    while (tmp != NULL) {
        printf("Proprietary: %s\n", tmp->proprietary);
        printf("Quests:\n");
        print_quests(tmp->quest);
        tmp = tmp->next;
    }
}

rpg_t *init_rpg(void)
{
    rpg_t *rpg = malloc(sizeof(rpg_t));

    srand(time(NULL));
    rpg->gamestate = GAME;
    rpg->win = init_win(WIDTH, HEIGHT);
    rpg->lwarrior = init_lwarrior();
    rpg->event = (sfEvent){0};
    rpg->debug = false;
    rpg->main_menu = init_menu();
    rpg->save_menu = init_save_menu();
    rpg->settings = init_settings();
    rpg->quests = init_all_quests();
    rpg->quest_text = create_text(rpg->settings->font, "", 100,
        (sfVector2f){200, 700});
    rpg->quest_desc = create_text(rpg->settings->font, "", 50,
        (sfVector2f){200, 800});
    rpg->quest_info = create_text(rpg->settings->font, "Appuie sur Entrée pour accepter", 20,
        (sfVector2f){200, 900});
    print_all_quests(rpg->quests);
    update_all(rpg);
    return rpg;
}
