/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** get_anim
*/

#include "rpg.h"

static char *get_warrior_texture_path(color_entity_t color)
{
    char *texture_paths[4] = {
        "assets/Warriors/Warrior_Blue.png",
        "assets/Warriors/Warrior_Purple.png",
        "assets/Warriors/Warrior_Red.png",
        "assets/Warriors/Warrior_Yellow.png",
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

static anim_t *get_anim_warrior(color_entity_t color)
{
    char *texture_path = get_warrior_texture_path(color);
    anim_t *anim = init_anim(texture_path, WARRIOR_WIDTH, WARRIOR_WIDTH);

    free(texture_path);
    return anim;
}

anim_t *get_anim(entity_type_t type, color_entity_t color)
{
    if (type == WARRIOR)
        return get_anim_warrior(color);
    return NULL;
}
