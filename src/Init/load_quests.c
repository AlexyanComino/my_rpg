/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** load_quests
*/

#include "rpg.h"

int load_quest_name(FILE *file, quest_t *tmp, char *c)
{
    *c = 0;
    tmp->name = "";
    while (*c != '+' && *c != '`' && *c != '|') {
        fread(c, sizeof(char), 1, file);
        if (*c == '+' || *c == '|')
            break;
        tmp->name = my_strcatdup(tmp->name, *c);
    }
    if (*c == '|' || *c == '`')
        return 1;
    return 0;
}

void load_quest_description(FILE *file, quest_t *tmp, char *c)
{
    *c = 0;
    tmp->description = "";
    while (*c != '+' && *c != '`') {
        fread(c, sizeof(char), 1, file);
        if (*c == '+')
            break;
        tmp->description = my_strcatdup(tmp->description, *c);
    }
}

void load_quest_objective(FILE *file, quest_t *tmp, char *c)
{
    *c = 0;
    tmp->objective = "";
    while (*c != '+' && *c != '`') {
        fread(c, sizeof(char), 1, file);
        if (*c == '+')
            break;
        tmp->objective = my_strcatdup(tmp->objective, *c);
    }
}

int load_proprietary(FILE *file, all_quests_t *tmp, char *c)
{
    *c = 0;
    tmp->quest = malloc(sizeof(quest_t));
    tmp->proprietary = "";
    while (*c != '+' && *c != '`') {
        fread(c, sizeof(char), 1, file);
        if (*c == '+')
            break;
        tmp->proprietary = my_strcatdup(tmp->proprietary, *c);
    }
    if (*c == '`')
        return 1;
    return 0;
}
