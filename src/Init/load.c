/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** load
*/

#include "rpg.h"

static int load_slot_name(FILE *file, slot_t *tmp, char *c)
{
    *c = 0;
    tmp->next = malloc(sizeof(slot_t));
    tmp->name = "";
    while (*c != '~' && *c != '#') {
        fread(c, sizeof(char), 1, file);
        if (*c == '~' || *c == '#')
            break;
        tmp->name = my_strcatdup(tmp->name, *c);
    }
    if (*c == '#')
        return 1;
    return 0;
}

static void load_slots(FILE *file, slot_t *tmp)
{
    char c = 0;

    while (c != '#') {
        if (load_slot_name(file, tmp, &c) == 1)
            break;
        fread(&tmp->type, sizeof(int), 1, file);
        tmp = tmp->next;
    }
}

static int load_stuff_name(slot_t *tmp2, FILE *file, char *c)
{
    *c = 0;
    tmp2->next = malloc(sizeof(slot_t));
    tmp2->name = "";
    while (*c != '~' && *c != '`') {
        fread(c, sizeof(char), 1, file);
        if (*c == '~' || *c == '`')
            break;
        tmp2->name = my_strcatdup(tmp2->name, *c);
    }
    if (*c == '`')
        return 1;
    return 0;
}

static void load_stuff(FILE *file, slot_t *tmp2)
{
    char c = 0;

    while (c != '`') {
        load_stuff_name(tmp2, file, &c);
        fread(&tmp2->type, sizeof(int), 1, file);
        if (strcmp(tmp2->name, "") != 0)
        tmp2 = tmp2->next;
    }
}

static int load_dialog_txt(FILE *file, dialog_t *tmp, char *c)
{
    *c = 0;
    tmp->txt = "";
    while (*c != '~' && *c != '#') {
        fread(c, sizeof(char), 1, file);
        if (*c == '~' || *c == '#')
            break;
        tmp->txt = my_strcatdup(tmp->txt, *c);
    }
    if (*c == '#')
        return 1;
    return 0;
}

static void load_dialog(quest_t *quest, FILE *file)
{
    char c = 0;
    dialog_t *tmp = malloc(sizeof(dialog_t));

    quest->dialog = tmp;
    while (c != '#') {
        if (load_dialog_txt(file, tmp, &c) == 1)
            break;
        tmp->next = malloc(sizeof(dialog_t));
        tmp = tmp->next;
    }
    tmp->next = NULL;
}

static void load_quest_line(FILE *file, quest_t *quest)
{
    quest_t *tmp = quest;
    char c = 0;

    while (c != '|') {
        if (load_quest_name(file, tmp, &c) == 1)
            break;
        load_quest_description(file, tmp, &c);
        load_quest_objective(file, tmp, &c);
        fread(&tmp->is_active, sizeof(bool), 1, file);
        fread(&tmp->is_displayed, sizeof(bool), 1, file);
        fread(&tmp->is_done, sizeof(bool), 1, file);
        fread(&tmp->is_last, sizeof(bool), 1, file);
        fread(&tmp->type, sizeof(int), 1, file);
        load_dialog(tmp, file);
        tmp->next = malloc(sizeof(quest_t));
        tmp = tmp->next;
    }
    tmp->next = NULL;
}

static void load_all_quests(FILE *file, all_quests_t *tmp)
{
    char c = 0;

    while (c != '`') {
        if (load_proprietary(file, tmp, &c) == 1)
            break;
        load_quest_line(file, tmp->quest);
        tmp->next = malloc(sizeof(all_quests_t));
        tmp = tmp->next;
    }
    tmp->next = NULL;
}

static void load_attributes(save_t *save, FILE *file)
{
    save->attributes = malloc(sizeof(attributes_t));
    save->pos = (sfVector2f){0, 0};
    fread((void *)(&save->pos.x), sizeof(save->pos.x), 1, file);
    fread((void *)(&save->pos.y), sizeof(save->pos.y), 1, file);
    fread(&save->attributes, sizeof(attributes_t), 1, file);
    fread(&save->type, sizeof(int), 1, file);
}

save_t *load(int nb)
{
    char *path = my_strcatdup("save", nb + '0');
    FILE *file = fopen(path, "r");
    save_t *save = malloc(sizeof(save_t));
    slot_t *tmp = malloc(sizeof(slot_t));
    slot_t *tmp2 = malloc(sizeof(slot_t));
    all_quests_t *tmp3 = malloc(sizeof(all_quests_t));

    if (!file)
        return NULL;
    load_attributes(save, file);
    save->slot = tmp;
    load_slots(file, tmp);
    save->stuff = tmp2;
    load_stuff(file, tmp2);
    save->quests = tmp3;
    load_all_quests(file, tmp3);
    fclose(file);
    free(path);
    return save;
}
