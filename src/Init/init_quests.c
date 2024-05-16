/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_quests
*/

#include "rpg.h"

static quest_type_t get_type(char *type)
{
    if (type[0] == 'K')
        return KILL;
    if (type[0] == 'T')
        return TALK;
    if (type[0] == 'G')
        return GATHER;
    if (type[0] == 'M')
        return MOVE;
    return -1;
}

static quest_t *init_quest(char **infos)
{
    quest_t *quest = malloc(sizeof(quest_t));

    quest->name = strdup(infos[1]);
    quest->description = strdup(infos[2]);
    quest->dialog = init_dialog(infos[3]);
    quest->reward = atoi(infos[4]);
    quest->xp = atoi(infos[5]);
    quest->type = get_type(infos[6]);
    quest->objective = strdup(infos[7]);
    quest->is_done = false;
    quest->is_active = false;
    quest->is_displayed = false;
    quest->is_last = strcmp(infos[8], "true") == 0 ? true : false;
    quest->next = NULL;
    return quest;
}

static quest_t *add_quest(quest_t *quest, char **infos)
{
    quest_t *new = init_quest(infos);
    quest_t *tmp = quest;

    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
    return quest;
}

static all_quests_t *add_node(all_quests_t *quests, char **infos)
{
    all_quests_t *new = malloc(sizeof(all_quests_t));
    all_quests_t *tmp = quests;

    new->proprietary = strdup(infos[0]);
    new->quest = init_quest(infos);
    new->entity = NULL;
    new->next = NULL;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
    return quests;
}

static all_quests_t *add_quests(all_quests_t *quests, char **infos,
    bool *end_loop)
{
    all_quests_t *tmp = quests;

    *end_loop = false;
    while (tmp != NULL) {
        if (strcmp(tmp->proprietary, infos[0]) == 0) {
            add_quest(tmp->quest, infos);
            *end_loop = true;
        }
        tmp = tmp->next;
    }
    if (*end_loop == true) {
        free_array(infos);
        return quests;
    }
    quests = add_node(quests, infos);
    return quests;
}

static sfRectangleShape *create_rect_shape(sfVector2f size, sfVector2f pos,
    sfColor color)
{
    sfRectangleShape *rect = sfRectangleShape_create();

    sfRectangleShape_setSize(rect, size);
    sfRectangleShape_setPosition(rect, pos);
    sfRectangleShape_setFillColor(rect, color);
    return rect;
}

static void init_quest_header(rpg_t *rpg)
{
    rpg->quest_header = malloc(sizeof(quest_header_t));
    rpg->quest_header->font = sfFont_createFromFile(
        "assets/fonts/HyliaSerifBeta-Regular.otf");
    rpg->quest_header->text = create_text(rpg->quest_header->font, "", 75,
        (sfVector2f){200, 700});
    sfText_setFillColor(rpg->quest_header->text, sfColor_fromRGBA(
        255, 255, 255, 0));
    rpg->quest_header->done = create_text(rpg->quest_header->font, "Complete",
        60, (sfVector2f){300, 750});
    sfText_setFillColor(rpg->quest_header->done, sfColor_fromRGBA(
        254, 250, 190, 0));
    rpg->quest_header->rect = create_rect_shape((sfVector2f){1920, 200},
        (sfVector2f){0, 700}, sfColor_fromRGBA(0, 0, 0, 0));
    rpg->quest_header->rect2 = create_rect_shape((sfVector2f){1920, 180},
        (sfVector2f){0, 700}, sfColor_fromRGBA(0, 0, 0, 0));
    rpg->quest_header->state = Q_HIDDEN;
    rpg->quest_header->myclock = NULL;
    rpg->quests = NULL;
}

void init_all_quests(rpg_t *rpg)
{
    char **lines = file_to_array(".quests.csv");
    char **infos = NULL;
    bool end_loop = false;

    init_quest_header(rpg);
    for (int i = 0; lines[i] != NULL; i++) {
        infos = split_string(lines[i], ";");
        if (rpg->quests == NULL) {
            rpg->quests = malloc(sizeof(all_quests_t));
            rpg->quests->proprietary = strdup(infos[0]);
            rpg->quests->quest = init_quest(infos);
            rpg->quests->entity = NULL;
            rpg->quests->next = NULL;
        } else
            add_quests(rpg->quests, infos, &end_loop);
        if (end_loop == true)
            continue;
        free_array(infos);
    }
    free_array(lines);
}
