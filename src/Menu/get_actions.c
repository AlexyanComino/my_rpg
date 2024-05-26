/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** get_actions
*/

#include "rpg.h"

static void *get_action4(char *txt)
{
    if (strcmp(txt, "Continuer") == 0)
        return &continue_game;
    if (strcmp(txt, "Reprendre") == 0)
        return &reprendre_game;
    if (strcmp(txt, "Sauvegarder") == 0)
        return &sauvegarder_game;
    if (strcmp(txt, "Volume") == 0)
        return &change_volume;
    return NULL;
}

static void *get_action3(char *txt)
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
    return get_action4(txt);
}

static void *get_action2(char *txt)
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
    if (strcmp(txt, "Jouer") == 0)
        return &save_menu;
    if (strcmp(txt, "Options") == 0)
        return &settings;
    if (strcmp(txt, "Quitter") == 0)
        return &quit;
    if (strcmp(txt, "FPS: 30") == 0 || strcmp(txt, "FPS: 60") == 0 ||
        strcmp(txt, "FPS: 120") == 0)
        return &change_fps;
    if (strcmp(txt, "Retour") == 0 || strcmp(txt, "Retour au menu") == 0 ||
        strcmp(txt, "Menu Principal") == 0)
        return &back_to_menu;
    if (strcmp(txt, "Sauvegarde 1") == 0)
        return &load_save1;
    if (strcmp(txt, "Sauvegarde 2") == 0)
        return &load_save2;
    if (strcmp(txt, "Sauvegarde 3") == 0)
        return &load_save3;
    return get_action2(txt);
}
