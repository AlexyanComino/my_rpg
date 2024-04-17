/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_menu
*/

#include "rpg.h"

void *get_action(char *txt)
{
    if (strcmp(txt, "PLAY") == 0)
        return &start;
    if (strcmp(txt, "OPTIONS") == 0)
        return &settings;
    if (strcmp(txt, "QUIT") == 0)
        return &quit;
    if (strcmp(txt, "RESUME") == 0)
        return &start;
    if (strcmp(txt, "FULLSCREEN") == 0)
        return &settings;
    if (strcmp(txt, "BACK") == 0)
        return &back_to_menu;
    return NULL;
}

static button_t *new_button(char *txt)
{
    button_t *new = malloc(sizeof(button_t));

    new->name = strdup(txt);
    new->sprite = sfSprite_create();
    new->text = sfText_create();
    new->texture = sfTexture_createFromFile(
        "assets/menu/gold_button.png", NULL);
    new->font = sfFont_createFromFile("assets/fonts/m6x11plus.ttf");
    new->state = NOTHING;
    new->action = get_action(txt);
    new->rect = (sfIntRect){0, 0, 48, 16};
    new->next = NULL;
    return new;
}

button_t *add_button(button_t *buttons, sfVector2f pos, char *txt)
{
    button_t *new = new_button(txt);
    button_t *tmp = buttons;

    sfSprite_setTexture(new->sprite, new->texture, sfTrue);
    sfText_setFont(new->text, new->font);
    sfText_setCharacterSize(new->text, 50);
    sfText_setColor(new->text, sfWhite);
    sfText_setString(new->text, txt);
    sfText_setPosition(new->text,
    (sfVector2f){pos.x + 10 - (strlen(txt) * 10), pos.y - 5});
    sfSprite_setPosition(new->sprite, (sfVector2f){pos.x - 90, pos.y});
    sfSprite_setScale(new->sprite, (sfVector2f){4, 4});
    if (buttons == NULL)
        return new;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
    return buttons;
}

menu_t *init_menu(void)
{
    menu_t *menu = malloc(sizeof(menu_t));

    menu->background_texture = sfTexture_createFromFile(
        "assets/menu/bg.jpg", NULL);
    menu->background = sfSprite_create();
    menu->rect = (sfIntRect){0, 0, 48, 16};
    sfSprite_setTexture(menu->background, menu->background_texture, sfTrue);
    menu->font = sfFont_createFromFile("assets/fonts/m6x11plus.ttf");
    menu->buttons = NULL;
    menu->buttons = add_button(menu->buttons, (sfVector2f)
    {(WIDTH - (menu->rect.width)) / 2, HEIGHT / 2 - 50}, "PLAY");
    add_button(menu->buttons, (sfVector2f)
    {(WIDTH - (menu->rect.width)) / 2, HEIGHT / 2 + 50}, "OPTIONS");
    add_button(menu->buttons, (sfVector2f)
    {(WIDTH - (menu->rect.width)) / 2, HEIGHT / 2 + 150}, "QUIT");
    return menu;
}

menu_t *init_settings(void)
{
    menu_t *menu = malloc(sizeof(menu_t));

    menu->background_texture = sfTexture_createFromFile(
        "assets/menu/bg.jpg", NULL);
    menu->background = sfSprite_create();
    menu->rect = (sfIntRect){0, 0, 48, 16};
    sfSprite_setTexture(menu->background, menu->background_texture, sfTrue);
    menu->font = sfFont_createFromFile("assets/fonts/m6x11plus.ttf");
    menu->buttons = NULL;
    menu->buttons = add_button(menu->buttons,
    (sfVector2f){(WIDTH - (menu->rect.width)) / 2, HEIGHT / 2 - 50}, "CACA");
    add_button(menu->buttons,
    (sfVector2f){(WIDTH - (menu->rect.width)) / 2, HEIGHT / 2 + 50}, "TEMP");
    add_button(menu->buttons,
    (sfVector2f){(WIDTH - (menu->rect.width)) / 2, HEIGHT / 2 + 150}, "BACK");
    return menu;
}
