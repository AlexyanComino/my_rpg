/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_interface
*/

#include "rpg.h"

static restricted_t *init_restricted(void)
{
    restricted_t *restricted = malloc(sizeof(restricted_t));
    sfFloatRect rect;

    restricted->texture = sfTexture_createFromFile(
        "assets/interface/danger.png", NULL);
    restricted->sprite = sfSprite_create();
    sfSprite_setTexture(restricted->sprite, restricted->texture, sfTrue);
    rect = sfSprite_getGlobalBounds(restricted->sprite);
    sfSprite_setOrigin(restricted->sprite,
        (sfVector2f){rect.width / 2, rect.height / 2});
    sfSprite_setColor(restricted->sprite, (sfColor){255, 255, 255, 0});
    restricted->in_base = false;
    restricted->animation = false;
    return restricted;
}

static health_bar_t *init_health_bar_interface(void)
{
    health_bar_t *health_bar = malloc(sizeof(health_bar_t));
    sfVector2f back_size = {WIDTH / 3, HEIGHT / 30};
    sfVector2f front_size = {WIDTH / 3 - 10, HEIGHT / 30 - 10};

    health_bar->back = init_round_rectangle((sfVector2f){0, 0}, 15,
        back_size, sfBlack);
    health_bar->front = init_round_rectangle((sfVector2f){0, 0}, 10,
        front_size, sfGreen);
    health_bar->front->init_r = 10;
    health_bar->front->init_size = front_size;
    health_bar->front->r = 10;
    return health_bar;
}

static void init_popup_item_text(sfText *text, int size, sfColor color,
    sfColor outline)
{
    sfColor color_png = {color.r, color.g, color.b, 0};
    sfColor outline_png = {outline.r, outline.g, outline.b, 0};

    sfText_setCharacterSize(text, size);
    sfText_setColor(text, color_png);
    sfText_setOutlineThickness(text, 1);
    sfText_setOutlineColor(text, outline_png);
}

static void init_popup_item3(popup_item_t *pop)
{
    pop->display = 0;
    pop->light_angle = 0;
    pop->item_anim = NULL;
}

static void init_popup_item2(popup_item_t *pop)
{
    sfText *text = sfText_create();

    sfSprite_setColor(pop->back_sprite, (sfColor){255, 255, 255, 0});
    pop->font = sfFont_createFromFile("assets/fonts/PoetsenOne-Regular.ttf");
    sfText_setFont(text, pop->font);
    init_popup_item_text(text, 70, sfWhite, sfBlack);
    pop->title = init_anim_text(text, 0.08, 0.003, NULL);
    pop->item_description = sfText_create();
    sfText_setFont(pop->item_description, pop->font);
    init_popup_item_text(pop->item_description, 30, sfWhite, sfBlack);
    sfText_setLineSpacing(pop->item_description, 1.5);
    pop->rarity = sfText_create();
    sfText_setFont(pop->rarity, pop->font);
    init_popup_item_text(pop->rarity, 35, sfWhite, sfBlack);
    pop->skip_text = sfText_create();
    sfText_setFont(pop->skip_text, pop->font);
    sfText_setString(pop->skip_text, "Press E to skip");
    init_popup_item_text(pop->skip_text, 30, sfBlack, sfWhite);
    init_popup_item3(pop);
}

static popup_item_t *init_popup_item(void)
{
    popup_item_t *pop = malloc(sizeof(popup_item_t));
    sfFloatRect rect;

    pop->back_texture = sfTexture_createFromFile(
        "assets/interface/popup_item1.png", NULL);
    pop->back_sprite = sfSprite_create();
    sfSprite_setTexture(pop->back_sprite, pop->back_texture, sfTrue);
    pop->light_texture = sfTexture_createFromFile(
        "assets/interface/light.png", NULL);
    pop->light_sprite = sfSprite_create();
    sfSprite_setTexture(pop->light_sprite, pop->light_texture, sfTrue);
    rect = sfSprite_getGlobalBounds(pop->light_sprite);
    sfSprite_setOrigin(pop->light_sprite,
        (sfVector2f){rect.width / 2, rect.height / 2});
    sfSprite_setScale(pop->light_sprite, (sfVector2f){1.5, 1.5});
    rect = sfSprite_getGlobalBounds(pop->back_sprite);
    sfSprite_setOrigin(pop->back_sprite,
        (sfVector2f){rect.width / 2, rect.height / 2});
    init_popup_item2(pop);
    return pop;
}

static player_infos_t *init_player_infos(void)
{
    player_infos_t *player_infos = malloc(sizeof(player_infos_t));

    player_infos->font =
        sfFont_createFromFile("assets/fonts/PoetsenOne-Regular.ttf");
    player_infos->player_text = sfText_create();
    sfText_setFont(player_infos->player_text, player_infos->font);
    sfText_setCharacterSize(player_infos->player_text, 30);
    sfText_setColor(player_infos->player_text, sfWhite);
    sfText_setOutlineThickness(player_infos->player_text, 2);
    sfText_setOutlineColor(player_infos->player_text, sfBlack);
    return player_infos;
}

interface_t *init_interface(void)
{
    interface_t *interface = malloc(sizeof(interface_t));

    interface->restricted = init_restricted();
    interface->health_bar = init_health_bar_interface();
    interface->popup_item = init_popup_item();
    interface->player_infos = init_player_infos();
    interface->command_list = NULL;
    return interface;
}
