/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_credits
*/

#include "rpg.h"

static void get_credit_size_and_thickness(int type, float *size,
    float *thickness)
{
    if (type == 1) {
        *size = 100;
        *thickness = 8;
    } else if (type == 2) {
        *size = 140;
        *thickness = 12;
    } else if (type == 3) {
        *size = 180;
        *thickness = 15;
    } else {
        *size = 60;
        *thickness = 4;
    } 
}

static text_list_t *init_new_text_list(char *str, sfVector2f pos,
    int type)
{
    text_list_t *new = malloc(sizeof(text_list_t));
    float size = 0;
    float thickness = 0;

    get_credit_size_and_thickness(type, &size, &thickness);
    new->text = sfText_create();
    sfText_setColor(new->text, sfWhite);
    sfText_setOutlineColor(new->text, sfBlack);
    sfText_setOutlineThickness(new->text, thickness);
    set_string_to_text(new->text, str);
    sfText_setCharacterSize(new->text, size);
    sfText_setPosition(new->text, pos);
    new->pos = pos;
    return new;
}

static void add_credits_text(text_list_t **list, char *str, sfVector2f pos,
    int type)

{
    text_list_t *new = init_new_text_list(str, pos, type);
    text_list_t *tmp = *list;

    new->next = NULL;
    if (!tmp) {
        *list = new;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

static void set_font_to_texts(credits_t *credits)
{
    text_list_t *tmp = credits->texts;
    sfFloatRect rect;

    credits->font =
        sfFont_createFromFile("assets/fonts/PoetsenOne-Regular.ttf");
    while (tmp) {
        sfText_setFont(tmp->text, credits->font);
        rect = sfText_getLocalBounds(tmp->text);
        sfText_setOrigin(tmp->text, (sfVector2f){rect.width / 2,
            rect.height / 2});
        tmp = tmp->next;
    }
}

static void get_line_type(char **line, int *type, bool *first)
{
    if ((*line)[0] == '|') {
        *type = 1;
        (*line)++;
    } else if ((*line)[0] == '~') {
        *type = 2;
        (*line)++;
    } else
        *type = 0;
    if (*first) {
        *type = 3;
        *first = false;
    }
}

static void read_credits_file(credits_t *credits, FILE *file)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    sfVector2f pos = {WIDTH / 2, HEIGHT + 150};
    int type = 2;
    bool first = true;

    read = getline(&line, &len, file);
    while (read != -1) {
        if (line[0] == '\n') {
            pos.y += 100;
            read = getline(&line, &len, file);
            continue;
        }
        get_line_type(&line, &type, &first);
        add_credits_text(&credits->texts, line, pos, type);
        pos.y += 100;
        read = getline(&line, &len, file);
    }
}

credits_t *init_credits(void)
{
    credits_t *credits = malloc(sizeof(credits_t));
    FILE *file = fopen(".credits.txt", "r");

    credits->texts = NULL;
    if (file) {
        read_credits_file(credits, file);
        fclose(file);
    }
    set_font_to_texts(credits);
    return credits;
}
