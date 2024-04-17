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
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#define WIDTH 1920
#define HEIGHT 1080

typedef enum {
    MAIN_MENU,
    GAME,
    PAUSE,
    SETTINGS,
    END
} state_t;

typedef enum button_state {
    HOVERED,
    CLICKED,
    RELEASED,
    NONE
} button_state_t;

typedef struct button_s {
    char *name;
    sfSprite *sprite;
    sfTexture *texture;
    sfText *text;
    sfFont *font;
    sfIntRect rect;
    button_state_t state;
    void (*action)(void *rpg);
    struct button_s *next;
} button_t;

typedef struct menu_s {
    sfSprite *background;
    sfTexture *background_texture;
    button_t *buttons;
    sfIntRect rect;
    sfFont *font;
} menu_t;

typedef struct win_s {
    sfRenderWindow *window;
    unsigned int width;
    unsigned int height;
} win_t;

typedef struct rpg_s {
    win_t *win;
    sfEvent event;
    menu_t *main_menu;
    menu_t *settings;
    state_t gamestate;
} rpg_t;

#include "../src/Init/init.h"
#include "../src/Display/display.h"
#include "../src/Event/event.h"
#include "../src/Destroy/destroy.h"
#include "../src/Menu/menu.h"
