/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_damages_texts
*/

#include "rpg.h"

static sfVector2f get_damage_text_pos(warrior_t *warrior,
    damage_text_state_t state)
{
    if (state == BAM || state == CRITICAL)
        return (sfVector2f){warrior->pos.x + rand() % 50 - 25,
            warrior->pos.y - 125};
    return (sfVector2f){warrior->pos.x + rand() % 50 - 25,
        warrior->pos.y - 50};
}

static float get_damage_text_size(int attack, damage_text_state_t state)
{
    if (state == BAM || state == CRITICAL)
        return 50;
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

static char *get_damage_text(int attack, damage_text_state_t state)
{
    char *damage_text = calloc(5, sizeof(char));

    if (state == BAM) {
        sprintf(damage_text, "BAM");
        return damage_text;
    }
    if (state == CRITICAL)
        sprintf(damage_text, "CRIT");
    else if (attack == 0)
        sprintf(damage_text, "MISS");
    else
        sprintf(damage_text, "-%d", attack);
    return damage_text;
}

static sfIntRect get_rect_effect(damage_text_state_t state)
{
    if (state == BAM)
        return (sfIntRect){0, 0, BAM_WIDTH, BAM_HEIGHT};
    return (sfIntRect){0, 0, CRIT_WIDTH, CRIT_WIDTH};
}

static void init_effect2(effect_t *new, sfVector2f pos)
{
    sfFloatRect rect = sfSprite_getGlobalBounds(new->sprite);

    sfSprite_setOrigin(new->sprite, (sfVector2f){rect.width / 2,
        rect.height / 2});
    sfSprite_setPosition(new->sprite, (sfVector2f){pos.x - 10, pos.y - 10});
}

static effect_t *init_effect(sfVector2f pos, damage_text_state_t state)
{
    effect_t *new = malloc(sizeof(effect_t));
    char *path = state == BAM ? "assets/Effects/bam.png" :
        "assets/Effects/crit.png";

    if (state != BAM && state != CRITICAL) {
        free(new);
        return NULL;
    }
    new->texture = sfTexture_createFromFile(path, NULL);
    new->sprite = sfSprite_create();
    sfSprite_setTexture(new->sprite, new->texture, sfTrue);
    new->rect = get_rect_effect(state);
    new->myclock = init_my_clock();
    sfSprite_setTextureRect(new->sprite, new->rect);
    sfSprite_setScale(new->sprite, (sfVector2f){0.8, 0.8});
    init_effect2(new, pos);
    return new;
}

static sfColor get_color_damage_text(rpg_t *rpg, warrior_t *warrior,
    damage_text_state_t state)
{
    if (is_player(rpg, warrior))
        return DAMAGE_COLOR_PLAYER;
    if (state == BAM)
        return DAMAGE_COLOR_BAM;
    if (state == CRITICAL)
        return DAMAGE_COLOR_CRITICAL;
    return get_color_from_faction(warrior);
}

static void init_damage_text2(damage_text_t *new, damage_text_state_t state)
{
    new->state = state;
    new->effect = init_effect(new->pos, state);
}

damage_text_t *init_damage_text(rpg_t *rpg, warrior_t *warrior,
    int attack, damage_text_state_t state)
{
    char *damage_text = get_damage_text(attack, state);
    damage_text_t *new = malloc(sizeof(damage_text_t));
    sfFloatRect rect;
    sfColor color = get_color_damage_text(rpg, warrior, state);

    new->text = sfText_create();
    new->font = sfFont_createFromFile("assets/fonts/Say Comic.ttf");
    new->size = get_damage_text_size(attack, state);
    sfText_setString(new->text, damage_text);
    sfText_setFont(new->text, new->font);
    sfText_setCharacterSize(new->text, new->size);
    new->pos = get_damage_text_pos(warrior, state);
    sfText_setPosition(new->text, new->pos);
    sfText_setColor(new->text, color);
    rect = sfText_getGlobalBounds(new->text);
    sfText_setOrigin(new->text, (sfVector2f){rect.width / 2, rect.height / 2});
    init_text_shadow(new, damage_text);
    init_damage_text2(new, state);
    new->next = NULL;
    return new;
}
