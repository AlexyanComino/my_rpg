/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_menu_selector
*/

#include "rpg.h"


static char **get_infos(char *txt)
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

static void get_entity(select_button_t *new)
{
    sfVector2f pos = sfRectangleShape_getPosition(new->rect_shape);
    char **infos = get_infos(new->name);

    if (infos != NULL) {
        new->entity = init_entity(infos);
        sfSprite_setScale(new->entity->common->anim->sprite, (sfVector2f){3,
            3});
        sfSprite_setPosition(new->entity->common->anim->sprite,
            (sfVector2f){pos.x, pos.y + 250});
        return free_array(infos);
    }
    new->entity = NULL;
}

static void get_attributes(char *txt, select_button_t *new, char **tab)
{
    char **infos = NULL;

    new->attributes = malloc(sizeof(attributes_t));
    if (!strcmp(txt, "BACK")) {
        free(new->attributes);
        new->attributes = NULL;
    }
    if (strcmp(txt, "WARRIOR") == 0)
        infos = split_string(tab[0], ";");
    if (strcmp(txt, "PAWN") == 0)
        infos = split_string(tab[1], ";");
    if (strcmp(txt, "ARCHER") == 0)
        infos = split_string(tab[5], ";");
    if (strcmp(txt, "TORCH") == 0)
        infos = split_string(tab[3], ";");
    if (strcmp(txt, "TNT") == 0)
        infos = split_string(tab[4], ";");
    if (infos != NULL) {
        new->attributes->health = atoi(infos[8]);
        new->attributes->attack = atoi(infos[9]);
        new->attributes->defense = atoi(infos[10]);
        new->attributes->speed = atoi(infos[11]);
        return free_array(infos);
    }
}

static select_button_t *sel_new_button(char *txt, sfVector2f pos)
{
    select_button_t *new = malloc(sizeof(select_button_t));

    new->name = strdup(txt);
    new->hp = sfText_create();
    new->attack = sfText_create();
    new->defense = sfText_create();
    new->font = sfFont_createFromFile("assets/fonts/CompassPro.ttf");
    new->text = create_text(new->font, txt, 100, pos);
    new->state = NOTHING;
    new->action = get_action(txt);
    new->rect_shape = sfRectangleShape_create();
    new->rect = (sfIntRect){0, 0, BUTTON_WIDTH, BUTTON_HEIGHT};
    new->next = NULL;
    sfText_setFillColor(new->text, sfBlack);
    sfRectangleShape_setSize(new->rect_shape, (sfVector2f){600, 1000});
    sfRectangleShape_setFillColor(new->rect_shape,
        sfColor_fromRGBA(200, 200, 200, 150));
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

static void init_stats(select_button_t *new, sfVector2f pos, char *txt,
    char **tab)
{
    char *str = malloc(sizeof(char) * 10);

    get_attributes(txt, new, tab);
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

static void init_sprites_attributes(select_button_t *new, sfVector2f pos)
{
    init_sprite_from_pos(&new->pp_texture, &new->pp_sprite,
        (sfVector2f){pos.x + 490, pos.y + 500}, "assets/inventory/19.png");
    init_sprite_from_pos(&new->hp_texture, &new->hp_sprite,
        (sfVector2f){pos.x + 80, pos.y + 700}, "assets/item/Misc/Heart.png");
    init_sprite_from_pos(&new->attack_texture, &new->attack_sprite,
        (sfVector2f){pos.x + 80, pos.y + 700 + 130}, "assets/item/Weapon & Tool/Iron Sword.png");
    init_sprite_from_pos(&new->defense_texture, &new->defense_sprite,
        (sfVector2f){pos.x + 80, pos.y + 700 + 130 * 2}, "assets/item/Weapon & Tool/Iron Shield.png");
    init_sprite_from_pos(&new->speed_texture, &new->speed_sprite,
        (sfVector2f){pos.x + 80, pos.y + 700 + 130 * 3}, "assets/item/Equipment/Leather Boot.png");
}

select_button_t *add_select_button(
    select_button_t *buttons, sfVector2f pos, char *txt, char **tab)
{
    select_button_t *new = sel_new_button(txt, pos);
    select_button_t *tmp = buttons;
    sfFloatRect rect;
    sfFloatRect rect2;

    init_stats(new, pos, txt, tab);
    init_sprites_attributes(new, pos);
    get_entity(new);
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

static void create_buttons(rpg_t *rpg, select_menu_t *menu)
{
    char **tab = file_to_array(".entities.csv");
    sfVector2f top_left = {rpg->win->view_pos.x - (WIDTH / 2 * rpg->win->zoom),
        rpg->win->view_pos.y - (HEIGHT / 2 * rpg->win->zoom)};

    menu->buttons = NULL;
    menu->buttons = add_select_button(menu->buttons,
    (sfVector2f){top_left.x + (WIDTH / 2 - 650) * rpg->win->zoom, top_left.y + (HEIGHT / 2 - 300) * rpg->win->zoom}, "WARRIOR", tab);
    add_select_button(menu->buttons,
    (sfVector2f){top_left.x + (WIDTH / 2 - 325) * rpg->win->zoom, top_left.y + (HEIGHT / 2 - 300) * rpg->win->zoom}, "PAWN", tab);
    add_select_button(menu->buttons,
    (sfVector2f){top_left.x + (WIDTH / 2) * rpg->win->zoom, top_left.y + (HEIGHT / 2 - 300) * rpg->win->zoom}, "ARCHER", tab);
    add_select_button(menu->buttons,
    (sfVector2f){top_left.x + (WIDTH / 2 + 325) * rpg->win->zoom, top_left.y + (HEIGHT / 2 - 300) * rpg->win->zoom}, "TORCH", tab);
    add_select_button(menu->buttons,
    (sfVector2f){top_left.x + (WIDTH / 2 + 650) * rpg->win->zoom, top_left.y + (HEIGHT / 2 - 300) * rpg->win->zoom}, "TNT", tab);
    add_select_button(menu->buttons,
    (sfVector2f){top_left.x + (WIDTH / 2) * rpg->win->zoom, top_left.y + (HEIGHT / 2 + 400) * rpg->win->zoom}, "BACK", tab);
}

select_menu_t *init_select_menu(rpg_t *rpg)
{
    select_menu_t *menu = malloc(sizeof(menu_t));

    menu->background_texture = sfTexture_createFromFile(
        "assets/menu/bg.png", NULL);
    menu->background = sfSprite_create();
    sfSprite_setTexture(menu->background, menu->background_texture, sfTrue);
    menu->font = sfFont_createFromFile("assets/fonts/m6x11plus.ttf");
    menu->myclock = NULL;
    menu->text = NULL;
    create_buttons(rpg, menu);
    return menu;
}
