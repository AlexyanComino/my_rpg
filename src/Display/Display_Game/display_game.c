/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** display_game
*/

#include "rpg.h"

static void display_collision(rpg_t *rpg)
{
    collision_t *coll = rpg->collision;
    entity_t *player = get_player(rpg);
    unsigned int col = player->common->pos.x / WIDTH;
    unsigned int row = player->common->pos.y / HEIGHT;

    if (col >= coll->cols || row >= coll->rows)
        return;
    for (unsigned int i = 0; i < coll->regions[col][row]->size; i++) {
        coll->rect.left = coll->regions[col][row]->pos[i].x;
        coll->rect.top = coll->regions[col][row]->pos[i].y;
        if (!intrect_is_in_view(rpg, coll->rect))
            continue;
        sfRectangleShape_setPosition(coll->shape,
            (sfVector2f){coll->rect.left, coll->rect.top});
        sfRenderWindow_drawRectangleShape(rpg->win->window, coll->shape, NULL);
    }
    sfRectangleShape_setPosition(coll->region_shape,
        (sfVector2f){col * WIDTH, row * HEIGHT});
    sfRenderWindow_drawRectangleShape(rpg->win->window,
        coll->region_shape, NULL);
}

static void display_name_cities(rpg_t *rpg)
{
    minimap_t *minimap = rpg->minimap;

    for (int i = 0; i < minimap->nb_texts; i++)
        sfRenderWindow_drawText(rpg->win->window, minimap->texts[i], NULL);
}

static void display_quests_icons(rpg_t *rpg)
{
    float init_scale = 0;

    for (unsigned int i = 0; i < rpg->ent_size; i++) {
        if (rpg->ent[i]->common->grade_type != SOLDAT_QUEST)
            continue;
        init_scale =
            sfSprite_getScale(rpg->ent[i]->common->grade_icon->sprite).x;
        sfSprite_setScale(rpg->ent[i]->common->grade_icon->sprite,
            (sfVector2f){init_scale * 8, init_scale * 8});
        sfRenderWindow_drawSprite(rpg->win->window,
            rpg->ent[i]->common->grade_icon->sprite, NULL);
        sfSprite_setScale(rpg->ent[i]->common->grade_icon->sprite,
            (sfVector2f){init_scale, init_scale});
    }
}

static void display_minimap(rpg_t *rpg)
{
    minimap_t *minimap = rpg->minimap;

    sfRenderWindow_drawSprite(rpg->win->window, minimap->blur, NULL);
    sfRenderWindow_drawSprite(rpg->win->window, minimap->back, NULL);
    sfRenderWindow_setView(rpg->win->window, minimap->view);
    sfRenderWindow_drawSprite(rpg->win->window, rpg->map->ground_sprite,
        NULL);
    sfRenderWindow_drawSprite(rpg->win->window, rpg->map->high_sprite,
        NULL);
    display_quests_icons(rpg);
    display_name_cities(rpg);
    sfRenderWindow_drawSprite(rpg->win->window, minimap->
        arrow_sprite, NULL);
    sfRenderWindow_setView(rpg->win->window, rpg->win->view);
    sfRenderWindow_drawRectangleShape(rpg->win->window, minimap->rect, NULL);
}

static void display_chests(rpg_t *rpg)
{
    for (unsigned int i = 0; i < rpg->chests_size; i++) {
        if (!intrect_is_in_view(rpg, rpg->chests[i]->rect))
            continue;
        sfRenderWindow_drawSprite(rpg->win->window,
            rpg->chests[i]->anim->sprite, NULL);
        if (rpg->modes->debug)
            sfRenderWindow_drawRectangleShape(rpg->win->window,
                rpg->chests[i]->shape, NULL);
    }
}

static void display_pause_menu(rpg_t *rpg)
{
    sfRenderWindow_drawSprite(rpg->win->window, rpg->pause_menu->back_sprite,
        NULL);
    display_anim_text(rpg, rpg->pause_menu->title);
    for (button_t *tmp = rpg->pause_menu->buttons; tmp; tmp = tmp->next) {
        sfRenderWindow_drawText(rpg->win->window, tmp->shadow, NULL);
        sfRenderWindow_drawText(rpg->win->window, tmp->text, NULL);
    }
}

static void display_normal_game(rpg_t *rpg)
{
    if (rpg->modes->debug)
        display_collision(rpg);
    display_game_interface(rpg);
    display_inv(rpg);
    display_text_box(rpg);
    display_quests(rpg);
    if (rpg->gamestate == MAP)
        display_minimap(rpg);
    if (rpg->gamestate == PAUSE)
        display_pause_menu(rpg);
}

static void display_victory(rpg_t *rpg)
{
    if (rpg->vict->state == MOVE_TEXT || rpg->vict->state == WAIT_REDUCE ||
        rpg->vict->state == REDUCE_VIEW)
        sfRenderWindow_drawText(rpg->win->window, rpg->vict->text, NULL);
}

static void display_health_bar_boss(rpg_t *rpg)
{
    if (rpg->vict->is_win)
        return;
    for (unsigned int i = 0; i < rpg->ent_size; i++) {
        if (rpg->ent[i]->common->grade_type != BOSS ||
            !is_alive(rpg->ent[i]) ||
            !intrect_is_in_real_view(rpg, rpg->ent[i]->common->zones->hitbox))
            continue;
        display_round_rectangle(rpg->win->window,
            rpg->ent[i]->common->health_bar->back);
        display_round_rectangle(rpg->win->window,
            rpg->ent[i]->common->health_bar->front);
        sfRenderWindow_drawText(rpg->win->window,
            rpg->ent[i]->common->name_text, NULL);
    }
}

void display_game(rpg_t *rpg)
{
    if (sfRenderWindow_getView(rpg->win->window) != rpg->win->view)
        sfRenderWindow_setView(rpg->win->window, rpg->win->view);
    sfRenderWindow_drawSprite(rpg->win->window, rpg->map->ground_sprite,
        NULL);
    display_decors_ground(rpg, intrect_is_in_real_view);
    display_chests(rpg);
    display_entities(rpg);
    sfRenderWindow_drawSprite(rpg->win->window, rpg->map->high_sprite,
        NULL);
    display_decors_high(rpg, intrect_is_in_real_view);
    display_high_entities(rpg);
    display_health_bar_boss(rpg);
    if (!rpg->vict->is_win)
        display_normal_game(rpg);
    else {
        display_quests(rpg);
        display_victory(rpg);
    }
}
