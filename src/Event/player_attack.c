/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** player_attack
*/

#include "rpg.h"

static void update_attack_rect(warrior_t *warrior)
{
    warrior->rect.left = 0;
    if (warrior->y == NONE)
        warrior->rect.top = WARRIOR_WIDTH * 2;
    if (warrior->y == DOWN)
        warrior->rect.top = WARRIOR_WIDTH * 4;
    if (warrior->y == UP)
        warrior->rect.top = WARRIOR_WIDTH * 6;
}

static void start_dead(warrior_t *warrior)
{
    printf("Warrior is dead\n");
    warrior->state = DEAD;
    warrior->death->dead_pos = (sfVector2f) {warrior->pos.x + WARRIOR_WIDTH / 2
        - DEAD_WIDTH / 2, warrior->pos.y + WARRIOR_WIDTH / 2 - DEAD_WIDTH / 2};
    sfClock_restart(warrior->death->clock_dead->clock);
}

static void decrease_health(warrior_t *player, warrior_t *warrior)
{
    unsigned int max_attack = (player->attributes->attack -
        warrior->attributes->defense);
    unsigned int attack = rand() % max_attack;

    warrior->attributes->health -= attack;
    printf("Health -%d --> %d\n", attack, warrior->attributes->health);
    if (warrior->attributes->health <= 0)
        start_dead(warrior);
}

static void check_attack_collide(rpg_t *rpg, warrior_t *player)
{
    lwarrior_t *tmp = rpg->lwarrior;

    while (tmp != NULL) {
        if (tmp->warrior != player && tmp->warrior->state != DEAD &&
            is_warrior_in_view(rpg, tmp->warrior) &&
        is_warrior_attack_collide(tmp->warrior,
            player->zones->hitbox_attack)) {
            decrease_health(player, tmp->warrior);
        }
        tmp = tmp->next;
    }
}

void player_attack(rpg_t *rpg)
{
    warrior_t *player = rpg->lwarrior->warrior;

    update_attack_rect(player);
    check_attack_collide(rpg, player);
}

void event_player_attack(rpg_t *rpg)
{
    warrior_t *player = rpg->lwarrior->warrior;

    if (rpg->event.type == sfEvtMouseButtonPressed) {
        if (rpg->event.mouseButton.button == sfMouseLeft &&
            player->state == ATTACK) {
            player->max_line_attack = 1;
        }
        if (rpg->event.mouseButton.button == sfMouseLeft &&
            player->state != ATTACK) {
            player->state = ATTACK;
            player->line_attack = 0;
            player->max_line_attack = 0;
            player_attack(rpg);
            sfClock_restart(player->myclock->clock);
        }
    }
}
