/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_menu
*/

#include "rpg.h"

static button_t *new_button(char *txt)
{
    button_t *new = malloc(sizeof(button_t));

    new->name = strdup(txt);
    new->text = sfText_create();
    new->font = sfFont_createFromFile("assets/fonts/CompassPro.ttf");
    new->state = NOTHING;
    new->action = get_action(txt);
    new->rect_shape = sfRectangleShape_create();
    new->rect = (sfIntRect){0, 0, BUTTON_WIDTH, BUTTON_HEIGHT};
    new->next = NULL;
    return new;
}

static button_t *add_button(button_t *buttons, sfVector2f pos, char *txt)
{
    button_t *new = new_button(txt);
    button_t *tmp = buttons;

    sfText_setFont(new->text, new->font);
    sfText_setCharacterSize(new->text, 50);
    sfText_setColor(new->text, sfWhite);
    sfText_setString(new->text, txt);
    sfText_setPosition(new->text, pos);
    sfRectangleShape_setSize(new->rect_shape, (sfVector2f){500, 150});
    sfRectangleShape_setPosition(new->rect_shape,
        (sfVector2f){pos.x - 190, pos.y});
    sfRectangleShape_setFillColor(new->rect_shape,
        sfColor_fromRGBA(0, 0, 0, 100));
    if (buttons == NULL)
        return new;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
    return buttons;
}

sfText *create_text(sfFont *font, char *str, int size, sfVector2f pos)
{
    sfText *text = sfText_create();

    sfText_setFont(text, font);
    sfText_setCharacterSize(text, size);
    sfText_setColor(text, sfWhite);
    sfText_setString(text, str);
    sfText_setPosition(text, pos);
    return text;
}

menu_t *init_menu(void)
{
    menu_t *menu = malloc(sizeof(menu_t));

    menu->background_texture = sfTexture_createFromFile(
        "assets/menu/bg.png", NULL);
    menu->background = sfSprite_create();
    menu->bg_rect = (sfIntRect){0, 0, WIDTH, HEIGHT};
    sfSprite_setTexture(menu->background, menu->background_texture, sfTrue);
    sfSprite_setTextureRect(menu->background, (sfIntRect){0, 0, 1920, HEIGHT});
    menu->myclock = init_my_clock();
    menu->font = sfFont_createFromFile("assets/fonts/CompassPro.ttf");
    menu->text = create_text(menu->font, "MY RPG", 100, (sfVector2f)
    {(WIDTH - (strlen("MY RPG") * 50)) / 2, 100});
    menu->buttons = NULL;
    menu->buttons = add_button(menu->buttons, (sfVector2f)
    {200, 400}, "PLAY");
    add_button(menu->buttons, (sfVector2f)
    {200, 600}, "OPTIONS");
    add_button(menu->buttons, (sfVector2f)
    {200, 800}, "QUIT");
    return menu;
}

menu_t *init_settings(void)
{
    menu_t *menu = malloc(sizeof(menu_t));

    menu->background_texture = sfTexture_createFromFile(
        "assets/menu/bg.png", NULL);
    menu->background = sfSprite_create();
    sfSprite_setTexture(menu->background, menu->background_texture, sfTrue);
    menu->font = sfFont_createFromFile("assets/fonts/m6x11plus.ttf");
    menu->myclock = NULL;
    menu->text = NULL;
    menu->buttons = NULL;
    menu->buttons = add_button(menu->buttons,
    (sfVector2f){(WIDTH - 100) / 2, HEIGHT / 2 - 50}, "CACA");
    add_button(menu->buttons,
    (sfVector2f){(WIDTH - 100) / 2, HEIGHT / 2 + 50}, "TEMP");
    add_button(menu->buttons,
    (sfVector2f){(WIDTH - 100) / 2, HEIGHT / 2 + 150}, "BACK");
    return menu;
}
