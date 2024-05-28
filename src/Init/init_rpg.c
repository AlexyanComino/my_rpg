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
    sfImage *icon = sfImage_createFromFile("assets/Icon.png");
    sfVector2u i = sfImage_getSize(icon);

    win->window = sfRenderWindow_create(mode, "The Blade of Eternity",
        sfDefaultStyle, NULL);
    sfRenderWindow_setIcon(win->window, i.x, i.y, sfImage_getPixelsPtr(icon));
    win->view = sfView_createFromRect((sfFloatRect){0, 0, width, height});
    win->view_menu = sfView_createFromRect((sfFloatRect){0, 0, width, height});
    win->width = width;
    win->height = height;
    win->framerate = 60;
    win->clock = sfClock_create();
    win->mouse_pos = (sfVector2f){0, 0};
    sfRenderWindow_setFramerateLimit(win->window, win->framerate);
    win->view_pos = (sfVector2f){4850, 8400};
    win->zoom = 2;
    win->view_menu_move = (sfVector2f){80, 0};
    return win;
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

static void pre_display_loading(rpg_t *rpg)
{
    sfRenderWindow_clear(rpg->win->window, sfBlack);
    sfRenderWindow_drawSprite(rpg->win->window,
        rpg->loading->load->sprite, NULL);
    sfRenderWindow_drawText(rpg->win->window,
        rpg->loading->title1->text, NULL);
    sfRenderWindow_drawText(rpg->win->window,
        rpg->loading->title2->text, NULL);
    sfRenderWindow_display(rpg->win->window);
}

static modes_t *init_modes(void)
{
    modes_t *modes = malloc(sizeof(modes_t));

    modes->plus = false;
    modes->keynote_mode = true;
    modes->k = false;
    modes->debug = false;
    return modes;
}

static save_t **init_saves(void)
{
    save_t **saves = malloc(sizeof(save_t *) * 3);

    for (int i = 0; i < 3; i++)
        saves[i] = load(i + 1);
    return saves;
}

static comp_t *init_comp(void)
{
    comp_t *skill = malloc(sizeof(comp_t));

    skill->fire = false;
    skill->poison = false;
    skill->carte = false;
    return skill;
}

static void init_rpg2(rpg_t *rpg)
{
    rpg->settings = init_settings(rpg);
    rpg->selector = init_select_menu(rpg);
    rpg->interface = init_interface();
    rpg->minimap = init_minimap(WIDTH, HEIGHT);
    rpg->collision = init_collision();
    init_all_quests(rpg);
    init_inventory(rpg, 15);
    rpg->inventory = *inventory();
    rpg->decors_size = 0;
    rpg->decors = init_decors(&rpg->decors_size);
    rpg->chests_size = 0;
    rpg->chests = init_chests(&rpg->chests_size);
    rpg->items_size = 0;
    rpg->items = init_items_tab(&rpg->items_size);
    rpg->transition = init_transition();
    rpg->end_menu = init_end_menu(rpg);
    rpg->pause_menu = init_pause_menu();
    rpg->skill_tree = init_all_skill();
    rpg->vict = init_victory();
    rpg->credits = init_credits();
    rpg->comp = init_comp();
}

rpg_t *init_rpg(void)
{
    rpg_t *rpg = malloc(sizeof(rpg_t));

    srand(time(NULL));
    rpg->player_index = UINT_MAX;
    init_thread(rpg);
    rpg->gamestate = LOADING;
    rpg->win = init_win(WIDTH, HEIGHT);
    rpg->loading = init_loading();
    pre_display_loading(rpg);
    rpg->event = (sfEvent){0};
    rpg->modes = init_modes();
    rpg->text_box = init_text_box();
    rpg->sounds = init_sounds();
    rpg->save = init_saves();
    rpg->main_menu = init_menu(rpg);
    rpg->save_menu = init_save_menu(rpg);
    rpg->volume = 1;
    init_rpg2(rpg);
    play_music(rpg->sounds->intro, 50 * rpg->volume);
    return rpg;
}
