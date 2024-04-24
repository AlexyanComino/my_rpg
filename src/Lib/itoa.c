/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** itoa
*/

#include "rpg.h"

char *my_itoa(int nb)
{
    int i = 0;
    int j = 0;
    char *str = malloc(sizeof(char) * 12);

    if (nb == 0)
        return "0";
    if (nb < 0) {
        str[i] = '-';
        i++;
        nb = nb * -1;
    }
    for (; nb > 0; i++) {
        str[i] = (nb % 10) + 48;
        nb = nb / 10;
    }
    str[i] = '\0';
    i--;
    while (j < i) {
        char temp = str[j];
        str[j] = str[i];
        str[i] = temp;
        j++;
        i--;
    }
    printf("str = %s\n", str);
    return str;
}