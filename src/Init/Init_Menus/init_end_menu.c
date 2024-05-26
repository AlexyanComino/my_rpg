/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_end_menu
*/

#include "rpg.h"

static sfText *get_title1_end_menu(rpg_t *rpg)
{
    sfText *text = sfText_create();
    sfFloatRect rect;

    sfText_setFont(text, rpg->loading->font);
    sfText_setCharacterSize(text, 300);
    sfText_setString(text, "Game");
    rect = sfText_getGlobalBounds(text);
    sfText_setOrigin(text, (sfVector2f){rect.width / 2, rect.height / 2});
    sfText_setPosition(text, (sfVector2f){WIDTH / 2 - 150, 150});
    sfText_setColor(text, sfColor_fromRGB(129, 0, 0));
    sfText_setOutlineColor(text, sfWhite);
    sfText_setOutlineThickness(text, 4);
    return text;
}

static sfText *get_title2_end_menu(rpg_t *rpg)
{
    sfText *text = sfText_create();
    sfFloatRect rect;

    sfText_setFont(text, rpg->loading->font);
    sfText_setCharacterSize(text, 300);
    sfText_setString(text, "Over");
    rect = sfText_getGlobalBounds(text);
    sfText_setOrigin(text, (sfVector2f){rect.width / 2, rect.height / 2});
    sfText_setPosition(text, (sfVector2f){WIDTH / 2 + 150, 350});
    sfText_setColor(text, sfColor_fromRGB(129, 0, 0));
    sfText_setOutlineColor(text, sfWhite);
    sfText_setOutlineThickness(text, 4);
    return text;
}

static void new_button_end2(button_t *new, sfVector2f pos, char *txt)
{
    sfFloatRect rec;

    sfText_setOutlineColor(new->text, sfWhite);
    sfText_setOutlineColor(new->shadow, sfColor_fromRGBA(255, 255, 255, 0));
    sfText_setOutlineThickness(new->text, 3);
    sfText_setOutlineThickness(new->shadow, 3);
    sfText_setString(new->shadow, txt);
    sfText_setString(new->text, txt);
    rec = sfText_getLocalBounds(new->text);
    sfText_setOrigin(new->text, (sfVector2f){rec.width / 2, rec.height / 2});
    rec = sfText_getLocalBounds(new->shadow);
    sfText_setOrigin(new->shadow, (sfVector2f){rec.width / 2, rec.height / 2});
    sfText_setPosition(new->text, pos);
    sfText_setPosition(new->shadow, (sfVector2f){pos.x + 8, pos.y + 8});
}

static button_t *new_button_end(char *txt, sfVector2f pos, sfFont *font)
{
    button_t *new = malloc(sizeof(button_t));
    sfColor color = sfColor_fromRGB(35, 35, 35);

    new->name = strdup(txt);
    new->text = sfText_create();
    sfText_setFont(new->text, font);
    sfText_setCharacterSize(new->text, 150);
    new->state = NOTHING;
    new->shadow = sfText_create();
    sfText_setFont(new->shadow, font);
    sfText_setCharacterSize(new->shadow, 150);
    new->action = get_action(txt);
    new->color = sfBlack;
    new->click_color = color;
    sfText_setColor(new->text, new->color);
    sfText_setColor(new->shadow, sfColor_fromRGBA(255, 255, 255, 0));
    new_button_end2(new, pos, txt);
    return new;
}

static void add_button_end(button_t **but, sfVector2f pos, char *txt,
    sfFont *font)
{
    button_t *new = new_button_end(txt, pos, font);
    button_t *tmp = *but;

    new->next = NULL;
    while (tmp && tmp->next != NULL)
        tmp = tmp->next;
    if (!tmp)
        *but = new;
    else if (tmp->next == NULL)
        tmp->next = new;
}

end_menu_t *init_end_menu(rpg_t *rpg)
{
    end_menu_t *end_menu = malloc(sizeof(end_menu_t));
    sfText *title1 = get_title1_end_menu(rpg);
    sfText *title2 = get_title2_end_menu(rpg);

    end_menu->title1 = init_anim_text(title1, 0.07, 0.0007, NULL);
    end_menu->title2 = init_anim_text(title2, 0.07, 0.0007, NULL);
    end_menu->buttons = NULL;
    add_button_end(&end_menu->buttons, (sfVector2f){400, 800},
        "Continuer", rpg->loading->font);
    add_button_end(&end_menu->buttons, (sfVector2f){1500, 800},
        "Menu Principal", rpg->loading->font);
    return end_menu;
}
