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
    new->font = sfFont_createFromFile("assets/fonts/Say Comic.ttf");
    new->state = NOTHING;
    new->action = get_action(txt);
    new->rect_shape = sfRectangleShape_create();
    new->rect = (sfIntRect){0, 0, BUTTON_WIDTH, BUTTON_HEIGHT};
    sfText_setFont(new->text, new->font);
    if (!strcmp(txt, "PLAY"))
        sfText_setCharacterSize(new->text, 300);
    else
        sfText_setCharacterSize(new->text, 120);
    new->next = NULL;
    return new;
}

static void add_button(button_t **buttons, sfVector2f pos, char *txt,
    sfColor color)
{
    button_t *new = new_button(txt);
    button_t *tmp = *buttons;
    sfFloatRect bounds;

    sfText_setColor(new->text, color);
    sfText_setString(new->text, txt);
    sfText_setPosition(new->text, pos);
    bounds = sfText_getLocalBounds(new->text);
    sfText_setOrigin(new->text, (sfVector2f){bounds.width / 2,
        bounds.height / 2});
    sfRectangleShape_setSize(new->rect_shape, (sfVector2f){500, 150});
    sfRectangleShape_setPosition(new->rect_shape,
        (sfVector2f){pos.x - 190, pos.y});
    sfRectangleShape_setFillColor(new->rect_shape,
        sfColor_fromRGBA(0, 0, 0, 100));
    while (tmp && tmp->next != NULL)
        tmp = tmp->next;
    if (!tmp)
        *buttons = new;
    else if (tmp->next == NULL)
        tmp->next = new;
}

sfText *create_text(sfFont *font, char *str, int size, sfVector2f pos)
{
    sfText *text = sfText_create();
    sfFloatRect bounds;

    sfText_setFont(text, font);
    sfText_setCharacterSize(text, size);
    sfText_setColor(text, sfWhite);
    sfText_setString(text, str);
    bounds = sfText_getLocalBounds(text);
    sfText_setOrigin(text, (sfVector2f){bounds.width / 2, bounds.height / 2});
    sfText_setPosition(text, pos);
    return text;
}

menu_t *init_menu(rpg_t *rpg)
{
    menu_t *menu = malloc(sizeof(menu_t));
    sfVector2f top_left = {rpg->win->view_pos.x - (WIDTH / 2 * rpg->win->zoom),
        rpg->win->view_pos.y - (HEIGHT / 2 * rpg->win->zoom)};
    char *buttons_names[3] = {"OPTIONS", "QUIT", "PLAY"};
    sfColor colors[3] = {sfColor_fromRGB(220, 220, 220), sfColor_fromRGB(255, 103, 101), sfColor_fromRGB(220, 220, 220)};

    menu->font = sfFont_createFromFile("assets/fonts/BreatheFireIii-PKLOB.ttf");
    menu->text = create_text(menu->font, "MY RPG", 300, (sfVector2f)
    {top_left.x + ((WIDTH - strlen("MY RPG") / 2) * rpg->win->zoom / 2), top_left.y + 100});
    menu->buttons = NULL;

    add_button(&menu->buttons, (sfVector2f){top_left.x + 250 * rpg->win->zoom, top_left.y + 760 * rpg->win->zoom}, buttons_names[0], colors[0]);
    add_button(&menu->buttons, (sfVector2f){top_left.x + 1760 * rpg->win->zoom, top_left.y + 950 * rpg->win->zoom}, buttons_names[1], colors[1]);
    add_button(&menu->buttons, (sfVector2f){top_left.x + 290 * rpg->win->zoom, top_left.y + 880 * rpg->win->zoom}, buttons_names[2], colors[2]);
    return menu;
}

menu_t *init_settings(rpg_t *rpg)
{
    menu_t *menu = malloc(sizeof(menu_t));
    sfColor color = sfColor_fromRGB(220, 220, 220);
    sfVector2f top_left = {rpg->win->view_pos.x - (WIDTH / 2 * rpg->win->zoom),
        rpg->win->view_pos.y - (HEIGHT / 2 * rpg->win->zoom)};
    char *buttons_names[3] = {"VOLUME", "FULLSCREEN", "BACK"};

    menu->font = sfFont_createFromFile("assets/fonts/m6x11plus.ttf");
    menu->myclock = NULL;
    menu->text = NULL;
    menu->buttons = NULL;
    add_button(&menu->buttons, (sfVector2f){top_left.x + (WIDTH - 100) / 2 * rpg->win->zoom,
        top_left.y + HEIGHT / 2 - 100 * rpg->win->zoom}, buttons_names[0], color);
    add_button(&menu->buttons, (sfVector2f){top_left.x + (WIDTH - 100) / 2 * rpg->win->zoom,
        top_left.y + HEIGHT / 2 * rpg->win->zoom}, buttons_names[1], color);
    add_button(&menu->buttons, (sfVector2f){top_left.x + (WIDTH - 100) / 2 * rpg->win->zoom,
        top_left.y + HEIGHT / 2 + 100 * rpg->win->zoom}, buttons_names[2], color);
    return menu;
}
