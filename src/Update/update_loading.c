/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_loading
*/

#include "rpg.h"


static bool disappear_anim(anim_t *anim, int speed)
{
    sfColor color = sfSprite_getColor(anim->sprite);

    if (color.a - speed < 0)
        color.a = 0;
    else
        color.a -= speed;
    sfSprite_setColor(anim->sprite, color);
    return (color.a == 0) ? true : false;
}

static void anim_dots(rpg_t *rpg)
{
    update_clock_seconds(rpg->loading->load->myclock);
    if (rpg->loading->load->myclock->seconds < 0.02)
        return;
    if (rpg->loading->load->rect.top >= DOTS_HEIGHT * 12) {
        rpg->loading->load->rect.left += DOTS_WIDTH;
        rpg->loading->load->rect.top = 0;
    } else if (rpg->loading->load->rect.left >= DOTS_WIDTH * 11) {
        rpg->loading->load->rect.left = 0;
        rpg->loading->load->rect.top = 0;
    } else
        rpg->loading->load->rect.top += DOTS_HEIGHT;
    sfSprite_setTextureRect(rpg->loading->load->sprite,
        rpg->loading->load->rect);
    sfClock_restart(rpg->loading->load->myclock->clock);
}

static void move_clic_text(loading_t *loading)
{
    float diff_y = sfText_getPosition(loading->cont->anim_text->text).y -
        loading->cont->text_pos.y;
    float transition_speed = fabs(diff_y) / 15.0f;

    if (!loading->cont->move_text)
        return;
    if (fabs(diff_y) > 0.1) {
        if (diff_y - transition_speed < 0)
            sfText_setPosition(loading->cont->anim_text->text,
                loading->cont->text_pos);
        else
            sfText_move(loading->cont->anim_text->text,
                (sfVector2f){0, -transition_speed});
    } else {
        loading->cont->move_text = false;
        loading->cont->is_arrived = true;
    }
}

void update_loading(rpg_t *rpg)
{
    if (rpg->loading->is_loaded != 2) {
        update_clock_seconds(rpg->loading->myclock);
        if (rpg->loading->myclock->seconds > 12.0) {
            rpg->loading->is_loaded = true;
            rpg->loading->cont->move_text = true;
        }
        anim_dots(rpg);
        if (rpg->loading->is_loaded == 1 &&
            disappear_anim(rpg->loading->load, 3))
            rpg->loading->is_loaded = 2;
    }
    move_clic_text(rpg->loading);
    if (rpg->loading->cont->is_arrived)
        anim_text_anim(rpg->loading->cont->anim_text);
    anim_text_anim(rpg->loading->title1);
    anim_text_anim(rpg->loading->title2);
}
