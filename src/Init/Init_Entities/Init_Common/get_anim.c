/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** get_anim
*/

#include "rpg.h"

static char *get_warrior_texture_path(color_entity_t color)
{
    char *texture_paths[5] = {
        "assets/Entities/Warriors/Warrior_Blue.png",
        "assets/Entities/Warriors/Warrior_Purple.png",
        "assets/Entities/Warriors/Warrior_Red.png",
        "assets/Entities/Warriors/Warrior_Yellow.png",
        "assets/Entities/Warriors/Warrior_Black.png",
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
    if (color == BLACK)
        color_index = 4;
    return strdup(texture_paths[color_index]);
}

static anim_t *get_anim_warrior(color_entity_t color)
{
    char *texture_path = get_warrior_texture_path(color);
    anim_t *anim = init_anim(texture_path, WARRIOR_WIDTH, WARRIOR_WIDTH);

    free(texture_path);
    return anim;
}

static char *get_pawn_texture_path(color_entity_t color)
{
    char *texture_paths[4] = {
        "assets/Entities/Pawn/Pawn_Blue.png",
        "assets/Entities/Pawn/Pawn_Purple.png",
        "assets/Entities/Pawn/Pawn_Red.png",
        "assets/Entities/Pawn/Pawn_Yellow.png",
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

static anim_t *get_anim_pawn(color_entity_t color)
{
    char *texture_path = get_pawn_texture_path(color);
    anim_t *anim = init_anim(texture_path, PAWN_WIDTH, PAWN_WIDTH);

    free(texture_path);
    return anim;
}

static char *get_torch_texture_path(color_entity_t color)
{
    char *texture_paths[5] = {
        "assets/Entities/Torch/Torch_Blue.png",
        "assets/Entities/Torch/Torch_Purple.png",
        "assets/Entities/Torch/Torch_Red.png",
        "assets/Entities/Torch/Torch_Yellow.png",
        "assets/Entities/Torch/Torch_Black.png"
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
    if (color == BLACK)
        color_index = 4;
    return strdup(texture_paths[color_index]);
}

static anim_t *get_anim_torch(color_entity_t color)
{
    char *texture_path = get_torch_texture_path(color);
    anim_t *anim = init_anim(texture_path, TORCH_WIDTH, TORCH_WIDTH);

    free(texture_path);
    return anim;
}

static char *get_tnt_texture_path(color_entity_t color)
{
    char *texture_paths[4] = {
        "assets/Entities/Tnt/TNT_Blue.png",
        "assets/Entities/Tnt/TNT_Purple.png",
        "assets/Entities/Tnt/TNT_Red.png",
        "assets/Entities/Tnt/TNT_Yellow.png",
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

static anim_t *get_anim_tnt(color_entity_t color)
{
    char *texture_path = get_tnt_texture_path(color);
    anim_t *anim = init_anim(texture_path, TNT_WIDTH, TNT_WIDTH);

    free(texture_path);
    return anim;
}

anim_t *get_anim(entity_type_t type, color_entity_t color)
{
    if (type == WARRIOR)
        return get_anim_warrior(color);
    if (type == PAWN)
        return get_anim_pawn(color);
    if (type == TORCH)
        return get_anim_torch(color);
    if (type == TNT)
        return get_anim_tnt(color);
    if (type == ARCHER)
        return get_anim_archer(color);
    return NULL;
}
