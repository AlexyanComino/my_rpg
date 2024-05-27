/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_credits
*/

#include "rpg.h"


static void remove_text(text_list_t **list, text_list_t *to_remove)
{
    text_list_t *tmp = *list;

    if (tmp == to_remove) {
        *list = tmp->next;
        sfText_destroy(tmp->text);
        free(tmp);
        return;
    }
    while (tmp->next != to_remove)
        tmp = tmp->next;
    tmp->next = to_remove->next;
    sfText_destroy(to_remove->text);
    free(to_remove);
}

void update_credits(rpg_t *rpg)
{
    text_list_t *tmp = rpg->credits->texts;

    if (tmp == NULL)
        return back_to_menu(rpg);
    while (tmp) {
        tmp->pos.y -= 200 * rpg->win->dt;
        if (sfKeyboard_isKeyPressed(sfKeySpace))
            tmp->pos.y -= 300 * rpg->win->dt;
        if (tmp->pos.y < -100) {
            remove_text(&rpg->credits->texts, tmp);
            tmp = rpg->credits->texts;
            continue;
        }
        sfText_setPosition(tmp->text, tmp->pos);
        tmp = tmp->next;
    }
}
