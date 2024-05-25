/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_pause_menu
*/

#include "rpg.h"

static sfText *init_title_pause_text(sfFont *font)
{
    sfText *text = sfText_create();
    sfFloatRect rect;

    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 140);
    sfText_setString(text, "Pause");
    rect = sfText_getGlobalBounds(text);
    sfText_setOrigin(text, (sfVector2f){rect.width / 2, rect.height / 2});
    sfText_setColor(text, sfColor_fromRGB(255, 160, 70));
    sfText_setOutlineColor(text, sfBlack);
    sfText_setOutlineThickness(text, 5);
    return text;
}

static void init_back_menu_pause(pause_menu_t *pause_menu)
{
    sfFloatRect rect;

    pause_menu->back_texture =
        sfTexture_createFromFile("assets/inventory/1.png", NULL);
    pause_menu->back_sprite = sfSprite_create();
    sfSprite_setTexture(pause_menu->back_sprite,
        pause_menu->back_texture, sfTrue);
    rect = sfSprite_getGlobalBounds(pause_menu->back_sprite);
    sfSprite_setOrigin(pause_menu->back_sprite, (sfVector2f){rect.width / 2,
        rect.height / 2});
    sfSprite_setScale(pause_menu->back_sprite, (sfVector2f){2.5, 2.5});
}

static void new_button_pause2(button_t *new, char *txt)
{
    sfFloatRect rect;

    sfText_setString(new->text, txt);
    sfText_setString(new->shadow, txt);
    rect = sfText_getGlobalBounds(new->text);
    sfText_setOrigin(new->text, (sfVector2f){rect.width / 2,
        rect.height / 2});
    sfText_setOrigin(new->shadow, (sfVector2f){rect.width / 2,
        rect.height / 2});
    sfText_setColor(new->text, sfWhite);
    sfText_setColor(new->shadow, sfColor_fromRGBA(0, 0, 0, 0));
    sfText_setOutlineColor(new->text, sfBlack);
    sfText_setOutlineColor(new->shadow, sfColor_fromRGBA(0, 0, 0, 0));
    sfText_setOutlineThickness(new->text, 3);
    sfText_setOutlineThickness(new->shadow, 3);
}

static button_t *new_button_pause(char *txt, sfFont *font)
{
    button_t *new = malloc(sizeof(button_t));

    new->text = sfText_create();
    new->shadow = sfText_create();
    new->color = sfWhite;
    new->name = strdup(txt);
    new->click_color = sfColor_fromRGB(220, 220, 220);
    new->state = NOTHING;
    new->action = get_action(txt);
    sfText_setFont(new->text, font);
    sfText_setFont(new->shadow, font);
    sfText_setCharacterSize(new->text, 95);
    sfText_setCharacterSize(new->shadow, 95);
    new_button_pause2(new, txt);
    return new;
}

static void add_button_pause(button_t **buttons, char *txt, sfFont *font)
{
    button_t *new = new_button_pause(txt, font);
    button_t *tmp = *buttons;

    new->next = NULL;
    while (tmp && tmp->next != NULL)
        tmp = tmp->next;
    if (!tmp)
        *buttons = new;
    else if (tmp->next == NULL)
        tmp->next = new;
}

pause_menu_t *init_pause_menu(void)
{
    pause_menu_t *pause_menu = malloc(sizeof(pause_menu_t));
    sfText *text_title;
    sfText *shadow;

    init_back_menu_pause(pause_menu);
    pause_menu->font =
        sfFont_createFromFile("assets/fonts/BreatheFireIii-PKLOB.ttf");
    text_title = init_title_pause_text(pause_menu->font);
    shadow = sfText_copy(text_title);
    sfText_setColor(shadow, sfBlack);
    sfText_setOutlineColor(shadow, sfBlack);
    sfText_setOutlineThickness(shadow, 5);
    pause_menu->title = init_anim_text(text_title, 0.08, 0.0005, shadow);
    pause_menu->buttons = NULL;
    add_button_pause(&pause_menu->buttons, "Reprendre", pause_menu->font);
    add_button_pause(&pause_menu->buttons, "Sauvegarder", pause_menu->font);
    add_button_pause(&pause_menu->buttons, "Retour au menu", pause_menu->font);
    add_button_pause(&pause_menu->buttons, "Quitter", pause_menu->font);
    return pause_menu;
}

void set_pos_buttons_pause_menu(rpg_t *rpg)
{
    entity_t *player = get_player(rpg);
    sfVector2f pos = {player->common->pos.x, player->common->pos.y - 330};
    button_t *tmp = rpg->pause_menu->buttons;

    sfSprite_setPosition(rpg->pause_menu->back_sprite, player->common->pos);
    sfText_setPosition(rpg->pause_menu->title->text, pos);
    sfText_setPosition(rpg->pause_menu->title->shadow,
        (sfVector2f){pos.x + 7, pos.y + 7});
    pos.y += 230;
    while (tmp) {
        sfText_setPosition(tmp->text, pos);
        sfText_setPosition(tmp->shadow, (sfVector2f){pos.x + 6, pos.y + 6});
        pos.y += 130;
        tmp = tmp->next;
    }
}
