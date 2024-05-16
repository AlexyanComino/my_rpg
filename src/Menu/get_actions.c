/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** get_actions
*/

#include "rpg.h"

void *get_action3(char *txt)
{
    if (strcmp(txt, "WARRIOR") == 0)
        return &start_warrior;
    if (strcmp(txt, "PAWN") == 0)
        return &start_pawn;
    if (strcmp(txt, "ARCHER") == 0)
        return &start_archer;
    if (strcmp(txt, "TORCH") == 0)
        return &start_torch;
    if (strcmp(txt, "TNT") == 0)
        return &start_tnt;
    return NULL;
}

void *get_action2(char *txt)
{
    if (strcmp(txt, "Bien sur!") == 0)
        return &accept_quest;
    if (strcmp(txt, "Non merci.") == 0)
        return &refuse_quest;
    if (strcmp(txt, "Oui") == 0)
        return &accept_quest;
    if (strcmp(txt, "Non") == 0)
        return &refuse_quest;
    return get_action3(txt);
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
        return &selector;
    if (strcmp(txt, "SAVE 2") == 0)
        return &selector;
    if (strcmp(txt, "SAVE 3") == 0)
        return &selector;
    return get_action2(txt);
}
