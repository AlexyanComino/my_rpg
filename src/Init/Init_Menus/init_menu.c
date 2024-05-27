/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_menu
*/

#include "rpg.h"

static sfText *init_title_text1(loading_t *loading, sfVector2f pos)
{
    sfText *text = sfText_create();
    sfFloatRect rect;

    sfText_setFont(text, loading->font);
    sfText_setCharacterSize(text, 430);
    sfText_setString(text, "The Blade of");
    rect = sfText_getGlobalBounds(text);
    sfText_setOrigin(text, (sfVector2f){rect.width / 2, rect.height / 2});
    sfText_setPosition(text, pos);
    sfText_setColor(text, sfWhite);
    sfText_setOutlineColor(text, sfBlack);
    sfText_setOutlineThickness(text, 20);
    return text;
}

static sfText *init_title_text2(loading_t *loading, sfVector2f pos)
{
    sfText *text = sfText_create();
    sfFloatRect rect;

    sfText_setFont(text, loading->font);
    sfText_setCharacterSize(text, 579);
    sfText_setString(text, "Eternity");
    rect = sfText_getGlobalBounds(text);
    sfText_setOrigin(text, (sfVector2f){rect.width / 2, rect.height / 2});
    sfText_setPosition(text, pos);
    sfText_setColor(text, sfWhite);
    sfText_setOutlineColor(text, sfBlack);
    sfText_setOutlineThickness(text, 20);
    return text;
}

static void init_titles(rpg_t *rpg, menu_t *menu, sfVector2f top_left)
{
    sfText *text = NULL;
    sfText *shadow = NULL;
    sfVector2f pos1 = {top_left.x + ((WIDTH - 600) * rpg->win->zoom),
        top_left.y + 200 * rpg->win->zoom};
    sfVector2f pos2 = {top_left.x + ((WIDTH - 600) * rpg->win->zoom),
        top_left.y + 328 * rpg->win->zoom};

    menu->font =
        sfFont_createFromFile("assets/fonts/BreatheFireIii-PKLOB.ttf");
    text = init_title_text1(rpg->loading, pos1);
    shadow = sfText_copy(text);
    sfText_setColor(shadow, sfBlack);
    sfText_setPosition(shadow, (sfVector2f){pos1.x + 20, pos1.y + 20});
    menu->title1 = init_anim_text(text, 0.05, 0.0002, shadow);
    text = init_title_text2(rpg->loading, pos2);
    shadow = sfText_copy(text);
    sfText_setColor(shadow, sfBlack);
    sfText_setPosition(shadow, (sfVector2f){pos2.x + 20, pos2.y + 20});
    menu->title2 = init_anim_text(text, 0.05, 0.0002, shadow);
}

menu_t *init_menu(rpg_t *rpg)
{
    menu_t *menu = malloc(sizeof(menu_t));
    sfVector2f top_left = {rpg->win->view_pos.x - (WIDTH / 2 * rpg->win->zoom),
        rpg->win->view_pos.y - (HEIGHT / 2 * rpg->win->zoom)};

    init_titles(rpg, menu, top_left);
    menu->buttons = NULL;
    add_button(&menu->buttons, (sfVector2f){top_left.x + 260 * rpg->win->zoom,
        top_left.y + 680 * rpg->win->zoom}, "Options");
    add_button(&menu->buttons, (sfVector2f){top_left.x + 1700 * rpg->win->zoom,
        top_left.y + 950 * rpg->win->zoom}, "Quitter");
    add_button(&menu->buttons, (sfVector2f){top_left.x + 350 * rpg->win->zoom,
        top_left.y + 850 * rpg->win->zoom}, "Jouer");
    return menu;
}

menu_t *init_settings(rpg_t *rpg)
{
    menu_t *menu = malloc(sizeof(menu_t));
    sfVector2f top_left = {rpg->win->view_pos.x - (WIDTH / 2 * rpg->win->zoom),
        rpg->win->view_pos.y - (HEIGHT / 2 * rpg->win->zoom)};

    menu->font =
        sfFont_createFromFile("assets/fonts/BreatheFireIii-PKLOB.ttf");
    menu->title1 = NULL;
    menu->title2 = NULL;
    menu->buttons = NULL;
    add_button(&menu->buttons, (sfVector2f){top_left.x +
        (WIDTH - 100) / 2 * rpg->win->zoom,
        top_left.y + HEIGHT / 2 - 100 * rpg->win->zoom}, "Volume");
    add_button(&menu->buttons, (sfVector2f){top_left.x +
        (WIDTH - 100) / 2 * rpg->win->zoom,
        top_left.y + HEIGHT / 2 * rpg->win->zoom}, "FPS: 60");
    add_button(&menu->buttons, (sfVector2f){top_left.x +
        (WIDTH - 100) / 2 * rpg->win->zoom,
        top_left.y + HEIGHT / 2 + 500 * rpg->win->zoom}, "Retour");
    return menu;
}
