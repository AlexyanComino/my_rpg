/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_text_box
*/

#include "rpg.h"

void set_sprite_transparent(sfSprite *sprite, int alpha)
{
    sfColor color = sfSprite_getColor(sprite);

    color.a = alpha;
    sfSprite_setColor(sprite, color);
}

button_t *new_button(char *txt)
{
    button_t *new = malloc(sizeof(button_t));

    new->name = strdup(txt);
    new->text = sfText_create();
    new->font = sfFont_createFromFile("assets/fonts/FOTRodin Pro DB.otf");
    new->texture = sfTexture_createFromFile(
        "assets/interface/dialog_option_button.png", NULL);
    new->sprite = sfSprite_create();
    set_sprite_transparent(new->sprite, 200);
    new->state = NOTHING;
    new->action = get_action(txt);
    new->rect = (sfIntRect){0, 0, CHOICE_WIDTH, CHOICE_HEIGHT};
    new->rect_shape = NULL;
    new->next = NULL;
    return new;
}

button_t *add_choice(button_t *buttons, char *txt)
{
    button_t *new = new_button(txt);
    button_t *tmp = buttons;

    sfSprite_setTexture(new->sprite, new->texture, sfTrue);
    sfSprite_setScale(new->sprite, (sfVector2f){0.75, 0.75});
    sfSprite_setTextureRect(new->sprite, new->rect);
    sfText_setFont(new->text, new->font);
    sfText_setCharacterSize(new->text, 25);
    sfText_setColor(new->text, sfWhite);
    sfText_setString(new->text, txt);
    if (buttons == NULL)
        return new;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
    return buttons;
}

static button_t *create_choices(void)
{
    button_t *choices = NULL;

    choices = add_choice(choices, "Bien sur!");
    choices = add_choice(choices, "Non merci.");
    choices->state = HOVERED;
    return choices;
}

static void create_text_box_text(text_box_t *text_box)
{
    text_box->font = sfFont_createFromFile("assets/fonts/CompassPro.ttf");
    text_box->npc_name = sfText_create();
    sfText_setFont(text_box->npc_name, text_box->font);
    sfText_setCharacterSize(text_box->npc_name, 43);
    text_box->npc_text = sfText_create();
    sfText_setFont(text_box->npc_text, text_box->font);
    sfText_setCharacterSize(text_box->npc_text, 35);
}

text_box_t *init_text_box(void)
{
    text_box_t *text_box = malloc(sizeof(text_box_t));

    text_box->box_texture = sfTexture_createFromFile(
        "assets/interface/text_box.png", NULL);
    text_box->box = sfSprite_create();
    sfSprite_setTexture(text_box->box, text_box->box_texture, sfTrue);
    sfSprite_setScale(text_box->box, (sfVector2f){0.6, 0.6});
    sfSprite_setOrigin(text_box->box, (sfVector2f){1566 / 2, 391 / 2});
    set_sprite_transparent(text_box->box, 150);
    create_text_box_text(text_box);
    text_box->choice = create_choices();
    text_box->clock = sfClock_create();
    text_box->is_displayed = false;
    text_box->is_fully_displayed = false;
    text_box->str = NULL;
    text_box->displayed_str = NULL;
    text_box->len = 0;
    return text_box;
}
