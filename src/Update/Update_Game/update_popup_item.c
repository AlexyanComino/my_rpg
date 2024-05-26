/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_popu_item
*/

#include "rpg.h"

static void set_alpha(sfColor *color, sfColor *outline_color, int diff)
{
    if (color->a + diff <= 0) {
        color->a = 0;
        outline_color->a = 0;
    } else {
        color->a += diff;
        outline_color->a += diff;
    }
}

static void update_text_color(sfText *text, float diff)
{
    sfColor color = sfText_getColor(text);
    sfColor outline_color = sfText_getOutlineColor(text);

    if (diff < 0) {
        set_alpha(&color, &outline_color, diff);
    } else {
        if (color.a + diff >= 255) {
            color.a = 255;
            outline_color.a = 255;
        } else {
            color.a += diff;
            outline_color.a += diff;
        }
    }
    sfText_setColor(text, color);
    sfText_setOutlineColor(text, outline_color);
}

static void update_sprite_color(sfSprite *sprite, int diff)
{
    sfColor color = sfSprite_getColor(sprite);

    if (diff < 0) {
        if (color.a + diff <= 0)
            color.a = 0;
        else
            color.a += diff;
    } else {
        if (color.a + diff >= 255)
            color.a = 255;
        else
            color.a += diff;
    }
    sfSprite_setColor(sprite, color);
}

static void appear_popup_item(popup_item_t *popup)
{
    update_text_color(popup->title->text, 10);
    update_text_color(popup->item_description, 10);
    update_text_color(popup->skip_text, 10);
    update_text_color(popup->rarity, 10);
    update_sprite_color(popup->back_sprite, 10);
    update_sprite_color(popup->item_anim->sprite, 10);
    update_sprite_color(popup->light_sprite, 10);
}

static void disappear_popup_item(popup_item_t *popup)
{
    update_text_color(popup->title->text, -7);
    update_text_color(popup->item_description, -7);
    update_text_color(popup->skip_text, -7);
    update_text_color(popup->rarity, -7);
    update_sprite_color(popup->back_sprite, -7);
    update_sprite_color(popup->light_sprite, -7);
    update_sprite_color(popup->item_anim->sprite, -7);
}

static void destroy_anim_sprite(anim_sprite_t *anim_sprite)
{
    sfSprite_destroy(anim_sprite->sprite);
    sfTexture_destroy(anim_sprite->texture);
    free(anim_sprite);
}

static void desactive_popup_item(rpg_t *rpg, popup_item_t *popup)
{
    popup->display = 0;
    destroy_anim_sprite(popup->item_anim);
    popup->item_anim = NULL;
    update_text_color(popup->title->text, -7);
    update_text_color(popup->item_description, -7);
    update_text_color(popup->skip_text, -7);
    update_text_color(popup->rarity, -7);
    update_sprite_color(popup->back_sprite, -7);
    update_sprite_color(popup->light_sprite, -7);
    get_player(rpg)->common->state = IDLE;
}

static void update_popup_item_color(rpg_t *rpg, popup_item_t *popup)
{
    sfColor color = sfSprite_getColor(popup->item_anim->sprite);

    if (popup->display == 1) {
        appear_popup_item(popup);
    } else {
        if (color.a - 7 > 0)
            disappear_popup_item(popup);
        else
            desactive_popup_item(rpg, popup);
    }
}

static void update_light_rotation(popup_item_t *popup)
{
    float angle = popup->light_angle;

    angle += 0.5;
    if (angle >= 360)
        angle = 0;
    popup->light_angle = angle;
    sfSprite_setRotation(popup->light_sprite, angle);
}

void update_popup_item(rpg_t *rpg)
{
    popup_item_t *popup = rpg->interface->popup_item;

    if (popup->display == 0)
        return;
    anim_text_anim(popup->title);
    anim_sprite_anim(popup->item_anim);
    update_light_rotation(popup);
    update_popup_item_color(rpg, popup);
}
