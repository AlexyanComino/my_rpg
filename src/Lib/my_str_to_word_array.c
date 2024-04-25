/*
** EPITECH PROJECT, 2023
** B-BOO-101-MPL-1-1-phoenixd04-alexyan.comino
** File description:
** split_string
*/

#include <stdlib.h>
#include <string.h>

int is_delimiter(char c, char *delim)
{
    while (*delim != '\0') {
        if (c == *delim)
            return 1;
        delim++;
    }
    return 0;
}

int count_words(char *str, char *delim)
{
    int count = 0;
    int in_word = 0;

    while (*str != '\0') {
        if (!is_delimiter(*str, delim) && !in_word) {
                count++;
                in_word = 1;
        } else {
            in_word = 0;
        }
        str++;
    }
    return count;
}

char **split_string(char *str, char *delim)
{
    char **array = malloc(sizeof(char *) * (count_words(str, delim) + 1));
    char *pch = strtok(str, delim);
    int i = 0;

    while (pch != NULL) {
        array[i] = strdup(pch);
        pch = strtok(NULL, delim);
        i++;
    }
    array[i] = NULL;
    return array;
}
