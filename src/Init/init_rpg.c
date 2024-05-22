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
    win->view_menu = sfView_createFromRect((sfFloatRect){0, 0, width, height});
    win->width = width;
    win->height = height;
    win->framerate = 60;
    win->clock = sfClock_create();
    win->mouse_pos = (sfVector2f){0, 0};
    sfRenderWindow_setFramerateLimit(win->window, win->framerate);
    win->view_pos = (sfVector2f){5331, 8353};
    sfView_setCenter(win->view_menu, win->view_pos);
    sfView_zoom(win->view_menu, 2);
    win->zoom = 2;
    sfRenderWindow_setView(win->window, win->view_menu);
    return win;
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
    unsigned int col = 0;
    unsigned int row = 0;

    for (unsigned int i = 0; i < size; i++) {
        col = pos[i].x / WIDTH;
        row = pos[i].y / HEIGHT;
        if (col >= cols || row >= rows)
            continue;
        regions[col][row]->pos = realloc(regions[col][row]->pos,
            sizeof(sfVector2f) * (regions[col][row]->size + 1));
        regions[col][row]->pos[regions[col][row]->size] = pos[i];
        regions[col][row]->size++;
    }
    free(pos);
    return regions;
}

static collision_t *init_collision(void)
{
    collision_t *collision = malloc(sizeof(collision_t));

    collision->rect = (sfIntRect){0, 0, TILE_SIZE, TILE_SIZE};
    collision->size = 0;
    collision->cols = ((MAP_WIDTH + WIDTH + 1) * TILE_SCALE) / WIDTH;
    collision->rows = ((MAP_HEIGHT + HEIGHT + 1) * TILE_SCALE) / HEIGHT;
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

static void init_thread(rpg_t *rpg)
{
    rpg->shm_fd1 = shm_open("/shared_memory", O_CREAT | O_RDWR, 0666);
    ftruncate(rpg->shm_fd1, sizeof(shared_data_t));
    rpg->shared_data = (shared_data_t *)mmap(NULL, sizeof(shared_data_t),
        PROT_READ | PROT_WRITE, MAP_SHARED, rpg->shm_fd1, 0);
    rpg->shared_data->loaded = 0;
    pthread_create(&rpg->thread, NULL, load_data, (void *)rpg->shared_data);
    rpg->shm_fd2 = shm_open("/shared_memory2", O_CREAT | O_RDWR, 0666);
    ftruncate(rpg->shm_fd2, sizeof(shared_data2_t));
    rpg->shared_data2 = (shared_data2_t *)mmap(NULL, sizeof(shared_data2_t),
        PROT_READ | PROT_WRITE, MAP_SHARED, rpg->shm_fd2, 0);
    rpg->shared_data2->loaded = 0;
    pthread_create(&rpg->thread2, NULL, load_entities,
        (void *)rpg->shared_data2);
}

static save_t **init_saves(void)
{
    save_t **saves = malloc(sizeof(save_t *) * 3);

    for (int i = 0; i < 3; i++)
        saves[i] = load(i + 1);
    return saves;
}

static void init_rpg2(rpg_t *rpg)
{
    rpg->main_menu = init_menu(rpg);
    rpg->save_menu = init_save_menu(rpg);
    rpg->settings = init_settings(rpg);
    rpg->selector = init_select_menu(rpg);
    rpg->interface = init_interface();
    rpg->minimap = init_minimap(WIDTH, HEIGHT);
    rpg->collision = init_collision();
    init_all_quests(rpg);
    rpg->plus = false;
    rpg->decors_size = 0;
    rpg->decors = init_decors(&rpg->decors_size);
    rpg->chests_size = 0;
    rpg->chests = init_chests(&rpg->chests_size);
    rpg->items_size = 0;
    rpg->items = init_items_tab(&rpg->items_size);
    init_inventory(rpg, 15);
    rpg->inventory = *inventory();
    rpg->skill_tree = init_all_skill();
    pthread_join(rpg->thread, NULL);
    if (rpg->shared_data->loaded)
        rpg->map = rpg->shared_data->map;
}

rpg_t *init_rpg(void)
{
    rpg_t *rpg = malloc(sizeof(rpg_t));

    srand(time(NULL));
    rpg->player_index = UINT_MAX;
    init_thread(rpg);
    rpg->gamestate = MAIN_MENU;
    rpg->win = init_win(WIDTH, HEIGHT);
    rpg->event = (sfEvent){0};
    rpg->debug = false;
    rpg->text_box = init_text_box();
    rpg->save = init_saves();
    init_rpg2(rpg);
    return rpg;
}
