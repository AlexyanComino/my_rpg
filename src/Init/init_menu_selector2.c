/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_menu_selector2
*/

#include "rpg.h"

char **get_infos(char *txt)
{
    char **tab = file_to_array(".entities.csv");
    char **infos = NULL;

    if (strcmp(txt, "WARRIOR") == 0)
        infos = split_string(tab[0], ";");
    if (strcmp(txt, "PAWN") == 0)
        infos = split_string(tab[1], ";");
    if (strcmp(txt, "ARCHER") == 0)
        infos = split_string(tab[4], ";");
    if (strcmp(txt, "TORCH") == 0)
        infos = split_string(tab[2], ";");
    if (strcmp(txt, "TNT") == 0)
        infos = split_string(tab[3], ";");
    free_array(tab);
    return infos;
}

void add_more_buttons(
    select_menu_t *menu, sfVector2f top_left, char **tab, rpg_t *rpg)
{
    add_select_button(menu->buttons,
    (sfVector2f){top_left.x + (WIDTH / 2 + 325) * rpg->win->zoom, top_left.y +
        (HEIGHT / 2 - 300) * rpg->win->zoom}, "TORCH", tab);
    add_select_button(menu->buttons,
    (sfVector2f){top_left.x + (WIDTH / 2 + 650) * rpg->win->zoom, top_left.y +
        (HEIGHT / 2 - 300) * rpg->win->zoom}, "TNT", tab);
    add_select_button(menu->buttons,
    (sfVector2f){top_left.x + (WIDTH / 2) * rpg->win->zoom, top_left.y +
        (HEIGHT / 2 + 400) * rpg->win->zoom}, "BACK", tab);
}

void create_buttons_select(rpg_t *rpg, select_menu_t *menu)
{
    char **tab = file_to_array(".entities.csv");
    sfVector2f top_left = {rpg->win->view_pos.x - (WIDTH / 2 * rpg->win->zoom),
        rpg->win->view_pos.y - (HEIGHT / 2 * rpg->win->zoom)};

    menu->buttons = NULL;
    menu->buttons = add_select_button(menu->buttons,
    (sfVector2f){top_left.x + (WIDTH / 2 - 650) * rpg->win->zoom, top_left.y +
        (HEIGHT / 2 - 300) * rpg->win->zoom}, "WARRIOR", tab);
    add_select_button(menu->buttons, (sfVector2f){top_left.x + (WIDTH / 2 -
        325) * rpg->win->zoom, top_left.y +
        (HEIGHT / 2 - 300) * rpg->win->zoom}, "PAWN", tab);
    add_select_button(menu->buttons,
    (sfVector2f){top_left.x + (WIDTH / 2) * rpg->win->zoom, top_left.y +
        (HEIGHT / 2 - 300) * rpg->win->zoom}, "ARCHER", tab);
    add_more_buttons(menu, top_left, tab, rpg);
}
