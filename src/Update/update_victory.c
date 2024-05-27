/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_victory
*/

#include "rpg.h"


static void init_text_pos(rpg_t *rpg)
{
    rpg->vict->text_pos = get_player(rpg)->common->pos;
    rpg->vict->text_pos.y -= HEIGHT / 2 * rpg->win->zoom;
    rpg->vict->text_pos.x -= 160;
    sfText_setPosition(rpg->vict->text, rpg->vict->text_pos);
}

static void reset_all_entities(rpg_t *rpg)
{
    entity_t *entity = NULL;
    entity_t *player = get_player(rpg);

    player->destroy(player);
    for (unsigned int i = (unsigned int) rpg->player_index;
        i < rpg->ent_size - 1; i++)
        rpg->ent[i] = rpg->ent[i + 1];
    rpg->ent_size--;
    rpg->player_index = UINT_MAX;
    for (unsigned int i = 0; i < rpg->ent_size; i++) {
        entity = rpg->ent[i];
        entity->common->state = IDLE;
        entity->common->attributes->health =
            entity->common->attributes->max_health;
        entity->common->pos = entity->common->init_pos;
    }
    rpg->vict->is_win = false;
}

static void dezoom_view(rpg_t *rpg, float obj_zoom, float adjusted_speed)
{
    rpg->win->zoom -= adjusted_speed;
    if (rpg->win->zoom < obj_zoom) {
        rpg->win->zoom = obj_zoom;
        rpg->gamestate = CREDITS;
        sfView_setCenter(rpg->win->view,
            (sfVector2f){WIDTH / 2, HEIGHT / 2});
        sfView_setSize(rpg->win->view, (sfVector2f){WIDTH, HEIGHT});
        reset_all_entities(rpg);
    }
}

static void resize_view(rpg_t *rpg, float obj_zoom)
{
    float old_zoom = rpg->win->zoom;
    float zoom_diff = fabs(obj_zoom - old_zoom);
    float speed = rpg->win->dt;
    float adjusted_speed = speed * (zoom_diff + 0.1f);

    if (obj_zoom > 1 && rpg->win->zoom < obj_zoom) {
        rpg->win->zoom += adjusted_speed;
        if (rpg->win->zoom > obj_zoom) {
            rpg->win->zoom = obj_zoom;
            rpg->vict->state = MOVE_TEXT;
            init_text_pos(rpg);
        }
    } else if (obj_zoom < 1 && rpg->win->zoom > obj_zoom) {
        dezoom_view(rpg, obj_zoom, adjusted_speed);
    }
    sfView_zoom(rpg->win->view, rpg->win->zoom / old_zoom);
}

static void move_text(rpg_t *rpg)
{
    sfVector2f player_pos = get_player(rpg)->common->pos;
    sfVector2f current_pos = rpg->vict->text_pos;
    float transition_speed = fabs(current_pos.y - player_pos.y) /
        rpg->win->zoom / 2;

    if (current_pos.y < player_pos.y)
        rpg->vict->text_pos.y += transition_speed;
    else
        rpg->vict->text_pos.y -= transition_speed;
    if (fabs(rpg->vict->text_pos.y - player_pos.y) < 500) {
        rpg->vict->state = WAIT_REDUCE;
        sfClock_restart(rpg->vict->myclock->clock);
    }
    sfText_setPosition(rpg->vict->text, rpg->vict->text_pos);
}

static void check_my_clock(rpg_t *rpg)
{
    float second = 0;
    vict_state_t state = rpg->vict->state;

    update_clock_seconds(rpg->vict->myclock);
    second = rpg->vict->myclock->seconds;
    if (state == WAIT_EXTEND && second > 6)
        rpg->vict->state = EXTEND_VIEW;
    if (state == WAIT_REDUCE && second > 3)
        rpg->vict->state = REDUCE_VIEW;
}

static void check_move_text(rpg_t *rpg, vict_t *vict)
{
    if (vict->state == MOVE_TEXT)
        move_text(rpg);
}

void update_victory(rpg_t *rpg)
{
    vict_t *vict = rpg->vict;

    if (vict->state == WAIT_EXTEND || vict->state == WAIT_REDUCE)
        check_my_clock(rpg);
    if (vict->state == EXTEND_VIEW)
        resize_view(rpg, 14);
    else if (vict->state == REDUCE_VIEW)
        resize_view(rpg, 0.3);
    else
        check_move_text(rpg, vict);
    update_chests(rpg);
    update_entities(rpg);
    update_decors_anim(rpg, intrect_is_in_real_view);
}
