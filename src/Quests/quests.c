/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** quests
*/

#include "rpg.h"

static void free_array(char **array)
{
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}

static char **file_to_tab(char *path)
{
    FILE *file = fopen(path, "r");
    char *line = NULL;
    size_t len = 0;
    char **tab = NULL;
    int i = 0;

    if (file == NULL)
        return NULL;
    while (getline(&line, &len, file) != -1)
        i++;
    tab = malloc(sizeof(char *) * (i + 1));
    fseek(file, 0, SEEK_SET);
    i = 0;
    while (getline(&line, &len, file) != -1) {
        tab[i] = strdup(line);
        i++;
    }
    tab[i] = NULL;
    fclose(file);
    return tab;
}

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

quest_t *init_quest(char **infos)
{
    quest_t *quest = malloc(sizeof(quest_t));

    quest->name = strdup(infos[1]);
    quest->description = strdup(infos[2]);
    quest->reward = atoi(infos[3]);
    quest->xp = atoi(infos[4]);
    quest->type = get_type(infos[5]);
    quest->objective = strdup(infos[6]);
    quest->is_done = false;
    quest->is_active = false;
    quest->is_displayed = false;
    quest->next = NULL;
    return quest;
}

quest_t *add_quest(quest_t *quest, char **infos)
{
    quest_t *new = init_quest(infos);
    quest_t *tmp = quest;

    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
    return quest;
}

all_quests_t *add_node(all_quests_t *quests, char **infos)
{
    all_quests_t *new = malloc(sizeof(all_quests_t));
    all_quests_t *tmp = quests;

    new->proprietary = strdup(infos[0]);
    new->quest = init_quest(infos);
    new->warrior = NULL;
    new->next = NULL;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
    return quests;
}

all_quests_t *add_quests(all_quests_t *quests, char **infos, bool *end_loop)
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

all_quests_t *init_all_quests(void)
{
    char **lines = file_to_tab(".quests.csv");
    char **infos = NULL;
    all_quests_t *quests = NULL;
    bool end_loop = false;

    for (int i = 0; lines[i] != NULL; i++) {
        infos = split_string(lines[i], ";");
        if (quests == NULL) {
            quests = malloc(sizeof(all_quests_t));
            quests->proprietary = strdup(infos[0]);
            quests->quest = init_quest(infos);
            quests->warrior = NULL;
            quests->next = NULL;
        } else
            add_quests(quests, infos, &end_loop);
        if (end_loop == true)
            continue;
        free_array(infos);
    }
    free_array(lines);
    return quests;
}
