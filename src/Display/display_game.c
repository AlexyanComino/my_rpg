/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** display_game
*/

#include "rpg.h"

static void display_restricted_text(rpg_t *rpg)
{
    restricted_t *restricted = rpg->interface->restricted;

    if (!player_is_alive(rpg))
        return;
    sfRenderWindow_drawSprite(rpg->win->window, restricted->sprite, NULL);
}

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
    display_name_cities(rpg);
    sfRenderWindow_drawSprite(rpg->win->window, minimap->
        arrow_sprite, NULL);
    sfRenderWindow_setView(rpg->win->window, rpg->win->view);
    sfRenderWindow_drawRectangleShape(rpg->win->window, minimap->rect, NULL);
}

static void display_health_bar_interface(rpg_t *rpg)
{
    display_round_rectangle(rpg->win->window,
        rpg->interface->health_bar->back);
    display_round_rectangle(rpg->win->window,
        rpg->interface->health_bar->front);
}

void display_game(rpg_t *rpg)
{
    if (sfRenderWindow_getView(rpg->win->window) != rpg->win->view)
        sfRenderWindow_setView(rpg->win->window, rpg->win->view);
    sfRenderWindow_drawSprite(rpg->win->window, rpg->map->ground_sprite,
        NULL);
    display_decors_ground(rpg);
    display_entities(rpg);
    sfRenderWindow_drawSprite(rpg->win->window, rpg->map->high_sprite,
        NULL);
    display_decors_high(rpg);
    if (rpg->debug)
        display_collision(rpg);
    display_inv(rpg);
    display_restricted_text(rpg);
    display_health_bar_interface(rpg);
    display_text_box(rpg);
    display_quests(rpg);
    if (rpg->gamestate == MAP)
        display_minimap(rpg);
}
