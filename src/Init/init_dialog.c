/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** quests
*/

#include "rpg.h"

char split_line(char c, int *j)
{
    if (*j >= 60) {
        c = '\n';
        *j = 0;
    }
    *j = *j + 1;
    return c;
}

dialog_t *init_dialog(char *dialog)
{
    dialog_t *new = malloc(sizeof(dialog_t));
    int len = 0;
    int j = 0;

    new->txt = NULL;
    for (int i = 0; dialog[i] != '\0'; i++) {
        len = (dialog[i] == ' ' ? i : len);
        if (((dialog[i] == '.' && dialog[i + 1] != '.') ||
            (dialog[i] == '!' && dialog[i + 1] != '!') ||
            (dialog[i] == '?' && dialog[i + 1] != '?')) &&
            dialog[i + 1] != '\0') {
            new->txt = strndup(dialog, i + 1);
            new->next = init_dialog((dialog + i + 1));
            return new;
        }
        dialog[len] = split_line(dialog[len], &j);
    }
    new->txt = (new->txt == NULL ? strdup(dialog) : new->txt);
    new->next = NULL;
    return new;
}
