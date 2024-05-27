/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** save
*/

#include "rpg.h"

static void write_player(rpg_t *rpg, FILE *file)
{
    entity_t *player = get_player(rpg);

    fwrite((void *)(&player->common->pos.x),
        sizeof(player->common->pos.x), 1, file);
    fwrite((void *)(&player->common->pos.y),
        sizeof(player->common->pos.y), 1, file);
    fwrite(&player->common->attributes->max_health,
        sizeof(unsigned int), 1, file);
    fwrite(&player->common->attributes->health,
        sizeof(int), 1, file);
    fwrite(&player->common->attributes->attack,
        sizeof(unsigned int), 1, file);
    fwrite(&player->common->attributes->defense,
        sizeof(unsigned int), 1, file);
    fwrite(&player->common->attributes->speed,
        sizeof(unsigned int), 1, file);
    fwrite(&player->common->attributes->level,
        sizeof(unsigned int), 1, file);
    fwrite(&player->type, sizeof(int), 1, file);
}

static int write_slot(slot_t *slot, FILE *file)
{
    char *str = NULL;

    if (slot->type == OTHER)
        return 1;
    if (slot->type == WEAPON) {
        str = (weapon_t *){slot->item}->name;
        for (int i = 0; str[i] != '\0'; i++)
            fwrite(&str[i], sizeof(char), 1, file);
    }
    if (slot->type == ARMOR) {
        str = (armor_t *){slot->item}->name;
        for (int i = 0; str[i] != '\0'; i++)
            fwrite(&str[i], sizeof(char), 1, file);
    }
    fwrite("~", sizeof(char), 1, file);
    fwrite(&slot->type, sizeof(int), 1, file);
    return 0;
}

static void write_name(slot_t *tmp, FILE *file)
{
    for (int i = 0; tmp->name[i] != '\0'; i++)
        fwrite(&tmp->name[i], sizeof(char), 1, file);
}

static void write_inventory(rpg_t *rpg, FILE *file)
{
    slot_t *tmp = rpg->inventory->slot;
    slot_t *tmp2 = rpg->inventory->player_status->stuff;

    for (; tmp->next != NULL; tmp = tmp->next) {
        if (tmp->type != OTHER) {
            write_name(tmp, file);
            fwrite("~", sizeof(char), 1, file);
            fwrite(&tmp->type, sizeof(int), 1, file);
        }
    }
    fwrite("#", sizeof(char), 1, file);
    for (; tmp2->next != NULL; tmp2 = tmp2->next) {
        if (write_slot(tmp2, file) == 1)
            continue;
    }
    fwrite("`", sizeof(char), 1, file);
}

static void write_quest_line(all_quests_t *quests, FILE *file)
{
    for (quest_t *tmp = quests->quest; tmp != NULL; tmp = tmp->next) {
        fwrite(&tmp->is_active, sizeof(bool), 1, file);
        fwrite(&tmp->is_displayed, sizeof(bool), 1, file);
        fwrite(&tmp->is_done, sizeof(bool), 1, file);
        fwrite(&tmp->is_last, sizeof(bool), 1, file);
        if (tmp->next != NULL)
            fwrite("#", sizeof(char), 1, file);
    }
}

static void write_all_quests(rpg_t *rpg, FILE *file)
{
    all_quests_t *quests = rpg->quests;

    for (; quests != NULL; quests = quests->next) {
        write_quest_line(quests, file);
        if (quests->next != NULL)
            fwrite("|", sizeof(char), 1, file);
    }
    fwrite("`", sizeof(char), 1, file);
}

void save(rpg_t *rpg, int nb)
{
    char *path = my_strcatdup("save", nb + '0');
    FILE *file = fopen(path, "w");

    if (!file)
        return;
    write_player(rpg, file);
    write_inventory(rpg, file);
    write_all_quests(rpg, file);
    fclose(file);
    free(path);
}
