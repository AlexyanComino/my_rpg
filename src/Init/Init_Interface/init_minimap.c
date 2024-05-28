/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_minimap
*/

#include "rpg.h"

static float get_alpha(float distance, unsigned int width)
{
    float alpha = 255 - distance * 255 / (width / 2);

    if (alpha < 0)
        alpha = 0;
    if (alpha > 255)
        alpha = 255;
    return alpha;
}

static sfImage *get_blur_image(unsigned int width, unsigned int height)
{
    sfImage *image = sfImage_create(width, height);
    float distance = 0;
    int alpha = 0;
    sfColor color;

    for (unsigned int x = 0; x < width; x++) {
        for (unsigned int y = 0; y < height; y++) {
            distance = get_distance((sfVector2f){width / 2, height / 2},
                (sfVector2f){x, y});
            alpha = get_alpha(distance, width);
            color = sfColor_fromRGBA(0, 0, 0, alpha);
            sfImage_setPixel(image, x, y, color);
        }
    }
    return image;
}

static void init_minimap_blur(minimap_t *minimap, unsigned int width,
    unsigned int height)
{
    sfImage *image = get_blur_image(width, height);

    minimap->blur_texture = sfTexture_create(width, height);
    sfTexture_updateFromImage(minimap->blur_texture, image, 0, 0);
    minimap->blur = sfSprite_create();
    sfSprite_setTexture(minimap->blur, minimap->blur_texture, sfTrue);
    sfSprite_setOrigin(minimap->blur, (sfVector2f){width / 2, height / 2});
    sfImage_destroy(image);
}

static void init_minimap_background(minimap_t *minimap)
{
    minimap->back_texture = sfTexture_createFromFile(
        "assets/interface/minimap_back.png", NULL);
    minimap->back = sfSprite_create();
    sfSprite_setTexture(minimap->back, minimap->back_texture, sfTrue);
    sfSprite_setOrigin(minimap->back, (sfVector2f){MINIMAP_BACK_SIZE / 2,
        MINIMAP_BACK_SIZE / 2});
    sfSprite_setScale(minimap->back,
        (sfVector2f){(float)1260 / MINIMAP_BACK_SIZE,
        (float)1260 / MINIMAP_BACK_SIZE});
}

static void get_text_size_and_thickness(char **infos, float *size,
    float *thickness)
{
    if (!strcmp(infos[1], "ville")) {
        *size = 280;
        *thickness = 30;
        return;
    }
    if (!strcmp(infos[1], "camp")) {
        *size = 260;
        *thickness = 25;
        return;
    }
    if (!strcmp(infos[1], "foret")) {
        *size = 300;
        *thickness = 35;
        return;
    }
    *size = 200;
    *thickness = 20;
}

static void init_text_city(minimap_t *minimap, char **infos, int i)
{
    float size;
    float thickness;

    get_text_size_and_thickness(infos, &size, &thickness);
    minimap->texts[i] = sfText_create();
    sfText_setFont(minimap->texts[i], minimap->font);
    set_string_to_text(minimap->texts[i], infos[0]);
    sfText_setCharacterSize(minimap->texts[i], size);
    sfText_setPosition(minimap->texts[i],
        (sfVector2f){atof(infos[2]), atof(infos[3])});
    sfText_setColor(minimap->texts[i], sfWhite);
    sfText_setOutlineColor(minimap->texts[i], sfBlack);
    sfText_setOutlineThickness(minimap->texts[i], thickness);
    sfText_setOrigin(minimap->texts[i], (sfVector2f)
        {sfText_getLocalBounds(minimap->texts[i]).width / 2,
        sfText_getLocalBounds(minimap->texts[i]).height / 2});
}

static void init_minimap_texts(minimap_t *minimap)
{
    char **tab = file_to_array(".cities.csv");
    char **infos = NULL;

    minimap->texts = malloc(sizeof(sfVector2f) * tab_len(tab));
    minimap->nb_texts = tab_len(tab);
    minimap->font =
        sfFont_createFromFile("assets/fonts/Burbank-Big-Condensed-Black.ttf");
    for (int i = 0; i < minimap->nb_texts; i++) {
        infos = split_string(tab[i], ";");
        init_text_city(minimap, infos, i);
        free_array(infos);
    }
    free_array(tab);
}

static void init_minimap2(minimap_t *minimap, unsigned int width,
    unsigned int height)
{
    minimap->rotation = 0;
    minimap->rect = sfRectangleShape_create();
    sfRectangleShape_setSize(minimap->rect, (sfVector2f){minimap->size,
        minimap->size});
    sfRectangleShape_setOrigin(minimap->rect, (sfVector2f){minimap->size / 2,
        minimap->size / 2});
    sfRectangleShape_setOutlineThickness(minimap->rect, 4);
    sfRectangleShape_setOutlineColor(minimap->rect, sfWhite);
    sfRectangleShape_setFillColor(minimap->rect, sfTransparent);
    init_minimap_blur(minimap, width, height);
    init_minimap_background(minimap);
    init_minimap_texts(minimap);
}

minimap_t *init_minimap(unsigned int width, unsigned int height)
{
    minimap_t *minimap = malloc(sizeof(minimap_t));

    minimap->size = 800;
    minimap->view = sfView_create();
    sfView_setSize(minimap->view, (sfVector2f){minimap->size, minimap->size});
    sfView_setViewport(minimap->view, (sfFloatRect){(1 - minimap->size / width)
        / 2, (1 - minimap->size / height) / 2,
        minimap->size / width, minimap->size / height});
    sfView_zoom(minimap->view, 10);
    minimap->zoom = 10.0f;
    minimap->arrow_texture = sfTexture_createFromFile(
        "assets/interface/arrow_player.png", NULL);
    minimap->arrow_sprite = sfSprite_create();
    sfSprite_setTexture(minimap->arrow_sprite, minimap->arrow_texture, sfTrue);
    sfSprite_setOrigin(minimap->arrow_sprite,
        (sfVector2f){MINIMAP_ARROW_WIDTH / 2,
        MINIMAP_ARROW_WIDTH / 2});
    init_minimap2(minimap, width, height);
    return minimap;
}
