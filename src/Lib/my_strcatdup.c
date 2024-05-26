/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** my_strcatdup
*/

#include <stdlib.h>
#include <string.h>

char *my_strcatdup(char *str1, char c)
{
    char *result = malloc(sizeof(char) * (strlen(str1) + 2));
    int i = 0;

    for (; str1[i] != '\0'; i++)
        result[i] = str1[i];
    result[i] = c;
    result[i + 1] = '\0';
    return result;
}

char *my_strcatdup2(char *str1, char *str2)
{
    char *result = malloc(sizeof(char) * (strlen(str1) + strlen(str2) + 1));
    char *tmp = strdup(str2);

    strcpy(result, str1);
    strcat(result, tmp);
    return result;
}
