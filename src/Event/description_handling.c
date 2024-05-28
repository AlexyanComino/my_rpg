/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** description_handling
*/

#include "rpg.h"

struct desc_s {
    char *new_desc;
    int i;
    int j;
    int cpt;
    int last_space;
    int new_len;
};

static struct desc_s *init_desc_struct(char *desc)
{
    struct desc_s *desc_s = malloc(sizeof(struct desc_s));

    desc_s->new_len = strlen(desc) + 1;
    desc_s->new_desc = malloc(desc_s->new_len * sizeof(char));
    desc_s->i = 0;
    desc_s->j = 0;
    desc_s->cpt = 0;
    desc_s->last_space = -1;
    return desc_s;
}

// Fonction pour gérer les séquences "\n"
static void handle_newline_sequence(struct desc_s *desc)
{
    desc->new_desc[desc->j] = '\n';
    desc->j++;
    desc->i += 2;
    desc->cpt = 0;
}

// Fonction pour ajouter un caractère et gérer le compteur
static void add_char_and_count(struct desc_s *desc, char c)
{
    desc->new_desc[desc->j] = c;
    desc->j++;
    desc->cpt++;
}

// Fonction pour insérer un saut de ligne et réajuster la chaîne
static void insert_newline(struct desc_s *desc)
{
    if (desc->last_space != -1) {
        desc->new_desc[desc->last_space] = '\n';
        desc->cpt = desc->j - desc->last_space - 1;
        desc->last_space = -1;
    } else {
        desc->new_desc[desc->j] = '\n';
        desc->j++;
        desc->cpt = 0;
    }
    desc->new_len++;
    desc->new_desc = realloc(desc->new_desc, desc->new_len * sizeof(char));
}

char *description_handling(char *description)
{
    struct desc_s *desc = init_desc_struct(description);
    char *tmp = NULL;

    while (description[desc->i] != '\0') {
        if (description[desc->i] == '\\' && description[desc->i + 1] == 'n') {
            handle_newline_sequence(desc);
            continue;
        }
        if (description[desc->i] == ' ')
            desc->last_space = desc->j;
        add_char_and_count(desc, description[desc->i]);
        if (desc->cpt == 58)
            insert_newline(desc);
        desc->i++;
    }
    desc->new_desc[desc->j] = '\0';
    tmp = desc->new_desc;
    free(desc);
    return tmp;
}
