/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_menu_save
*/

#include "rpg.h"

static void get_attributes(char *txt, save_button_t *new, save_t *save)
{
    new->attributes = malloc(sizeof(attributes_t));
    if (strcmp(txt, "Retour") == 0) {
        free(new->attributes);
        new->attributes = NULL;
        return;
    }
    if (save != NULL) {
        new->attributes->health = save->attributes->max_health;
        new->attributes->attack = save->attributes->attack;
        new->attributes->defense = save->attributes->defense;
        new->attributes->speed = save->attributes->speed;
    } else {
        new->attributes->health = 0;
        new->attributes->attack = 0;
        new->attributes->defense = 0;
        new->attributes->speed = 0;
    }
}

static void adjust(save_button_t *new, sfVector2f pos)
{
    sfRectangleShape_setSize(new->rect_shape, (sfVector2f){600, 1000});
    sfRectangleShape_setFillColor(new->rect_shape,
        sfColor_fromRGBA(200, 200, 200, 150));
    sfRectangleShape_setPosition(new->rect_shape,
        (sfVector2f){pos.x, pos.y});
}

static save_button_t *save_new_button(char *txt, sfVector2f pos)
{
    save_button_t *new = malloc(sizeof(save_button_t));

    new->name = strdup(txt);
    new->hp = sfText_create();
    new->attack = sfText_create();
    new->defense = sfText_create();
    new->font = sfFont_createFromFile("assets/fonts/CompassPro.ttf");
    new->text = create_text(new->font, txt, 100, pos);
    new->new_txt = create_text(new->font, "NOUVELLE PARTIE", 75, (sfVector2f){
        pos.x, pos.y + 500});
    new->state = NOTHING;
    new->action = get_action(txt);
    new->rect_shape = sfRectangleShape_create();
    new->rect = (sfIntRect){0, 0, BUTTON_WIDTH, BUTTON_HEIGHT};
    new->next = NULL;
    adjust(new, pos);
    return new;
}

static sfText *create_texte(
    save_button_t *new, char *str, int size, sfVector2f pos)
{
    sfText *text = sfText_create();
    sfFloatRect rect;
    static int i = 0;

    if (i > 390)
        i = 0;
    sfText_setFont(text, new->font);
    sfText_setCharacterSize(text, size);
    sfText_setColor(text, sfWhite);
    sfText_setString(text, str);
    rect = sfText_getGlobalBounds(text);
    sfText_setOrigin(text, (sfVector2f){rect.height / 2, rect.width / 2});
    sfText_setPosition(text, (sfVector2f){pos.x + 120, pos.y + 500 + i});
    i += 130;
    return text;
}

static void init_sprite_from_pos(sfTexture **texture, sfSprite **sprite,
    sfVector2f pos, char *path)
{
    sfFloatRect rect;

    *texture = sfTexture_createFromFile(path, NULL);
    *sprite = sfSprite_create();
    sfSprite_setTexture(*sprite, *texture, sfTrue);
    sfSprite_setScale(*sprite, (sfVector2f){4, 4});
    rect = sfSprite_getGlobalBounds(*sprite);
    sfSprite_setOrigin(*sprite, (sfVector2f){rect.width / 2, rect.height / 2});
    sfSprite_setPosition(*sprite, pos);
}

static void init_sprites_attributes(save_button_t *new, sfVector2f pos)
{
    init_sprite_from_pos(&new->pp_texture, &new->pp_sprite,
        (sfVector2f){pos.x + 490, pos.y + 500}, "assets/inventory/19.png");
    init_sprite_from_pos(&new->hp_texture, &new->hp_sprite,
        (sfVector2f){pos.x + 80, pos.y + 700}, "assets/item/Misc/Heart.png");
    init_sprite_from_pos(&new->attack_texture, &new->attack_sprite,
        (sfVector2f){pos.x + 80, pos.y + 700 + 130},
        "assets/item/Weapon & Tool/Iron Sword.png");
    init_sprite_from_pos(&new->defense_texture, &new->defense_sprite,
        (sfVector2f){pos.x + 80, pos.y + 700 + 130 * 2},
        "assets/item/Weapon & Tool/Iron Shield.png");
    init_sprite_from_pos(&new->speed_texture, &new->speed_sprite,
        (sfVector2f){pos.x + 80, pos.y + 700 + 130 * 3},
        "assets/item/Equipment/Leather Boot.png");
}

static void init_stats(
    save_button_t *new, sfVector2f pos, char *txt, save_t *save)
{
    char *str = malloc(sizeof(char) * 10);

    get_attributes(txt, new, save);
    if (new->attributes == NULL)
        return;
    sprintf(str, "%d", new->attributes->health);
    new->hp = create_texte(new, str, 80, pos);
    sprintf(str, "%d", new->attributes->attack);
    new->attack = create_texte(new, str, 80, pos);
    sprintf(str, "%d", new->attributes->defense);
    new->defense = create_texte(new, str, 80, pos);
    sprintf(str, "%d", new->attributes->speed);
    new->speed = create_texte(new, str, 80, pos);
    init_sprites_attributes(new, pos);
}

save_button_t *add_save_button(
    save_button_t *buttons, sfVector2f pos, char *txt, save_t *save)
{
    save_button_t *new = save_new_button(txt, pos);
    save_button_t *tmp = buttons;
    sfFloatRect rect;

    init_stats(new, pos, txt, save);
    if (save != NULL)
        get_entity_save(new, save->type);
    else
        get_entity_save(new, WARRIOR);
    rect = sfText_getGlobalBounds(new->text);
    sfText_setOrigin(new->text, (sfVector2f){rect.width / 2, rect.height / 2});
    rect = sfRectangleShape_getGlobalBounds(new->rect_shape);
    sfRectangleShape_setOrigin(
        new->rect_shape, (sfVector2f){rect.width / 2, 0});
    if (buttons == NULL)
        return new;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
    return buttons;
}

static void create_buttons(rpg_t *rpg, save_menu_t *menu)
{
    sfVector2f top_left = {rpg->win->view_pos.x - (WIDTH / 2 * rpg->win->zoom),
        rpg->win->view_pos.y - (HEIGHT / 2 * rpg->win->zoom)};

    menu->buttons = NULL;
    menu->buttons = add_save_button(menu->buttons,
    (sfVector2f){top_left.x + (WIDTH / 2 - 500) * rpg->win->zoom, top_left.y
    + (HEIGHT / 2 - 300) * rpg->win->zoom}, "Sauvegarde 1", rpg->save[0]);
    add_save_button(menu->buttons,
    (sfVector2f){top_left.x + (WIDTH / 2) * rpg->win->zoom, top_left.y
    + (HEIGHT / 2 - 300) * rpg->win->zoom}, "Sauvegarde 2", rpg->save[1]);
    add_save_button(menu->buttons,
    (sfVector2f){top_left.x + (WIDTH / 2 + 500) * rpg->win->zoom, top_left.y
    + (HEIGHT / 2 - 300) * rpg->win->zoom}, "Sauvegarde 3", rpg->save[2]);
    add_save_button(menu->buttons,
    (sfVector2f){top_left.x + (WIDTH / 2) * rpg->win->zoom, top_left.y
    + (HEIGHT / 2 + 400) * rpg->win->zoom}, "Retour", NULL);
}

save_menu_t *init_save_menu(rpg_t *rpg)
{
    save_menu_t *menu = malloc(sizeof(save_menu_t));

    menu->font = sfFont_createFromFile("assets/fonts/m6x11plus.ttf");
    menu->text = NULL;
    create_buttons(rpg, menu);
    return menu;
}
