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

    map->ground_texture = sfTexture_createFromFile("assets/bas.png", NULL);
    map->ground_sprite = sfSprite_create();
    sfSprite_setTexture(map->ground_sprite, map->ground_texture, sfTrue);
    sfSprite_setScale(map->ground_sprite,
        (sfVector2f){TILE_SCALE, TILE_SCALE});
    map->high_texture = sfTexture_createFromFile("assets/haut.png", NULL);
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

static region_t ***init_regions(unsigned int cols, unsigned int rows)
{
    region_t ***regions = malloc(sizeof(region_t **) * cols);

    for (unsigned int i = 0; i < cols; i++) {
        regions[i] = malloc(sizeof(region_t *) * rows);
        for (unsigned int j = 0; j < rows; j++) {
            regions[i][j] = malloc(sizeof(region_t));
            regions[i][j]->size = 0;
            regions[i][j]->pos = NULL;
            regions[i][j]->rect = (sfIntRect){i * WIDTH, j * HEIGHT, WIDTH,
                HEIGHT};
        }
    }
    return regions;
}

static region_t ***get_regions(unsigned int cols, unsigned int rows)
{
    region_t ***regions = init_regions(cols, rows);
    unsigned int size = 0;
    sfVector2f *pos = get_collisions_pos(&size);
    unsigned int region_col = 0;
    unsigned int region_row = 0;

    for (unsigned int i = 0; i < size; i++) {
        region_col = pos[i].x / WIDTH;
        region_row = pos[i].y / HEIGHT;
        if (region_col >= cols || region_row >= rows)
            continue;
        regions[region_col][region_row]->pos = realloc(regions[region_col][region_row]->pos,
            sizeof(sfVector2f) * (regions[region_col][region_row]->size + 1));
        regions[region_col][region_row]->pos[regions[region_col][region_row]->size] = pos[i];
        regions[region_col][region_row]->size++;
    }
    free(pos);
    return regions;
}

static collision_t *init_collision(void)
{
    collision_t *collision = malloc(sizeof(collision_t));

    collision->rect = (sfIntRect){0, 0, TILE_SIZE, TILE_SIZE};
    collision->size = 0;
    collision->cols = (MAP_WIDTH + WIDTH + 1) / WIDTH;
    collision->rows = (MAP_HEIGHT + HEIGHT + 1) / HEIGHT;
    collision->regions = get_regions(collision->cols, collision->rows);
    collision->shape = sfRectangleShape_create();
    sfRectangleShape_setFillColor(collision->shape, sfTransparent);
    sfRectangleShape_setOutlineColor(collision->shape, sfBlack);
    sfRectangleShape_setOutlineThickness(collision->shape, 2);
    sfRectangleShape_setSize(collision->shape, (sfVector2f){TILE_SIZE,
        TILE_SIZE});
    collision->region_shape = sfRectangleShape_create();
    sfRectangleShape_setFillColor(collision->region_shape, sfTransparent);
    sfRectangleShape_setOutlineColor(collision->region_shape, sfRed);
    sfRectangleShape_setOutlineThickness(collision->region_shape, 2);
    sfRectangleShape_setSize(collision->region_shape, (sfVector2f){WIDTH,
        HEIGHT});
    return collision;
}

void *load_data(void *arg)
{
    shared_data_t *shared_data = (shared_data_t *)arg;

    shared_data->map = init_map();
    shared_data->loaded = 1;
    pthread_exit(NULL);
}

static void init_thread(rpg_t *rpg)
{
    rpg->shm_fd = shm_open("/shared_memory", O_CREAT | O_RDWR, 0666);
    ftruncate(rpg->shm_fd, sizeof(shared_data_t));
    rpg->shared_data = (shared_data_t *)mmap(NULL, sizeof(shared_data_t),
        PROT_READ | PROT_WRITE, MAP_SHARED, rpg->shm_fd, 0);
    rpg->shared_data->loaded = 0;
    pthread_create(&rpg->thread, NULL, load_data, (void *)rpg->shared_data);
}

rpg_t *init_rpg(void)
{
    rpg_t *rpg = malloc(sizeof(rpg_t));

    srand(time(NULL));
    init_thread(rpg);
    rpg->gamestate = MAIN_MENU;
    rpg->win = init_win(WIDTH, HEIGHT);
    rpg->ent_size = 0;
    rpg->ent = init_ent(&rpg->ent_size);
    rpg->event = (sfEvent){0};
    rpg->debug = true;
    rpg->main_menu = init_menu();
    rpg->save_menu = init_save_menu();
    rpg->settings = init_settings();
    rpg->interface = init_interface();
    rpg->collision = init_collision();
    rpg->quest_desc = NULL;
    rpg->quest_info = NULL;
    rpg->quest_text = NULL;
    init_inventory(15);
    rpg->inventory = *inventory();
    rpg->items = malloc(sizeof(item_t *));
    rpg->items_size = 0;
    return rpg;
}
