/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** add_command
*/

#include "rpg.h"

static sfText *get_action_text_from_str(char *action_str, sfFont *font,
    float zoom)
{
    sfText *text = sfText_create();
    sfFloatRect rect;

    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 28);
    sfText_setColor(text, sfWhite);
    sfText_setOutlineThickness(text, 2);
    sfText_setOutlineColor(text, sfBlack);
    set_string_to_text(text, action_str);
    rect = sfText_getGlobalBounds(text);
    sfText_setOrigin(text, (sfVector2f){rect.width, rect.height / 2});
    sfText_setScale(text, (sfVector2f){zoom, zoom});
    return text;
}

static char *get_texture_path_from_str2(char *action_str)
{
    if (!strcmp(action_str, "Retour au jeu"))
        return "assets/interface/Clavier/escape_light.png";
    if (!strcmp(action_str, "Sélectionner"))
        return "assets/interface/Clavier/left_mouse_button_light.png";
    if (!strcmp(action_str, "Zoom"))
        return "assets/interface/Clavier/scroll_up_down_light.png";
    if (!strcmp(action_str, "Déplacer"))
        return "assets/interface/Clavier/mouse_light.png";
    if (!strcmp(action_str, "Étourdir"))
        return "assets/interface/Clavier/a_key_light.png";
    if (!strcmp(action_str, "Émote"))
        return "assets/interface/Clavier/r_light.png";
    fprintf(stderr, "Error: action not found\n");
    return NULL;
}

static char *get_texture_path_from_str(char *action_str)
{
    if (!strcmp(action_str, "Interagir"))
        return "assets/interface/Clavier/e_light.png";
    if (!strcmp(action_str, "Carte"))
        return "assets/interface/Clavier/t_light.png";
    if (!strcmp(action_str, "Marcher"))
        return "assets/interface/Clavier/shift_light.png";
    if (!strcmp(action_str, "Attaquer"))
        return "assets/interface/Clavier/space_light.png";
    if (!strcmp(action_str, "Inventaire") ||
        !strcmp(action_str, "Revenir au jeu"))
        return "assets/interface/Clavier/tab_light.png";
    if (!strcmp(action_str, "Zoom +"))
        return "assets/interface/Clavier/+_light.png";
    if (!strcmp(action_str, "Zoom -"))
        return "assets/interface/Clavier/-_light.png";
    if (!strcmp(action_str, "Déplacement"))
        return "assets/interface/Clavier/arrows.png";
    if (!strcmp(action_str, "Supprimer"))
        return "assets/interface/Clavier/backspace_light.png";
    return get_texture_path_from_str2(action_str);
}

static command_list_t *get_command_help(char *action_str, sfFont *font,
    float zoom)
{
    command_list_t *new = malloc(sizeof(command_list_t));
    char *texture_path = get_texture_path_from_str(action_str);
    sfFloatRect rect;

    new->action = get_action_text_from_str(action_str, font, zoom);
    new->sprite = sfSprite_create();
    new->texture = sfTexture_createFromFile(texture_path, NULL);
    sfSprite_setTexture(new->sprite, new->texture, sfTrue);
    rect = sfSprite_getGlobalBounds(new->sprite);
    sfSprite_setOrigin(new->sprite, (sfVector2f){rect.width,
        rect.height / 2});
    if (!strcmp(action_str, "Déplacement"))
        sfSprite_setScale(new->sprite, (sfVector2f){0.5 * zoom, 0.5 * zoom});
    else
        sfSprite_setScale(new->sprite, (sfVector2f){0.8 * zoom, 0.8 * zoom});
    return new;
}

void add_command_help(command_list_t **command_list, char *action_str,
    sfFont *font, float zoom)
{
    command_list_t *new = get_command_help(action_str, font, zoom);
    command_list_t *tmp = *command_list;

    new->next = NULL;
    if (*command_list == NULL) {
        *command_list = new;
        return;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
}

void delete_command_help(command_list_t **command_list)
{
    command_list_t *tmp = *command_list;
    command_list_t *next;

    while (tmp != NULL) {
        next = tmp->next;
        sfSprite_destroy(tmp->sprite);
        sfTexture_destroy(tmp->texture);
        sfText_destroy(tmp->action);
        free(tmp);
        tmp = next;
    }
    *command_list = NULL;
}

void set_command_pos(command_list_t *command_list, sfVector2f position,
    float zoom)
{
    command_list_t *tmp = command_list;
    sfVector2f pos = (sfVector2f){position.x + (935 * zoom),
        position.y + (500 * zoom)};
    sfVector2f posText = (sfVector2f){0, 0};
    sfFloatRect rect;

    while (tmp != NULL) {
        rect = sfSprite_getGlobalBounds(tmp->sprite);
        posText = (sfVector2f){pos.x - rect.width - (18 * zoom), pos.y};
        sfSprite_setPosition(tmp->sprite, pos);
        sfText_setPosition(tmp->action, posText);
        pos.y -= (50 * zoom);
        tmp = tmp->next;
    }
}
