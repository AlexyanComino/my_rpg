/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_loading
*/

#include "rpg.h"

anim_text_t *init_anim_text(sfText *text, float scale_bonus,
    float transition_speed, sfText *shadow)
{
    anim_text_t *anim_text = malloc(sizeof(anim_text_t));
    float scale_text = sfText_getScale(text).x;

    anim_text->text = text;
    anim_text->scale_dir = 1;
    anim_text->scale_max = scale_text + scale_bonus;
    anim_text->scale_min = scale_text - scale_bonus;
    anim_text->speed = transition_speed;
    anim_text->shadow = shadow;
    if (shadow == NULL) {
        anim_text->shadow = NULL;
        anim_text->has_shadow = false;
    } else {
        anim_text->has_shadow = true;
    }
    return anim_text;
}

static void init_cont_loading(loading_t *loading)
{
    sfFloatRect rect;
    sfText *text = sfText_create();

    loading->cont = malloc(sizeof(continue_t));
    sfText_setFont(text, loading->font);
    sfText_setCharacterSize(text, 80);
    sfText_setString(text, "Press Space to continue");
    rect = sfText_getGlobalBounds(text);
    sfText_setOrigin(text, (sfVector2f){rect.width / 2, rect.height / 2});
    loading->cont->text_pos = (sfVector2f){WIDTH / 2, HEIGHT - 200};
    sfText_setPosition(text, (sfVector2f){WIDTH / 2, HEIGHT + 100});
    sfText_setColor(text, sfBlack);
    sfText_setOutlineColor(text, sfWhite);
    sfText_setOutlineThickness(text, 1);
    loading->cont->is_arrived = false;
    loading->cont->anim_text = init_anim_text(text, 0.07, 0.0005, NULL);
    loading->cont->move_text = false;
}

static sfText *init_title_text_load1(loading_t *loading)
{
    sfText *text = sfText_create();
    sfFloatRect rect;

    sfText_setFont(text, loading->font);
    sfText_setCharacterSize(text, 230);
    sfText_setString(text, "The Blade of");
    rect = sfText_getGlobalBounds(text);
    sfText_setOrigin(text, (sfVector2f){rect.width / 2, rect.height / 2});
    sfText_setPosition(text, (sfVector2f){WIDTH / 2, 350});
    sfText_setColor(text, sfBlack);
    sfText_setOutlineColor(text, sfWhite);
    sfText_setOutlineThickness(text, 3);
    return text;
}

static sfText *init_title_text_load2(loading_t *loading)
{
    sfText *text = sfText_create();
    sfFloatRect rect;

    sfText_setFont(text, loading->font);
    sfText_setCharacterSize(text, 310);
    sfText_setString(text, "Eternity");
    rect = sfText_getGlobalBounds(text);
    sfText_setOrigin(text, (sfVector2f){rect.width / 2, rect.height / 2});
    sfText_setPosition(text, (sfVector2f){WIDTH / 2, 460});
    sfText_setColor(text, sfBlack);
    sfText_setOutlineColor(text, sfWhite);
    sfText_setOutlineThickness(text, 3);
    return text;
}

loading_t *init_loading(void)
{
    loading_t *loading = malloc(sizeof(loading_t));

    loading->font =
        sfFont_createFromFile("assets/fonts/BreatheFireIii-PKLOB.ttf");
    loading->load = init_anim("assets/interface/dots.png", DOTS_WIDTH,
        DOTS_HEIGHT);
    sfSprite_setPosition(loading->load->sprite, (sfVector2f){WIDTH - 150,
        HEIGHT - 100});
    loading->is_loaded = 0;
    loading->myclock = init_my_clock();
    loading->title1 = init_anim_text(init_title_text_load1(loading),
        0.05, 0.0003, NULL);
    loading->title2 = init_anim_text(init_title_text_load2(loading),
        0.05, 0.0003, NULL);
    init_cont_loading(loading);
    return loading;
}
