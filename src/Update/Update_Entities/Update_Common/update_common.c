/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_common
*/

#include "rpg.h"

static void check_against_all(rpg_t *rpg, entity_t *entity)
{
    entity_t *other;

    if (!is_alive(entity))
        return;
    if (entity->common->faction == AGAINST_ALL) {
        other = get_nearest_entity(rpg, entity, true);
        if (!other || !hitbox_in_detection(entity->common->zones->hitbox,
            other->common->zones->l_radius, other->common->pos))
            entity->common->faction = entity->common->faction_origin;
    }
}

static void update_name_text_pos(entity_t *entity)
{
    sfVector2f pos = entity->common->pos;

    pos.y -= 50;
    sfText_setPosition(entity->common->name_text, pos);
}

static void update_name_text_boss_pos(rpg_t *rpg, entity_t *entity)
{
    sfVector2f pos = get_player(rpg)->common->pos;
    sfVector2f pos1 = {pos.x, pos.y - HEIGHT / 2 + 110};

    sfText_setPosition(entity->common->name_text, pos1);
}

static void update_list_arrows_hit(entity_t *entity)
{
    arrows_t *tmp = entity->common->arrows_hit;
    arrows_t *prev = NULL;

    if (!tmp)
        return;
    while (tmp) {
        update_clock_seconds(tmp->myclock);
        if (tmp->myclock->seconds >= ARROW_HIT_ENTITY_COOLDOWN) {
            remove_arrow(&entity->common->arrows_hit, tmp, prev);
            tmp = prev;
        }
        if (tmp) {
            tmp->pos = (sfVector2f){entity->common->pos.x + tmp->diff_center.x,
            entity->common->pos.y + tmp->diff_center.y};
            sfSprite_setPosition(tmp->anim->sprite, tmp->pos);
            prev = tmp;
            tmp = tmp->next;
        }
    }
}

void update_grade_icon_pos(entity_t *entity)
{
    sfVector2f pos = entity->common->pos;

    if (entity->common->grade_type == SOLDAT)
        return;
    if (entity->common->grade_type == BOSS) {
        pos.y -= 60 * entity->common->scale;
    } else {
        pos.y -= 80 * entity->common->scale;
    }
    anim_sprite_anim(entity->common->grade_icon);
    sfSprite_setPosition(entity->common->grade_icon->sprite, pos);
}

static void check_respawn_entity(rpg_t *rpg, entity_t *entity)
{
    sfIntRect rect = entity->get_hitbox(entity->common->pos,
        entity->common->scale);

    update_clock_seconds(entity->common->death->anim->myclock);
    if (entity->common->death->anim->myclock->seconds > RESPAWN_TIME &&
        !intrect_is_in_view(rpg, rect)) {
        entity->common->state = IDLE;
        sfClock_restart(entity->common->death->anim->myclock->clock);
    }
}

static void launch_end(rpg_t *rpg)
{
    rpg->gamestate = END;
    sfView_setCenter(rpg->win->view, (sfVector2f){WIDTH / 2, HEIGHT / 2});
    sfSprite_setPosition(rpg->transition->anim->sprite,
        (sfVector2f){WIDTH / 2, HEIGHT / 2});
    sfRenderWindow_setView(rpg->win->window, rpg->win->view);
    rpg->ent[rpg->player_index]->destroy(rpg->ent[rpg->player_index]);
    for (unsigned int i = rpg->player_index; i < rpg->ent_size - 1; i++)
        rpg->ent[i] = rpg->ent[i + 1];
    rpg->ent_size--;
}

static void check_player_game_over(rpg_t *rpg, entity_t *player)
{
    update_clock_seconds(player->common->death->anim->myclock);
    if (player->common->death->anim->myclock->seconds > 3) {
        sfClock_restart(player->common->death->anim->myclock->clock);
        sfSprite_setPosition(rpg->transition->anim->sprite,
            player->common->pos);
        rpg->interface->health_bar->front->r =
            rpg->interface->health_bar->front->init_r;
        launch_transition(rpg, &launch_end);
    }
}

static void update_common2(rpg_t *rpg, entity_t *entity)
{
    if (entity->common->grade_type == BOSS) {
        update_health_bar_boss(rpg, entity);
        update_name_text_boss_pos(rpg, entity);
    }
    if (rpg->modes->plus) {
        if (entity->common->grade_type != BOSS) {
            update_health_bar(entity);
            update_name_text_pos(entity);
        }
    }
}

void update_common(rpg_t *rpg, entity_t *entity)
{
    if (entity->common->state == RIEN)
        return check_respawn_entity(rpg, entity);
    if (is_player(rpg, entity) && entity->common->state == DEAD)
        check_player_game_over(rpg, entity);
    update_damage_texts(&entity->common->damage_texts);
    update_damage_text_effects(&entity->common->damage_texts);
    update_grade_icon_pos(entity);
    update_entity_sprite(entity);
    if (entity->common->state == DEAD)
        return;
    anim_common_effects(entity);
    check_against_all(rpg, entity);
    update_entity_detection(rpg, entity);
    update_effs(rpg, entity);
    update_list_arrows_hit(entity);
    update_common2(rpg, entity);
}
