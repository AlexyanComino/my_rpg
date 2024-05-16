/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_menu_selector
*/

#include "rpg.h"


static void get_texture(char *txt, select_button_t *new)
{
    new->texture = NULL;
    if (strcmp(txt, "WARRIOR") == 0)
        new->texture = sfTexture_createFromFile(
            "assets/Entities/Warriors/Warrior_Blue.png", NULL);
    if (strcmp(txt, "PAWN") == 0)
        new->texture = sfTexture_createFromFile(
            "assets/Entities/Pawn/Pawn_Blue.png", NULL);
    if (strcmp(txt, "ARCHER") == 0)
        new->texture = sfTexture_createFromFile(
            "assets/Entities/Warriors/Warrior_Purple.png", NULL);
    if (strcmp(txt, "TORCH") == 0)
        new->texture = sfTexture_createFromFile(
            "assets/Entities/Torch/Torch_Blue.png", NULL);
    if (strcmp(txt, "TNT") == 0)
        new->texture = sfTexture_createFromFile(
            "assets/Entities/Warriors/Warrior_Red.png", NULL);
    if (new->texture == NULL)
        return;
}

static void get_sprite(select_button_t *new)
{
    sfVector2f pos = sfRectangleShape_getPosition(new->rect_shape);

    get_texture(new->name, new);
    if (new->texture != NULL) {
        new->sprite = sfSprite_create();
        sfSprite_setTexture(new->sprite, new->texture, sfTrue);
        sfSprite_setTextureRect(new->sprite,
            (sfIntRect){0, 0, WARRIOR_WIDTH, WARRIOR_WIDTH});
        sfSprite_setPosition(new->sprite, (sfVector2f){pos.x, pos.y + 150});
        sfSprite_setOrigin(new->sprite,
            (sfVector2f){WARRIOR_WIDTH / 2, WARRIOR_WIDTH / 2});
    }
}

static void get_attributes2(char *txt, select_button_t *new)
{
    if (strcmp(txt, "ARCHER") == 0) {
        new->attributes->health = 100;
        new->attributes->attack = 15;
        new->attributes->defense = 5;
        new->attributes->speed = 5;
    }
    if (strcmp(txt, "TORCH") == 0) {
        new->attributes->health = 75;
        new->attributes->attack = 20;
        new->attributes->defense = 0;
        new->attributes->speed = 5;
    }
    if (strcmp(txt, "TNT") == 0) {
        new->attributes->health = 50;
        new->attributes->attack = 25;
        new->attributes->defense = 0;
        new->attributes->speed = 5;
    }
}

static void get_attributes(char *txt, select_button_t *new)
{
    new->attributes = malloc(sizeof(attributes_t));
    if (strcmp(txt, "WARRIOR") == 0) {
        new->attributes->health = 100;
        new->attributes->attack = 10;
        new->attributes->defense = 10;
        new->attributes->speed = 10;
    }
    if (strcmp(txt, "PAWN") == 0) {
        new->attributes->health = 50;
        new->attributes->attack = 5;
        new->attributes->defense = 5;
        new->attributes->speed = 10;
    }
    get_attributes2(txt, new);
}

static select_button_t *sel_new_button(char *txt, sfVector2f pos)
{
    select_button_t *new = malloc(sizeof(select_button_t));

    new->name = strdup(txt);
    new->hp = sfText_create();
    new->attack = sfText_create();
    new->defense = sfText_create();
    new->font = sfFont_createFromFile("assets/fonts/CompassPro.ttf");
    new->text = create_text(new->font, txt, 50, pos);
    new->state = NOTHING;
    new->action = get_action(txt);
    new->rect_shape = sfRectangleShape_create();
    new->rect = (sfIntRect){0, 0, BUTTON_WIDTH, BUTTON_HEIGHT};
    new->next = NULL;
    sfRectangleShape_setSize(new->rect_shape, (sfVector2f){300, 500});
    sfRectangleShape_setFillColor(new->rect_shape,
        sfColor_fromRGBA(0, 0, 0, 100));
    sfRectangleShape_setPosition(new->rect_shape,
        (sfVector2f){pos.x, pos.y});
    return new;
}

static sfText *create_texte(
    select_button_t *new, char *str, int size, sfVector2f pos)
{
    sfText *text = sfText_create();
    sfFloatRect rect;
    static int i = 0;

    if (i > 150)
        i = 0;
    sfText_setFont(text, new->font);
    sfText_setCharacterSize(text, size);
    sfText_setColor(text, sfWhite);
    sfText_setString(text, str);
    rect = sfText_getGlobalBounds(text);
    sfText_setOrigin(text, (sfVector2f){rect.height / 2, rect.width / 2});
    sfText_setPosition(text, (sfVector2f){pos.x + 300 / 6, pos.y + 240 + i});
    i += 50;
    return text;
}

static void init_stats(select_button_t *new, sfVector2f pos, char *txt)
{
    char *str = calloc(5, sizeof(char));

    get_attributes(txt, new);
    sprintf(str, "%d", new->attributes->health);
    new->hp = create_texte(new, str, 30, pos);
    sprintf(str, "%d", new->attributes->attack);
    new->attack = create_texte(new, str, 30, pos);
    sprintf(str, "%d", new->attributes->defense);
    new->defense = create_texte(new, str, 30, pos);
    sprintf(str, "%d", new->attributes->speed);
    new->speed = create_texte(new, str, 30, pos);
}

select_button_t *add_select_button(
    select_button_t *buttons, sfVector2f pos, char *txt)
{
    select_button_t *new = sel_new_button(txt, pos);
    select_button_t *tmp = buttons;
    sfFloatRect rect;
    sfFloatRect rect2;

    init_stats(new, pos, txt);
    get_sprite(new);
    rect = sfText_getGlobalBounds(new->text);
    rect2 = sfRectangleShape_getGlobalBounds(new->rect_shape);
    sfText_setOrigin(new->text, (sfVector2f){rect.width / 2, rect.height / 2});
    sfRectangleShape_setOrigin(
        new->rect_shape, (sfVector2f){rect2.width / 2, 0});
    if (buttons == NULL)
        return new;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
    return buttons;
}

static void create_buttons(select_menu_t *menu)
{
    menu->buttons = NULL;
    menu->buttons = add_select_button(menu->buttons,
    (sfVector2f){WIDTH / 2 - 650, HEIGHT / 2 - 300}, "WARRIOR");
    add_select_button(menu->buttons,
    (sfVector2f){WIDTH / 2 - 325, HEIGHT / 2 - 300}, "PAWN");
    add_select_button(menu->buttons,
    (sfVector2f){WIDTH / 2, HEIGHT / 2 - 300}, "ARCHER");
    add_select_button(menu->buttons,
    (sfVector2f){WIDTH / 2 + 325, HEIGHT / 2 - 300}, "TORCH");
    add_select_button(menu->buttons,
    (sfVector2f){WIDTH / 2 + 650, HEIGHT / 2 - 300}, "TNT");
    add_select_button(menu->buttons,
    (sfVector2f){WIDTH / 2, HEIGHT / 2 + 400}, "BACK");
}

select_menu_t *init_select_menu(void)
{
    select_menu_t *menu = malloc(sizeof(menu_t));

    menu->background_texture = sfTexture_createFromFile(
        "assets/menu/bg.png", NULL);
    menu->background = sfSprite_create();
    sfSprite_setTexture(menu->background, menu->background_texture, sfTrue);
    menu->font = sfFont_createFromFile("assets/fonts/m6x11plus.ttf");
    menu->myclock = NULL;
    menu->text = NULL;
    create_buttons(menu);
    return menu;
}
