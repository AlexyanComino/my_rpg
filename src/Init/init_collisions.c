/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_collisions
*/

#include "rpg.h"


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
        pos[*size].y = atoi(strtok(NULL, " ")) * TILE_SCALE + TILE_SIZE / 2;
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

collision_t *init_collision(void)
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
