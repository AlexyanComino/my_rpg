/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_map
*/

#include "rpg.h"

bool is_valid_minimap_view_pos(minimap_t *minimap, sfVector2f new_pos)
{
    if (new_pos.x - (minimap->size / 2 * minimap->zoom) > 11.5 * TILE_SIZE &&
        new_pos.y - (minimap->size / 2 * minimap->zoom) > 0 &&
        new_pos.x + (minimap->size / 2 * minimap->zoom) < MAP_WIDTH *
            TILE_SCALE - 11.5 * TILE_SIZE &&
        new_pos.y + (minimap->size / 2 * minimap->zoom) < MAP_HEIGHT *
            TILE_SCALE) {
        return true;
    }
    return false;
}

static void get_valid_minimap_view_pos(minimap_t *minimap, sfVector2f new_pos)
{
    if (new_pos.x - (minimap->size / 2 * minimap->zoom) < 11.5 * TILE_SIZE)
        new_pos.x = minimap->size / 2 * minimap->zoom + 11.5 * TILE_SIZE;
    if (new_pos.y - (minimap->size / 2 * minimap->zoom) < 0)
        new_pos.y = minimap->size / 2 * minimap->zoom;
    if (new_pos.x + (minimap->size / 2 * minimap->zoom) > MAP_WIDTH *
        TILE_SCALE - 11.5 * TILE_SIZE)
        new_pos.x = MAP_WIDTH * TILE_SCALE - 11.5 * TILE_SIZE -
            minimap->size / 2 * minimap->zoom;
    if (new_pos.y + (minimap->size / 2 * minimap->zoom) > MAP_HEIGHT *
        TILE_SCALE)
        new_pos.y =
            MAP_HEIGHT * TILE_SCALE - minimap->size / 2 * minimap->zoom;
    sfView_setCenter(minimap->view, new_pos);
}

static void init_minimap_pos(rpg_t *rpg, entity_t *player)
{
    minimap_t *minimap = rpg->minimap;

    sfRectangleShape_setPosition(minimap->rect, player->common->pos);
    sfView_zoom(minimap->view, 10 / minimap->zoom);
    update_text_cities_size(rpg, 10 / minimap->zoom);
    minimap->zoom = 10;
    if (!is_valid_minimap_view_pos(minimap, player->common->pos)) {
        get_valid_minimap_view_pos(minimap, player->common->pos);
    } else
        sfView_setCenter(minimap->view, player->common->pos);
    sfSprite_setPosition(minimap->blur, player->common->pos);
    sfSprite_setPosition(minimap->back, player->common->pos);
    minimap->pos = (sfVector2f){0, 0};
    minimap->is_drag = false;
}

static void init_arrow_rotation(minimap_t *minimap, float angle)
{
    minimap->rotation = angle;
    sfSprite_setRotation(minimap->arrow_sprite, minimap->rotation);
}

static void init_arrow_map2(rpg_t *rpg)
{
    minimap_t *minimap = rpg->minimap;
    bool top = sfKeyboard_isKeyPressed(sfKeyZ);
    bool right = sfKeyboard_isKeyPressed(sfKeyD);
    bool left = sfKeyboard_isKeyPressed(sfKeyQ);
    bool down = sfKeyboard_isKeyPressed(sfKeyS);

    if (!top && !right && left && down && minimap->rotation != -135)
        return init_arrow_rotation(minimap, -135);
    if (top && !right && !left && !down && minimap->rotation != 0)
        return init_arrow_rotation(minimap, 0);
    if (!top && right && !left && !down && minimap->rotation != 90)
        return init_arrow_rotation(minimap, 90);
    if (!top && !right && left && !down && minimap->rotation != 270)
        return init_arrow_rotation(minimap, 270);
    if (!top && !right && !left && down && minimap->rotation != 180)
        return init_arrow_rotation(minimap, 180);
}

static void init_arrow_map(rpg_t *rpg, entity_t *player)
{
    minimap_t *minimap = rpg->minimap;
    bool top = sfKeyboard_isKeyPressed(sfKeyZ);
    bool right = sfKeyboard_isKeyPressed(sfKeyD);
    bool left = sfKeyboard_isKeyPressed(sfKeyQ);
    bool down = sfKeyboard_isKeyPressed(sfKeyS);

    sfSprite_setPosition(minimap->arrow_sprite, player->common->pos);
    if (!top && !right && !left && !down) {
        if (player->common->x == RIGHT)
            return init_arrow_rotation(minimap, 90);
        else
            return init_arrow_rotation(minimap, 270);
    }
    if (top && right && !left && !down && minimap->rotation != 45)
        return init_arrow_rotation(minimap, 45);
    if (top && !right && left && !down && minimap->rotation != -45)
        return init_arrow_rotation(minimap, -45);
    if (!top && right && !left && down && minimap->rotation != 135)
        return init_arrow_rotation(minimap, 135);
    init_arrow_map2(rpg);
}

void init_map_pos(rpg_t *rpg)
{
    entity_t *player = get_player(rpg);

    init_minimap_pos(rpg, player);
    init_arrow_map(rpg, player);
}

void update_map(rpg_t *rpg)
{
    entity_t *entity = NULL;

    for (unsigned int i = 0; i < rpg->ent_size; i++) {
        if (rpg->ent[i]->common->grade_type != SOLDAT_QUEST)
            continue;
        entity = rpg->ent[i];
        update_grade_icon_pos(entity);
    }
}
