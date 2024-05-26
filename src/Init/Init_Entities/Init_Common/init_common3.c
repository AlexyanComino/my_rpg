/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_common3
*/

#include "rpg.h"


static sfVector2f get_back_health_bar_size(entity_type_t type)
{
    type = type;
    return (sfVector2f){76, 16};
}

static sfVector2f get_front_health_bar_size(entity_type_t type)
{
    type = type;
    return (sfVector2f){70, 10};
}

health_bar_t *init_health_bar(entity_type_t type, float scale)
{
    health_bar_t *health_bar = malloc(sizeof(health_bar_t));
    sfVector2f back_size = get_back_health_bar_size(type);
    sfVector2f front_size = get_front_health_bar_size(type);

    back_size.x *= scale;
    back_size.y *= scale;
    front_size.x *= scale;
    front_size.y *= scale;
    health_bar->back = init_round_rectangle((sfVector2f){0, 0}, 7,
        back_size, sfBlack);
    health_bar->front = init_round_rectangle((sfVector2f){0, 0}, 5,
        front_size, sfGreen);
    health_bar->diff_y = 40;
    return health_bar;
}

health_bar_t *init_health_bar_boss(void)
{
    health_bar_t *health_bar = malloc(sizeof(health_bar_t));
    sfVector2f back_size = (sfVector2f){WIDTH / 2 + WIDTH / 8, 80};
    sfVector2f front_size = (sfVector2f){WIDTH / 2 + WIDTH / 8 - 20, 60};

    health_bar->back = init_round_rectangle((sfVector2f){0, 0}, 30,
        back_size, sfBlack);
    health_bar->front = init_round_rectangle((sfVector2f){0, 0}, 20,
        front_size, sfRed);
    health_bar->diff_y = 0;
    return health_bar;
}
