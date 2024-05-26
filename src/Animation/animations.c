/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** animations
*/

#include "rpg.h"

static void anim_decors(decor_anim_t *decor)
{
    update_clock_seconds(decor->anim->myclock);
    if (decor->anim->myclock->seconds < decor->speed)
        return;
    if (decor->anim->rect.left >= decor->width * decor->nb_cols &&
        decor->anim->rect.top >= decor->height * decor->nb_rows) {
        decor->anim->rect.left = 0;
        decor->anim->rect.top = 0;
    } else if (decor->anim->rect.left >= decor->width * decor->nb_cols) {
        decor->anim->rect.left = 0;
        decor->anim->rect.top += decor->height;
    } else
        decor->anim->rect.left += decor->width;
    sfSprite_setTextureRect(decor->anim->sprite, decor->anim->rect);
    sfClock_restart(decor->anim->myclock->clock);
}

void update_decors_anim(rpg_t *rpg, bool(*in_view)(rpg_t *, sfIntRect))
{
    for (int i = 0; i < (int)rpg->decors_size; i++) {
        if (!in_view(rpg, rpg->decors[i]->rect))
            continue;
        anim_decors(rpg->decors[i]);
    }
}

static void anim_transition2(rpg_t *rpg)
{
    if (rpg->transition->anim->rect.left >= TRANSI_WIDTH && rpg->transition
        ->anim->rect.top >= TRANSI_HEIGHT * 15) {
        rpg->transition->anim->rect.left = 0;
        rpg->transition->anim->rect.top = 0;
    } else if (rpg->transition->anim->rect.top >= TRANSI_HEIGHT * 15) {
        rpg->transition->anim->rect.left += TRANSI_WIDTH;
        rpg->transition->anim->rect.top = 0;
    } else
        rpg->transition->anim->rect.top += TRANSI_HEIGHT;
}

void anim_transition(rpg_t *rpg)
{
    if (!rpg->transition->displayed)
        return;
    update_clock_seconds(rpg->transition->anim->myclock);
    if (rpg->transition->anim->myclock->seconds < 0.06)
        return;
    if (rpg->transition->anim->rect.left >= TRANSI_WIDTH &&
        rpg->transition->anim->rect.top == TRANSI_HEIGHT * 7) {
        rpg->transition->displayed = false;
    }
    if (rpg->transition->anim->rect.left == 0 &&
        rpg->transition->anim->rect.top == TRANSI_HEIGHT * 4) {
        rpg->transition->callback(rpg);
    }
    anim_transition2(rpg);
    sfSprite_setTextureRect(rpg->transition->anim->sprite,
        rpg->transition->anim->rect);
    sfClock_restart(rpg->transition->anim->myclock->clock);
}

void anim_text_anim(anim_text_t *anim_text)
{
    float obj_scale = (anim_text->scale_dir == 1) ? anim_text->scale_max :
        anim_text->scale_min;
    float current_scale = sfText_getScale(anim_text->text).x;
    float diff_scale = obj_scale - current_scale;

    if (fabs(diff_scale) > 0.01) {
        if (anim_text->scale_dir == 1) {
            current_scale += anim_text->speed;
        } else {
            current_scale -= anim_text->speed;
        }
        sfText_setScale(anim_text->text,
            (sfVector2f){current_scale, current_scale});
        if (anim_text->has_shadow)
            sfText_setScale(anim_text->shadow,
                (sfVector2f){current_scale, current_scale});
    } else {
        anim_text->scale_dir = anim_text->scale_dir == 1 ? -1 : 1;
    }
}

void anim_sprite_anim(anim_sprite_t *anim_sprite)
{
    float obj_scale = (anim_sprite->scale_dir == 1) ? anim_sprite->scale_max :
        anim_sprite->scale_min;
    float current_scale = sfSprite_getScale(anim_sprite->sprite).x;
    float diff_scale = obj_scale - current_scale;

    if (fabs(diff_scale) > 0.01) {
        if (anim_sprite->scale_dir == 1) {
            current_scale += anim_sprite->speed;
        } else {
            current_scale -= anim_sprite->speed;
        }
        sfSprite_setScale(anim_sprite->sprite,
            (sfVector2f){current_scale, current_scale});
    } else {
        anim_sprite->scale_dir = anim_sprite->scale_dir == 1 ? -1 : 1;
    }
}
