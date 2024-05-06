/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** file_to_array
*/

#include "rpg.h"

char **file_to_array(char *path)
{
    FILE *file = fopen(path, "r");
    char *line = NULL;
    size_t len = 0;
    char **tab = NULL;
    int i = 0;

    if (file == NULL)
        return NULL;
    while (getline(&line, &len, file) != -1)
        i++;
    tab = malloc(sizeof(char *) * (i + 1));
    fseek(file, 0, SEEK_SET);
    i = 0;
    while (getline(&line, &len, file) != -1) {
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
