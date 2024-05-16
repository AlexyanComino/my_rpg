/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_archer
*/

#include "rpg.h"

static void change_current_arrow(entity_t *entity, arrows_t *tmp_arrows,
    arrows_t *prev_arrows)
{
    if (prev_arrows) {
        prev_arrows->next = tmp_arrows->next;
    } else {
        entity->spe->archer->arrows = tmp_arrows->next;
    }
}

static void change_arrow_list(entity_t *entity, entity_t *target,
    arrows_t *arrow)
{
    arrows_t *tmp_arrows_hit = target->common->arrows_hit;
    arrows_t *tmp_arrows = entity->spe->archer->arrows;
    arrows_t *prev_arrows = NULL;

    arrow->next = NULL;
    while (tmp_arrows_hit && tmp_arrows_hit->next)
        tmp_arrows_hit = tmp_arrows_hit->next;
    if (!tmp_arrows_hit)
        target->common->arrows_hit = arrow;
    else
        tmp_arrows_hit->next = arrow;
    while (tmp_arrows) {
        if (tmp_arrows == arrow) {
            change_current_arrow(entity, tmp_arrows, prev_arrows);
            return;
        }
        prev_arrows = tmp_arrows;
        tmp_arrows = tmp_arrows->next;
    }
}

static void check_arrow_damage(rpg_t *rpg, entity_t *entity, arrows_t *arrow)
{
    for (unsigned int i = 0; i < rpg->ent_size; i++) {
        if (!is_alive(rpg->ent[i]) ||
            !rpg->ent[i]->in_view || rpg->ent[i] == entity)
            continue;
        if (sfIntRect_contains(&rpg->ent[i]->common->zones->hitbox,
            arrow->pos.x, arrow->pos.y)) {
            decrease_health(rpg, entity, rpg->ent[i]);
            arrow->state = HIT_ARROW;
            arrow->anim->rect.top += ARROW_WIDTH;
            sfSprite_setTextureRect(arrow->anim->sprite, arrow->anim->rect);
            sfClock_restart(arrow->myclock->clock);
            arrow->diff_center = (sfVector2f){arrow->pos.x -
                rpg->ent[i]->common->pos.x,
                arrow->pos.y - rpg->ent[i]->common->pos.y};
            change_arrow_list(entity, rpg->ent[i], arrow);
            return;
        }
    }
}

static void move_arrow(rpg_t *rpg, entity_t *entity, arrows_t *arrow)
{
    float distance = get_distance(arrow->pos, arrow->end);

    if (distance < 20) {
        arrow->state = HIT_ARROW;
        arrow->anim->rect.top += ARROW_WIDTH;
        sfSprite_setTextureRect(arrow->anim->sprite, arrow->anim->rect);
        sfClock_restart(arrow->myclock->clock);
    } else {
        arrow->pos = (sfVector2f){arrow->pos.x + arrow->dir.x,
        arrow->pos.y + arrow->dir.y};
        sfSprite_setPosition(arrow->anim->sprite, arrow->pos);
        check_arrow_damage(rpg, entity, arrow);
    }
}

void remove_arrow(arrows_t **head, arrows_t *tmp, arrows_t *prev)
{
    if (prev) {
        prev->next = tmp->next;
    } else {
        *head = tmp->next;
    }
    destroy_anim(tmp->anim);
    sfClock_destroy(tmp->myclock->clock);
    free(tmp);
}

static void check_arrow_hit(arrows_t *arrow, arrows_t **head)
{
    arrows_t *tmp = *head;
    arrows_t *prev = NULL;

    while (tmp) {
        update_clock_seconds(arrow->myclock);
        if (arrow->myclock->seconds < ARROW_COOLDOWN) {
            prev = tmp;
            tmp = tmp->next;
            continue;
        }
        if (tmp == arrow)
            return remove_arrow(head, tmp, prev);
        prev = tmp;
        tmp = tmp->next;
    }
}

static void update_arrows(rpg_t *rpg, entity_t *entity)
{
    arrows_t *tmp = entity->spe->archer->arrows;

    while (tmp) {
        if (tmp->state == FLY_ARROW)
            move_arrow(rpg, entity, tmp);
        else
            check_arrow_hit(tmp, &entity->spe->archer->arrows);
        tmp = tmp->next;
    }
}

void update_archer(void *vrpg, entity_t *entity)
{
    rpg_t *rpg = vrpg;

    if (entity->common->state == RIEN)
        return;
    update_common(rpg, entity);
    if (!is_player(rpg, entity) && is_alive(entity))
        update_pnj_archer(rpg, entity);
    update_arrows(rpg, entity);
    anim_archer(rpg, entity);
}
