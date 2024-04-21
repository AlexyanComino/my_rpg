/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update
*/
#pragma once

// Update_all
void update_all(rpg_t *rpg);

// Update warriors
void update_warriors(rpg_t *rpg);

// Update all warriors
void update_all_warriors(rpg_t *rpg, warrior_t *tmp);

// Warrior move
void warrior_move(rpg_t *rpg, warrior_t *warrior);

// Warrior attack
void update_attack_rect(warrior_t *warrior);
void warrior_attack(rpg_t *rpg, warrior_t *warrior);

// Update pnj warrior
x_warrior_t get_warrior_side(warrior_t *warrior, warrior_t *enemy);
void update_pnj_warrior(rpg_t *rpg, warrior_t *player);

// damage text
void add_damage_text(rpg_t *rpg, warrior_t *target, int attack);

// Warrior x y
void update_side_x(warrior_t *warrior, sfVector2f movement);
void update_side_y(warrior_t *warrior, sfVector2f movement);
void update_warrior_x(rpg_t *rpg, warrior_t *warrior, sfVector2f movement);
void update_warrior_y(rpg_t *rpg, warrior_t *warrior, sfVector2f movement);

// Update warrior detection
void update_warrior_detection(warrior_t *warrior, warrior_t *enemy);

// Update warrior pos
void update_warrior_pos(rpg_t *rpg, warrior_t *tmp, warrior_t *enemy);
