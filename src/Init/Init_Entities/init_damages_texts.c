/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_damages_texts
*/

#include "rpg.h"

static sfVector2f get_damage_text_pos(entity_t *entity,
    damage_text_state_t state)
{
    if (state == BAM || state == CRITICAL)
        return (sfVector2f){entity->common->pos.x + rand() % 50 - 25,
            entity->common->pos.y - 150};
    return (sfVector2f){entity->common->pos.x + rand() % 50 - 25,
        entity->common->pos.y - 50};
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

static sfColor get_color_damage_text(rpg_t *rpg, entity_t *entity,
    damage_text_state_t state)
{
    if (state == FIRE_TEXT)
        return DAMAGE_COLOR_FIRE;
    if (state == POISON_TEXT)
        return DAMAGE_COLOR_POISON;
    if (is_player(rpg, entity))
        return DAMAGE_COLOR_PLAYER;
    if (state == BAM)
        return DAMAGE_COLOR_BAM;
    if (state == CRITICAL)
        return DAMAGE_COLOR_CRITICAL;
    return get_color_from_faction(entity);
}

static void init_damage_text2(damage_text_t *new, damage_text_state_t state)
{
    char *path = state == BAM ? "assets/Entities/Effects/bam.png" :
        "assets/Entities/Effects/crit.png";
    int width = state == BAM ? BAM_WIDTH : CRIT_WIDTH;
    int height = state == BAM ? BAM_WIDTH : CRIT_WIDTH;
    sfFloatRect rect = sfText_getGlobalBounds(new->text);

    sfText_setOrigin(new->text, (sfVector2f){rect.width / 2, rect.height / 2});
    new->state = state;
    if (state != BAM && state != CRITICAL)
        new->effect = NULL;
    else {
        new->effect = init_anim(path, width, height);
        sfSprite_setScale(new->effect->sprite, (sfVector2f){0.9, 0.9});
        sfSprite_setPosition(new->effect->sprite, (sfVector2f){new->pos.x,
            new->pos.y});
    }
    new->next = NULL;
}

damage_text_t *init_damage_text(rpg_t *rpg, entity_t *entity,
    int attack, damage_text_state_t state)
{
    char *damage_text = get_damage_text(attack, state);
    damage_text_t *new = malloc(sizeof(damage_text_t));
    sfColor color = get_color_damage_text(rpg, entity, state);

    new->text = sfText_create();
    new->font = sfFont_createFromFile("assets/fonts/Say Comic.ttf");
    new->size = get_damage_text_size(attack, state);
    sfText_setString(new->text, damage_text);
    sfText_setFont(new->text, new->font);
    sfText_setCharacterSize(new->text, new->size);
    sfText_setScale(new->text, (sfVector2f){entity->common->scale,
        entity->common->scale});
    sfText_setOutlineThickness(new->text, 2);
    sfText_setOutlineColor(new->text, (entity->common->color == BLACK) ?
        sfWhite : sfBlack);
    new->pos = get_damage_text_pos(entity, state);
    sfText_setPosition(new->text, new->pos);
    sfText_setColor(new->text, color);
    init_damage_text2(new, state);
    return new;
}
