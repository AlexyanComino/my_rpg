/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** get_anim2
*/

#include "rpg.h"

static char *get_archer_texture_path(color_entity_t color)
{
    char *texture_paths[4] = {
        "assets/Entities/Archer/Archer_Blue.png",
        "assets/Entities/Archer/Archer_Purple.png",
        "assets/Entities/Archer/Archer_Red.png",
        "assets/Entities/Archer/Archer_Yellow.png",
    };
    int color_index = 0;

    if (color == BLUE)
        color_index = 0;
    if (color == PURPLE)
        color_index = 1;
    if (color == RED)
        color_index = 2;
    if (color == YELLOW)
        color_index = 3;
    return strdup(texture_paths[color_index]);
}

anim_t *get_anim_archer(color_entity_t color)
{
    char *texture_path = get_archer_texture_path(color);
    anim_t *anim = init_anim(texture_path, ARCHER_WIDTH, ARCHER_WIDTH);

    free(texture_path);
    return anim;
}
