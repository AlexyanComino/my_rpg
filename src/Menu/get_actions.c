/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** get_actions
*/

#include "rpg.h"

void *get_action2(char *txt)
{
    if (strcmp(txt, "Bien sur!") == 0)
        return &accept_quest;
    if (strcmp(txt, "Non merci.") == 0)
        return &refuse_quest;
    return NULL;
}

void *get_action(char *txt)
{
    if (strcmp(txt, "PLAY") == 0)
        return &save_menu;
    if (strcmp(txt, "OPTIONS") == 0)
        return &settings;
    if (strcmp(txt, "QUIT") == 0)
        return &quit;
    if (strcmp(txt, "RESUME") == 0)
        return &start;
    if (strcmp(txt, "FULLSCREEN") == 0)
        return &settings;
    if (strcmp(txt, "BACK") == 0)
        return &back_to_menu;
    if (strcmp(txt, "SAVE 1") == 0)
        return &start;
    if (strcmp(txt, "SAVE 2") == 0)
        return &start;
    if (strcmp(txt, "SAVE 3") == 0)
        return &start;
    return get_action2(txt);
}
