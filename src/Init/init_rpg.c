/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_rpg
*/

#include "rpg.h"

static win_t *init_win(unsigned int width, unsigned int height)
{
    win_t *win = malloc(sizeof(win_t));
    sfVideoMode mode = {width, height, 32};

    win->window = sfRenderWindow_create(mode, "My_RPG", sfDefaultStyle, NULL);
    win->view = sfView_createFromRect((sfFloatRect){0, 0, width, height});
    sfView_setViewport(win->view, (sfFloatRect){0, 0, 1, 1});
    sfRenderWindow_setView(win->window, win->view);
    win->width = width;
    win->height = height;
    win->framerate = 60;
    win->clock = sfClock_create();
    sfRenderWindow_setFramerateLimit(win->window, win->framerate);
    return win;
}

static map_t *init_map(void)
{
    map_t *map = malloc(sizeof(map_t));

    map->ground_texture = sfTexture_createFromFile("assets/menu/bg.jpg", NULL);
    map->ground_sprite = sfSprite_create();
    sfSprite_setTexture(map->ground_sprite, map->ground_texture, sfTrue);
    sfSprite_setScale(map->ground_sprite,
        (sfVector2f){TILE_SCALE, TILE_SCALE});
    map->high_texture = sfTexture_createFromFile("assets/menu/bg.jpg", NULL);
    map->high_sprite = sfSprite_create();
    sfSprite_setTexture(map->high_sprite, map->high_texture, sfTrue);
    sfSprite_setScale(map->high_sprite, (sfVector2f){TILE_SCALE, TILE_SCALE});
    return map;
}

static sfVector2f *get_collisions_pos(unsigned int *size)
{
    sfVector2f *pos = NULL;
    size_t len = 0;
    char *line = NULL;
    FILE *file = fopen("Collisions/res.coll", "r");

    while (getline(&line, &len, file) != -1) {
        pos = realloc(pos, sizeof(sfVector2f) * (*size + 1));
        pos[*size].x = atoi(strtok(line, " ")) * TILE_SCALE + TILE_SIZE * 12 -
            TILE_SIZE / 2;
        pos[*size].y = atoi(strtok(NULL, " ")) * TILE_SCALE;
        (*size)++;
    }
    free(line);
    fclose(file);
    return pos;
}

static collision_t *init_collision(void)
{
    collision_t *collision = malloc(sizeof(collision_t));

    collision->rect = (sfIntRect){0, 0, TILE_SIZE, TILE_SIZE};
    collision->size = 0;
    collision->pos = get_collisions_pos(&collision->size);
    collision->shape = sfRectangleShape_create();
    sfRectangleShape_setFillColor(collision->shape, sfTransparent);
    sfRectangleShape_setOutlineColor(collision->shape, sfBlack);
    sfRectangleShape_setOutlineThickness(collision->shape, 2);
    sfRectangleShape_setSize(collision->shape, (sfVector2f){TILE_SIZE,
        TILE_SIZE});
    return collision;
}

void *load_data(void *arg)
{
    shared_data_t *shared_data = (shared_data_t *)arg;

    shared_data->map = init_map();
    shared_data->loaded = 1;
    pthread_exit(NULL);
}

static void init_rpg2(rpg_t *rpg)
{
    rpg->main_menu = init_menu();
    rpg->save_menu = init_save_menu();
    rpg->settings = init_settings();
    init_all_quests(rpg);
    rpg->interface = init_interface();
    rpg->collision = init_collision();
    init_inventory(15);
    rpg->inventory = *inventory();
}

static void set_sprite_transparent(sfSprite *sprite, int alpha)
{
    sfColor color = sfSprite_getColor(sprite);

    color.a = alpha;
    sfSprite_setColor(sprite, color);
}

static text_box_t *init_text_box(void)
{
    text_box_t *text_box = malloc(sizeof(text_box_t));

    text_box->box_texture = sfTexture_createFromFile("assets/interface/text_box.png",
        NULL);
    text_box->box = sfSprite_create();
    sfSprite_setTexture(text_box->box, text_box->box_texture, sfTrue);
    sfSprite_setScale(text_box->box, (sfVector2f){0.5, 0.5});
    set_sprite_transparent(text_box->box, 150);
    text_box->font = sfFont_createFromFile("assets/fonts/CompassPro.ttf");
    text_box->npc_name = sfText_create();
    sfText_setFont(text_box->npc_name, text_box->font);
    sfText_setCharacterSize(text_box->npc_name, 30);
    text_box->npc_text = sfText_create();
    sfText_setFont(text_box->npc_text, text_box->font);
    sfText_setCharacterSize(text_box->npc_text, 30);
    text_box->is_displayed = false;
    text_box->is_fully_displayed = false;
    text_box->clock = sfClock_create();
    text_box->str = NULL;
    text_box->displayed_str = NULL;
    text_box->len = 0;
    return text_box;
}

rpg_t *init_rpg(void)
{
    rpg_t *rpg = malloc(sizeof(rpg_t));

    srand(time(NULL));
    rpg->shm_fd = shm_open("/shared_memory", O_CREAT | O_RDWR, 0666);
    ftruncate(rpg->shm_fd, sizeof(shared_data_t));
    rpg->shared_data = (shared_data_t *)mmap(NULL, sizeof(shared_data_t),
        PROT_READ | PROT_WRITE, MAP_SHARED, rpg->shm_fd, 0);
    rpg->shared_data->loaded = 0;
    pthread_create(&rpg->thread, NULL, load_data, (void *)rpg->shared_data);
    rpg->gamestate = MAIN_MENU;
    start(rpg);
    rpg->win = init_win(WIDTH, HEIGHT);
    rpg->lwarrior = init_lwarrior();
    rpg->event = (sfEvent){0};
    rpg->debug = true;
    rpg->text_box = init_text_box();
    init_rpg2(rpg);
    return rpg;
}
