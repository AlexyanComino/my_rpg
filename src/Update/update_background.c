/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_background
*/

#include "rpg.h"

// void update_background(rpg_t *rpg)
// {
//     rpg->main_menu->myclock->time =
//         sfClock_getElapsedTime(rpg->main_menu->myclock->clock);
//     rpg->main_menu->myclock->seconds =
//         rpg->main_menu->myclock->time.microseconds / 1000000.0;
//     if (rpg->main_menu->myclock->seconds > 0.1) {
//         if (rpg->main_menu->bg_rect.top >= 1080 * 5)
//             rpg->main_menu->bg_rect.top = 0;
//         else
//             rpg->main_menu->bg_rect.top += 1080;
//         sfSprite_setTextureRect(
//             rpg->main_menu->background, rpg->main_menu->bg_rect);
//         sfClock_restart(rpg->main_menu->myclock->clock);
//     }
// }
