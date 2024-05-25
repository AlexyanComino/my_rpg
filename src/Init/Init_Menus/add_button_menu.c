/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** add_button_menu
*/

#include "rpg.h"

static void new_button3(button_t *new, char *txt, sfVector2f pos)
{
    sfFloatRect bounds;

    set_string_to_text(new->text, txt);
    set_string_to_text(new->shadow, txt);
    sfText_setPosition(new->text, pos);
    sfText_setPosition(new->shadow, (sfVector2f){pos.x + 30, pos.y + 30});
    bounds = sfText_getLocalBounds(new->text);
    sfText_setOrigin(new->text, (sfVector2f){bounds.width / 2,
        bounds.height / 2});
    bounds = sfText_getLocalBounds(new->shadow);
    sfText_setOrigin(new->shadow, (sfVector2f){bounds.width / 2,
        bounds.height / 2});
    sfRectangleShape_setSize(new->rect_shape, (sfVector2f){500, 150});
    sfRectangleShape_setPosition(new->rect_shape,
        (sfVector2f){pos.x - 190, pos.y});
    sfRectangleShape_setFillColor(new->rect_shape,
        sfColor_fromRGBA(0, 0, 0, 100));
}

static sfColor get_but_color_from_name(char *txt)
{
    if (!strcmp(txt, "Options"))
        return sfColor_fromRGB(220, 220, 220);
    if (!strcmp(txt, "Quitter"))
        return sfColor_fromRGB(199, 59, 47);
    if (!strcmp(txt, "Jouer"))
        return sfColor_fromRGB(220, 220, 220);
    if (!strcmp(txt, "Volume"))
        return sfColor_fromRGB(220, 220, 220);
    if (!strcmp(txt, "Plein Ecran"))
        return sfColor_fromRGB(220, 220, 220);
    if (!strcmp(txt, "Retour"))
        return sfColor_fromRGB(220, 220, 220);
    return sfWhite;
}

static sfColor get_but_color_click_from_name(char *txt)
{
    if (!strcmp(txt, "Options"))
        return sfColor_fromRGB(255, 255, 255);
    if (!strcmp(txt, "Quitter"))
        return sfColor_fromRGB(255, 255, 255);
    if (!strcmp(txt, "Jouer"))
        return sfColor_fromRGB(255, 255, 255);
    if (!strcmp(txt, "Volume"))
        return sfColor_fromRGB(255, 255, 255);
    if (!strcmp(txt, "Plein Ecran"))
        return sfColor_fromRGB(255, 255, 255);
    if (!strcmp(txt, "Retour"))
        return sfColor_fromRGB(255, 255, 255);
    return sfWhite;
}

static void new_button2(button_t *new, char *txt, sfVector2f pos)
{
    float size = 0;

    if (!strcmp(txt, "Jouer")) {
        sfText_setCharacterSize(new->text, 450);
        sfText_setCharacterSize(new->shadow, 450);
        size = 18;
    } else {
        sfText_setCharacterSize(new->text, 200);
        sfText_setCharacterSize(new->shadow, 200);
        size = 14;
    }
    sfText_setOutlineColor(new->text, sfBlack);
    sfText_setOutlineColor(new->shadow, sfColor_fromRGBA(0, 0, 0, 0));
    sfText_setOutlineThickness(new->text, size);
    sfText_setOutlineThickness(new->shadow, size);
    new->color = get_but_color_from_name(txt);
    new->click_color = get_but_color_click_from_name(txt);
    sfText_setColor(new->text, new->color);
    sfText_setColor(new->shadow, sfColor_fromRGBA(0, 0, 0, 0));
    new_button3(new, txt, pos);
}

static button_t *new_button(char *txt, sfVector2f pos)
{
    button_t *new = malloc(sizeof(button_t));

    new->name = strdup(txt);
    new->text = sfText_create();
    new->font = sfFont_createFromFile("assets/fonts/BreatheFireIii-PKLOB.ttf");
    new->state = NOTHING;
    new->shadow = sfText_create();
    new->action = get_action(txt);
    new->rect_shape = sfRectangleShape_create();
    new->rect = (sfIntRect){0, 0, BUTTON_WIDTH, BUTTON_HEIGHT};
    sfText_setFont(new->text, new->font);
    sfText_setFont(new->shadow, new->font);
    new_button2(new, txt, pos);
    return new;
}

void add_button(button_t **buttons, sfVector2f pos, char *txt)
{
    button_t *new = new_button(txt, pos);
    button_t *tmp = *buttons;

    new->next = NULL;
    while (tmp && tmp->next != NULL)
        tmp = tmp->next;
    if (!tmp)
        *buttons = new;
    else if (tmp->next == NULL)
        tmp->next = new;
}
