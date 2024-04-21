/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** damage_text
*/

#include "rpg.h"

static sfVector2f get_damage_text_pos(warrior_t *warrior)
{
    return (sfVector2f){warrior->pos.x + rand() % 50 - 25,
        warrior->pos.y - 50};
}

static float get_damage_text_size(int attack)
{
    if (attack < 10)
        return 20;
    if (attack < 20)
        return 25;
    if (attack < 30)
        return 30;
    return 40;
}

static void init_text_shadow(damage_text_t *new, char *damage_text)
{
    sfFloatRect rect;

    new->text_shadow = sfText_create();
    sfText_setString(new->text_shadow, damage_text);
    sfText_setFont(new->text_shadow, new->font);
    sfText_setCharacterSize(new->text_shadow, new->size);
    sfText_setPosition(new->text_shadow, (sfVector2f){new->pos.x + 2,
        new->pos.y + 2});
    sfText_setColor(new->text_shadow, sfBlack);
    rect = sfText_getGlobalBounds(new->text_shadow);
    sfText_setOrigin(new->text_shadow, (sfVector2f){rect.width / 2,
        rect.height / 2});
}

static damage_text_t *init_damage_text(rpg_t *rpg, warrior_t *warrior,
    char *damage_text, int attack)
{
    damage_text_t *new = malloc(sizeof(damage_text_t));
    sfFloatRect rect;
    sfColor color = WARRIOR_IS_PLAYER(rpg, warrior) ? DAMAGE_COLOR_PLAYER :
        get_color_from_faction(warrior);

    new->text = sfText_create();
    new->font = sfFont_createFromFile("assets/fonts/Say Comic.ttf");
    new->size = get_damage_text_size(attack);
    sfText_setString(new->text, damage_text);
    sfText_setFont(new->text, new->font);
    sfText_setCharacterSize(new->text, new->size);
    new->pos = get_damage_text_pos(warrior);
    sfText_setPosition(new->text, new->pos);
    sfText_setColor(new->text, color);
    rect = sfText_getGlobalBounds(new->text);
    sfText_setOrigin(new->text, (sfVector2f){rect.width / 2, rect.height / 2});
    init_text_shadow(new, damage_text);
    new->next = NULL;
    return new;
}

static char *get_damage_text(int attack)
{
    char *damage_text = calloc(5, sizeof(char));

    if (attack == 0)
        sprintf(damage_text, "MISS");
    else
        sprintf(damage_text, "-%d", attack);
    return damage_text;
}

void add_damage_text(rpg_t *rpg, warrior_t *target, int attack)
{
    char *damage_text = get_damage_text(attack);
    damage_text_t *new = init_damage_text(rpg, target, damage_text, attack);
    damage_text_t *tmp = target->damage_texts;

    if (tmp == NULL) {
        target->damage_texts = new;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}
