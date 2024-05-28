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
    mbstowcs(ws, buffer, len + 1);
    ws[len] = L'\0';
    unicode = (sfUint32 *)ws;
    sfText_setUnicodeString(text, unicode);
}

void setup_end_header(rpg_t *rpg, char *string)
{
    sfFloatRect rect;

    if (string != NULL) {
        set_string_to_text(rpg->quest_header->text, string);
        rect = sfText_getGlobalBounds(rpg->quest_header->text);
        sfText_setOrigin(rpg->quest_header->text, (sfVector2f){
            rect.width / 2, rect.height / 2});
    }
    rpg->quest_header->state = Q_END;
}
