/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** display_inv
*/

#include "rpg.h"
#include "singleton.h"


static int update_slot(void)
{
    int x = 0;
    int y = 0;
    inventory_t *inv = (*inventory());

    sfSprite_setPosition(inv->sprite, (sfVector2f){(*view_pos()).x - 960,
        (*view_pos()).y - 450});
    for (slot_t *tmp = inv->slot; tmp; tmp = tmp->next) {
        sfSprite_setPosition(tmp->sprite,
        (sfVector2f){(*view_pos()).x - 770 + x, (*view_pos()).y + y});
        sfSprite_setPosition(tmp->highlight,
        (sfVector2f){(*view_pos()).x - 785 + x, (*view_pos()).y - 17 + y});
        x += 100;
        if (x > 400) {
            y += 100;
            x = 0;
        }
    }
    return 0;
}

static int update_stuff(void)
{
    int x = 0;
    int y = 0;
    inventory_t *inv = (*inventory());

    for (slot_t *tmp = inv->player_status->stuff; tmp; tmp = tmp->next) {
        sfSprite_setPosition(tmp->sprite,
        (sfVector2f){(*view_pos()).x - 595 + x, (*view_pos()).y - 150});
        sfSprite_setPosition(tmp->highlight,
        (sfVector2f){(*view_pos()).x - 611 + x, (*view_pos()).y - 167});
        x += 75;
        if (x > 400) {
            y += 75;
            x = 0;
        }
    }
    return 0;
}

static void update_player_status(void)
{
    inventory_t *inv = (*inventory());

    sfSprite_setPosition(inv->player_status->s_attack,
    (sfVector2f){(*view_pos()).x - 420, (*view_pos()).y - 250});
    sfText_setPosition(inv->player_status->t_attack,
    (sfVector2f){(*view_pos()).x - 370, (*view_pos()).y - 280});
    sfSprite_setPosition(inv->player_status->s_hp,
    (sfVector2f){(*view_pos()).x - 575, (*view_pos()).y - 250});
    sfText_setPosition(inv->player_status->t_hp,
    (sfVector2f){(*view_pos()).x - 520, (*view_pos()).y - 280});
    sfSprite_setPosition(inv->player_status->s_speed,
    (sfVector2f){(*view_pos()).x - 420, (*view_pos()).y - 200});
    sfText_setPosition(inv->player_status->t_speed,
    (sfVector2f){(*view_pos()).x - 370, (*view_pos()).y - 220});
    sfSprite_setPosition(inv->player_status->s_def,
    (sfVector2f){(*view_pos()).x - 575, (*view_pos()).y - 200});
}

static void update_player_stat(void)
{
    inventory_t *inv = (*inventory());

    sfText_setPosition(inv->player_status->t_defense,
    (sfVector2f){(*view_pos()).x - 520, (*view_pos()).y - 220});
    sfSprite_setPosition(inv->player_status->s_gold,
    (sfVector2f){(*view_pos()).x - 375, (*view_pos()).y - 70});
    sfText_setPosition(inv->player_status->t_gold,
    (sfVector2f){(*view_pos()).x - 320, (*view_pos()).y - 70});
    sfText_setPosition(inv->player_status->t_level,
    (sfVector2f){(*view_pos()).x - 755, (*view_pos()).y - 70});
    sfSprite_setPosition(inv->player_status->pp,
    (sfVector2f){(*view_pos()).x - 780, (*view_pos()).y - 105});
    sfSprite_setPosition(inv->player_status->player->common->anim->sprite,
    (sfVector2f){(*view_pos()).x - 702, (*view_pos()).y - 175});
}

int *scroll_quest(int *scroll, int *scroll_max)
{
    int i = 0;

    for (all_quests_t *all = (*inventory())->quest; all &&
    (*inventory())->is_open; all = all->next) {
        for (quest_t *tmp = all->quest; tmp &&
        (*inventory())->is_open; tmp = tmp->next)
            i = (tmp->is_active) ? i + 1 : i;
    }
    if ((*inventory())->is_open && i != 0)
        *scroll_max = 4 % i;
    if (sfKeyboard_isKeyPressed(sfKeyS) &&
    *scroll < *scroll_max && (*inventory())->is_open)
        *scroll += 1;
    if (sfKeyboard_isKeyPressed(sfKeyZ) && *scroll > 0 &&
    (*inventory())->is_open)
        *scroll -= 1;
    return scroll;
}

static int print_quest(quest_t *tmp, int *i, int *scroll)
{
    if (tmp->is_active == false || *i < *scroll) {
        *i = (tmp->is_active) ? *i + 1 : *i;
        return 1;
    }
    return 0;
}

static void update_quest_next(sfSprite *sprite, sfText *name_s,
    sfText *desc_s, rpg_t *rpg)
{
    inventory_t *inv = (*inventory());
    int pos = 0;
    int i = 0;

    for (quest_t *tmp = inv->quest->quest; tmp; tmp = tmp->next) {
        if (print_quest(tmp, &i, &inv->scroll))
            continue;
        sfSprite_setPosition(sprite, (sfVector2f){(*view_pos()).x + 100,
            (*view_pos()).y - 400 + pos});
        sfText_setString(name_s, tmp->name);
        sfText_setPosition(name_s, (sfVector2f){(*view_pos()).x + 200,
            (*view_pos()).y - 325 + pos});
        sfText_setString(desc_s, tmp->description);
        sfText_setPosition(desc_s, (sfVector2f){(*view_pos()).x + 200,
            (*view_pos()).y - 275 + pos});
        sfRenderWindow_drawSprite(rpg->win->window, sprite, NULL);
        sfRenderWindow_drawText(rpg->win->window, name_s, NULL);
        sfRenderWindow_drawText(rpg->win->window, desc_s, NULL);
        pos += 200;
    }
}

void update_quest(rpg_t *rpg)
{
    static sfSprite *sprite = NULL;
    static sfText *name_s = NULL;
    static sfText *desc_s = NULL;

    if (sprite == NULL) {
        sprite = init_sprite_from_file("assets/inventory/QUEST.png");
        sfSprite_setScale(sprite, (sfVector2f){1.2, 1.2});
        name_s = create_text(
        sfFont_createFromFile("assets/fonts/m6x11plus.ttf"), "empty", 50,
        (sfVector2f){200, 700});
        sfText_setColor(name_s, sfColor_fromRGB(105, 165, 125));
        desc_s = create_text(
        sfFont_createFromFile("assets/fonts/m6x11plus.ttf"), "empty", 30,
            (sfVector2f){200, 700});
        sfText_setColor(desc_s, sfColor_fromRGB(135, 195, 155));
    }
    update_quest_next(sprite, name_s, desc_s, rpg);
}

int display_inv(rpg_t *rpg)
{
    if (rpg->gamestate == INVENTORY) {
        update_slot();
        update_stuff();
        update_player_status();
        update_player_stat();
        apply_stuff(rpg);
        open_inventory(rpg);
        update_quest(rpg);
    }
    return 0;
}
