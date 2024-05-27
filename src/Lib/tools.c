/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** tools
*/

#include "rpg.h"

float get_distance(sfVector2f center1, sfVector2f center2)
{
    return sqrt(pow(center1.x - center2.x, 2) + pow(center1.y - center2.y, 2));
}

void update_clock_seconds(my_clock_t *myclock)
{
    myclock->time = sfClock_getElapsedTime(myclock->clock);
    myclock->seconds = myclock->time.microseconds / 1000000.0;
}

int tab_len(char **tab)
{
    int i = 0;

    for (; tab[i] != NULL; i++);
    return i;
}

void set_string_to_text(sfText *text, const char *string)
{
    sfUint32 *unicode;
    size_t len = strlen(string);
    char buffer[512];

    if (len > 512)
        fprintf(stderr, "String too long\n");
    wchar_t ws[len + 1];
    strcpy(buffer, string);
    if (setlocale(LC_CTYPE, "") == NULL)
        perror("setlocale");
    if (mbstowcs(ws, buffer, len + 1) == (size_t)-1)
        perror("mbstowcs");
    ws[len] = L'\0';
    unicode = (sfUint32 *)ws;
    sfText_setUnicodeString(text, unicode);
}
