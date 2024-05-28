/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** actions2
*/

#include "rpg.h"

static void edit_quests_status(rpg_t *rpg)
{
    quest_t *tmp = NULL;
    quest_t *tmp2 = NULL;

    for (all_quests_t *quests = rpg->quests; quests; quests = quests->next) {
        tmp = quests->quest;
        tmp2 = rpg->save[rpg->save_index]->quests->quest;
        for (; tmp; tmp = tmp->next) {
            tmp->is_active = tmp2->is_active;
            tmp->is_done = tmp2->is_done;
            tmp->is_displayed = tmp2->is_displayed;
            tmp->is_last = tmp2->is_last;
            tmp2 = tmp2->next;
        }
        rpg->save[rpg->save_index]->quests =
            rpg->save[rpg->save_index]->quests->next;
    }
}

static char *get_player_infos(rpg_t *rpg)
{
    char *type[] = {"W;Player;B", "P;Player;B", "TO;Player;B",
        "TN;Player;B", "A;Player;B", NULL};
    char *str = type[rpg->save[rpg->save_index]->type];
    char *str2 = malloc(sizeof(char) * strlen(str) + 100);

    sprintf(str2, "%s;%d;%d;S;1;0;0;0;%u;%u;%u;%u;0;", str,
        (int)rpg->save[rpg->save_index]->pos.x,
        (int)rpg->save[rpg->save_index]->pos.y,
        rpg->save[rpg->save_index]->attributes->max_health,
        rpg->save[rpg->save_index]->attributes->attack,
        rpg->save[rpg->save_index]->attributes->defense,
        rpg->save[rpg->save_index]->attributes->speed);
    if (rpg->save[rpg->save_index]->type == 1)
        str2 = my_strcatdup2(str2, "N;0;0;R;0;0;0;");
    else
        str2 = my_strcatdup2(str2, "0");
    return str2;
}

static void add_player(rpg_t *rpg, char **infos)
{
    rpg->ent[rpg->ent_size] = init_entity(infos);
    rpg->ent[rpg->ent_size]->common->faction = BLUE_TEAM;
    rpg->ent[rpg->ent_size]->common->faction_origin = BLUE_TEAM;
    rpg->player_index = rpg->ent_size;
    rpg->inventory->player_status =
        init_player_status(infos, rpg->ent[rpg->ent_size]->common->attributes);
    create_slot_inventory(rpg, rpg->inventory->size);
    sfSprite_setScale(rpg->inventory->player_status->player->common->
        anim->sprite, (sfVector2f){1.7, 1.7});
    update_interface_pos(rpg, rpg->ent[rpg->ent_size],
        rpg->ent[rpg->ent_size]->common->pos);
    rpg->ent[rpg->ent_size]->common->attributes =
        rpg->save[rpg->save_index]->attributes;
    rpg->ent[rpg->ent_size]->common->pos = rpg->save[rpg->save_index]->pos;
    rpg->ent[rpg->ent_size]->type = rpg->save[rpg->save_index]->type;
    rpg->ent_size++;
}

static void create_player(rpg_t *rpg, int i)
{
    char *str = strdup(get_player_infos(rpg));
    char **infos = split_string(str, ";");

    add_player(rpg, infos);
    for (; rpg->save[i]->stuff && strlen(rpg->save[i]->stuff->name) > 0;
        rpg->save[i]->stuff = rpg->save[i]->stuff->next) {
        add_stuff_from_type(rpg, rpg->save[i]->stuff->name,
            rpg->save[i]->stuff->type);
    }
    for (; rpg->save[i]->slot; rpg->save[i]->slot =
        rpg->save[i]->slot->next) {
        if (strlen(rpg->save[i]->slot->name) > 0) {
            add_item_from_type(rpg, rpg->save[i]->slot->name,
                rpg->save[i]->slot->type);
        }
    }
}

static void join_threads(rpg_t *rpg)
{
    pthread_join(rpg->thread2, NULL);
    if (rpg->shared_data2->loaded) {
        rpg->ent = rpg->shared_data2->entities;
        rpg->ent_size = rpg->shared_data2->nb_entities;
    }
}

void load_save1(rpg_t *rpg)
{
    rpg->save_index = 0;
    if (rpg->save[0] == NULL) {
        selector(rpg);
        return;
    }
    edit_quests_status(rpg);
    join_threads(rpg);
    create_player(rpg, 0);
    start(rpg);
}

void load_save2(rpg_t *rpg)
{
    rpg->save_index = 1;
    if (rpg->save[1] == NULL) {
        selector(rpg);
        return;
    }
    edit_quests_status(rpg);
    join_threads(rpg);
    create_player(rpg, 1);
    start(rpg);
}

void load_save3(rpg_t *rpg)
{
    rpg->save_index = 2;
    if (rpg->save[2] == NULL) {
        selector(rpg);
        return;
    }
    edit_quests_status(rpg);
    join_threads(rpg);
    create_player(rpg, 2);
    start(rpg);
}

void selector(rpg_t *rpg)
{
    rpg->gamestate = SELECTOR;
    setup_command_help_menu(rpg);
}

void change_fps(rpg_t *rpg)
{
    char *str = malloc(sizeof(char) * 10);

    switch (rpg->win->framerate) {
    case 30:
        rpg->win->framerate = 60;
        break;
    case 60:
        rpg->win->framerate = 120;
        break;
    case 120:
        rpg->win->framerate = 30;
        break;
    }
    sfRenderWindow_setFramerateLimit(rpg->win->window, rpg->win->framerate);
    sprintf(str, "FPS: %d", rpg->win->framerate);
    sfText_setString(rpg->settings->buttons->next->text, str);
}
