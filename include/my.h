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

/////////////////////////INIT/////////////////////////
// InitRpg
rpg_t *init_rpg(void);

/////////////////////////EVENT/////////////////////////
// Event
void event(rpg_t *rpg);

/////////////////////////DRAW/////////////////////////
// Draw
void draw(rpg_t *rpg);

/////////////////////////DESTROY/////////////////////////
// DestroyRpg
void destroy_rpg(rpg_t *rpg);
