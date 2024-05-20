/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_menu_save
*/

#include "rpg.h"

static save_button_t *new_save_button(char *txt)
{
    save_button_t *new = malloc(sizeof(button_t));

    new->name = strdup(txt);
    new->text = sfText_create();
    new->font = sfFont_createFromFile("assets/fonts/CompassPro.ttf");
    new->state = NOTHING;
    new->action = get_action(txt);
    new->rect_shape = sfRectangleShape_create();
    new->rect = (sfIntRect){0, 0, BUTTON_WIDTH, BUTTON_HEIGHT};
    new->player_status = init_player_status();
    new->next = NULL;
    return new;
}

static save_button_t *add_button_save(
    save_button_t *buttons, sfVector2f pos, char *txt)
{
    save_button_t *new = new_save_button(txt);
    save_button_t *tmp = buttons;
    sfFloatRect rect;

    sfText_setFont(new->text, new->font);
    sfText_setCharacterSize(new->text, 100);
    sfText_setColor(new->text, sfWhite);
    sfText_setString(new->text, txt);
    rect = sfText_getGlobalBounds(new->text);
    sfText_setOrigin(new->text, (sfVector2f){rect.width / 2, rect.height / 2});
    sfText_setPosition(new->text, pos);
    sfRectangleShape_setSize(new->rect_shape, (sfVector2f){1000, 250});
    sfRectangleShape_setOrigin(new->rect_shape, (sfVector2f){500, 125});
    sfRectangleShape_setPosition(new->rect_shape, pos);
    sfRectangleShape_setFillColor(new->rect_shape, sfColor_fromRGBA(0, 0, 0, 100));
    if (buttons == NULL)
        return new;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
    return buttons;
}

save_menu_t *init_save_menu(rpg_t *rpg)
{
    save_menu_t *menu = malloc(sizeof(menu_t));
    sfVector2f top_left = {rpg->win->view_pos.x - (WIDTH / 2 * rpg->win->zoom),
        rpg->win->view_pos.y - (HEIGHT / 2 * rpg->win->zoom)};
    
    menu->background_texture = sfTexture_createFromFile(
        "assets/menu/bg.png", NULL);
    menu->background = sfSprite_create();
    sfSprite_setTexture(menu->background, menu->background_texture, sfTrue);
    menu->font = sfFont_createFromFile("assets/fonts/m6x11plus.ttf");
    menu->myclock = NULL;
    menu->text = NULL;
    menu->buttons = NULL;
    menu->buttons = add_button_save(menu->buttons,
    (sfVector2f){top_left.x + WIDTH / 2 * rpg->win->zoom,
        top_left.y + (HEIGHT / 2 - 150) * rpg->win->zoom}, "SAVE 1");
    add_button_save(menu->buttons,
    (sfVector2f){top_left.x + WIDTH / 2 * rpg->win->zoom,
        top_left.y + (HEIGHT / 2 + 75) * rpg->win->zoom}, "SAVE 2");
    add_button_save(menu->buttons,
    (sfVector2f){top_left.x + WIDTH / 2 * rpg->win->zoom,
        top_left.y + (HEIGHT / 2 + 300) * rpg->win->zoom}, "SAVE 3");
    add_button_save(menu->buttons,
    (sfVector2f){top_left.x + WIDTH / 2 * rpg->win->zoom,
        top_left.y + (HEIGHT / 2 + 450) * rpg->win->zoom}, "BACK");
    return menu;
}
