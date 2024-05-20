/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_tnt
*/
#pragma once

// Init Tnt
sfVector2f* get_points_parabol(float velocity, float angle, float gravity);
sfConvexShape *get_parabol_curve(sfVector2f *points, int nb_points);
entity_t *init_entity_tnt(char **infos);
