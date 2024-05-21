/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** save
*/

#include "rpg.h"

void save(rpg_t *rpg)
{
    FILE *file = fopen("save.txt", "w");
    entity_t *player = get_player(rpg);
    slot_t *tmp = rpg->inventory->slot;
    slot_t *tmp2 = rpg->inventory->player_status->stuff;

    if (!file)
        return;
    fwrite((void *)(&player->common->pos.x), sizeof(player->common->pos.x), 1, file);
    fwrite((void *)(&player->common->pos.y), sizeof(player->common->pos.y), 1, file);
    fwrite(&player->common->attributes, sizeof(attributes_t), 1, file);
    fwrite(&player->type, sizeof(int), 1, file);
    for (; tmp->next != NULL; tmp = tmp->next) {
        if (tmp->name != NULL) {
            for (int i = 0; tmp->name[i] != '\0'; i++)
                fwrite(&tmp->name[i], sizeof(char), 1, file);
            fwrite("~", sizeof(char), 1, file);
            fwrite(&tmp->type, sizeof(int), 1, file);
        }
    }
    fwrite("#", sizeof(char), 1, file);
    for (; tmp2->next != NULL; tmp2 = tmp2->next) {
        if (tmp2->name != NULL) {
            for (int i = 0; tmp2->name[i] != '\0'; i++)
                fwrite(&tmp2->name[i], sizeof(char), 1, file);
            fwrite("~", sizeof(char), 1, file);
            fwrite(&tmp2->type, sizeof(int), 1, file);
        }
    }
    fwrite("`", sizeof(char), 1, file);
    fclose(file);
}

save_t *load(rpg_t *rpg)
{
    FILE *file = fopen("save.txt", "r");
    save_t *save = malloc(sizeof(save_t));
    slot_t *tmp = malloc(sizeof(slot_t));
    slot_t *tmp2 = malloc(sizeof(slot_t));
    char c = 0;

    if (!file)
        return NULL;
    save->attributes = malloc(sizeof(attributes_t));
    save->pos = (sfVector2f){0, 0};
    fread((void *)(&save->pos.x), sizeof(save->pos.x), 1, file);
    fread((void *)(&save->pos.y), sizeof(save->pos.y), 1, file);
    fread(&save->attributes, sizeof(attributes_t), 1, file);
    fread(&save->type, sizeof(int), 1, file);
    save->slot = tmp;
    while (c != '#') {
        c = 0;
        tmp->next = malloc(sizeof(slot_t));
        tmp->name = "";
        while (c != '~' && c != '#') {
            fread(&c, sizeof(char), 1, file);
            if (c == '~' || c == '#') {
                break;
            }
            tmp->name = my_strcatdup(tmp->name, c);
        }
        rpg = rpg;
        if (c == '#')
            break;
        fread(&tmp->type, sizeof(int), 1, file);
        add_item_from_type(rpg, tmp->name, tmp->type);
        tmp = tmp->next;
    }
    save->stuff = tmp2;
    while (c != '`') {
        c = 0;
        tmp2->next = malloc(sizeof(slot_t));
        tmp2->name = "";
        while (c != '~' && c != '`') {
            fread(&c, sizeof(char), 1, file);
            if (c == '~' || c == '`') {
                break;
            }
            tmp2->name = my_strcatdup(tmp2->name, c);
        }
        if (c == '`')
            break;
        fread(&tmp2->type, sizeof(int), 1, file);
        add_item_from_type(rpg, tmp2->name, tmp2->type);
        tmp2 = tmp2->next;
    }
    fclose(file);
    return save;
}