/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** file_to_array
*/

#include "rpg.h"

static int count_lines(FILE *file)
{
    char *line = NULL;
    size_t len = 0;
    int i = 0;

    while (getline(&line, &len, file) != -1) {
        if (line[0] == '#' || line[0] == '\n' || line[0] == '\0')
            continue;
        i++;
    }
    return i;
}

char **file_to_array(char *path)
{
    FILE *file = fopen(path, "r");
    char *line = NULL;
    size_t len = 0;
    char **tab = NULL;
    int i = 0;

    if (file == NULL)
        return NULL;
    tab = malloc(sizeof(char *) * (count_lines(file) + 1));
    fseek(file, 0, SEEK_SET);
    while (getline(&line, &len, file) != -1) {
        if (line[0] == '#' || line[0] == '\n' || line[0] == '\0')
            continue;
        tab[i] = strdup(line);
        i++;
    }
    tab[i] = NULL;
    fclose(file);
    return tab;
}

void free_array(char **array)
{
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}
