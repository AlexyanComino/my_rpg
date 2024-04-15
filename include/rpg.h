/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** my
*/

#pragma once

#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <stdlib.h>

#define WIDTH 1920
#define HEIGHT 1080

typedef struct win_s {
    sfRenderWindow *window;
    unsigned int width;
    unsigned int height;
} win_t;

typedef struct rpg_s {
    win_t *win;
    sfEvent event;
} rpg_t;

#include "../src/Init/init.h"
#include "../src/Display/display.h"
#include "../src/Event/event.h"
#include "../src/Destroy/destroy.h"
