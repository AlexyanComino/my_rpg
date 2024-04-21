/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** *
*/

#include "rpg.h"

static sfVector2f get_exclam_pos(warrior_t *warrior)
{
    if (warrior->x == RIGHT) {
        return (sfVector2f){warrior->pos.x + WARRIOR_WIDTH / 4,
            warrior->pos.y - WARRIOR_WIDTH / 3};
    } else {
        return (sfVector2f){warrior->pos.x - WARRIOR_WIDTH / 4,
            warrior->pos.y - WARRIOR_WIDTH / 3};
    }
}

static sfVector2f get_inter_pos(warrior_t *warrior)
{
    if (warrior->x == RIGHT)
        return (sfVector2f){warrior->pos.x + WARRIOR_WIDTH / 4,
            warrior->pos.y - WARRIOR_WIDTH / 3};
    else
        return (sfVector2f){warrior->pos.x - WARRIOR_WIDTH / 4,
            warrior->pos.y - WARRIOR_WIDTH / 3};
}

static void update_exclam_pos(warrior_t *warrior)
{
    warrior->exclam->pos = get_exclam_pos(warrior);
    sfSprite_setPosition(warrior->exclam->sprite, warrior->exclam->pos);
}

static void update_inter_pos(warrior_t *warrior)
{
    warrior->inter->pos = get_inter_pos(warrior);
    sfSprite_setPosition(warrior->inter->sprite, warrior->inter->pos);
}

static bool enemy_is_in_exclamation_range(warrior_t *warrior, warrior_t *enemy)
{
    if (enemy == NULL)
        return false;
    if (!warrior_look_at_enemy(warrior, enemy) && IS_DISCREET(enemy))
        return false;
    if (hitbox_in_detection(enemy->zones->hitbox, warrior->exclam->radius,
        warrior->pos))
        return true;
    return false;
}

static bool cooldown_is_over(mark_t *mark, float cooldown)
{
    return mark->myclock->seconds > cooldown;
}

static void update_exclam_detection(warrior_t *warrior, warrior_t *enemy,
    bool in_base)
{
    if (enemy_is_in_exclamation_range(warrior, enemy) && in_base) {
        warrior->exclam->is_detecting = true;
        if (warrior->exclam->is_display == 0) {
            warrior->exclam->is_display = 1;
            warrior->exclam->rect.left = 0;
            warrior->exclam->rect.top = 0;
            update_exclam_pos(warrior);
        }
    } else {
        update_clock_seconds(warrior->exclam->myclock);
        warrior->exclam->is_detecting = false;
        if (warrior->exclam->is_display == 2 &&
            cooldown_is_over(warrior->exclam, EXCLAM_COOLDOWN))
            warrior->exclam->is_display = 0;
    }
}

static void update_inter_detection(warrior_t *warrior, warrior_t *enemy,
    bool in_base)
{
    update_clock_seconds(warrior->inter->myclock);
    if (warrior_see_enemy(warrior, enemy)) {
        warrior->inter->is_detecting = true;
        if (warrior->inter->is_display == 0 || (warrior->inter->is_display == 2
            && cooldown_is_over(warrior->inter, INTER_INTERVAL) &&
            (!enemy_is_in_exclamation_range(warrior, enemy) || !in_base))) {
            warrior->inter->is_display = 1;
            warrior->inter->rect.left = 0;
            warrior->inter->rect.top = 0;
            update_inter_pos(warrior);
        }
    } else {
        warrior->inter->is_detecting = false;
        if (warrior->inter->is_display == 2 &&
            cooldown_is_over(warrior->inter, INTER_COOLDOWN))
            warrior->inter->is_display = 0;
    }
}

void update_warrior_detection(warrior_t *warrior, warrior_t *enemy)
{
    bool in_base = WARRIOR_HAS_BASE(warrior) &&
        sfIntRect_intersects(&warrior->base->rect, &enemy->zones->hitbox,
        NULL);

    if (!in_base && !WARRIOR_HAS_BASE(warrior))
        in_base = true;
    update_exclam_detection(warrior, enemy, in_base);
    update_inter_detection(warrior, enemy, in_base);
}
