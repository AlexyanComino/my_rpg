/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** update_all
*/

#include "rpg.h"

static void anim_decors(decor_anim_t *decor)
{
    update_clock_seconds(decor->anim->myclock);
    if (decor->anim->myclock->seconds < decor->speed)
        return;
    if (decor->anim->rect.left >= decor->width * decor->nb_cols &&
        decor->anim->rect.top >= decor->height * decor->nb_rows) {
        decor->anim->rect.left = 0;
        decor->anim->rect.top = 0;
    } else if (decor->anim->rect.left >= decor->width * decor->nb_cols) {
        decor->anim->rect.left = 0;
        decor->anim->rect.top += decor->height;
    } else
        decor->anim->rect.left += decor->width;
    sfSprite_setTextureRect(decor->anim->sprite, decor->anim->rect);
    sfClock_restart(decor->anim->myclock->clock);
}

static void update_decors_anim(rpg_t *rpg)
{
    for (int i = 0; i < (int)rpg->decors_size; i++) {
        if (!intrect_is_in_view_menu(rpg, rpg->decors[i]->rect))
            continue;
        anim_decors(rpg->decors[i]);
    }
}

static void update_anim_inventory(rpg_t *rpg)
{
    entity_t *entity = rpg->inventory->player_status->player;

    switch (get_player(rpg)->type) {
        case WARRIOR:
            anim_warrior(rpg, entity);
            break;
        case PAWN:
            anim_pawn(rpg, entity);
            break;
        case TORCH:
            anim_torch(rpg, entity);
            break;
        case TNT:
            anim_tnt(entity);
            break;
        case ARCHER:
            anim_archer(rpg, entity);
            break;
    }
}

void update(rpg_t *rpg)
{
    if (rpg->gamestate == MAIN_MENU || rpg->gamestate == PAUSE ||
        rpg->gamestate == SETTINGS || rpg->gamestate == SAVE_MENU) {
        update_decors_anim(rpg);
    }
    if (rpg->gamestate == GAME) {
        update_game_interface(rpg);
        update_chests(rpg);
        update_entities(rpg);
        update_quest_header(rpg);
        update_quests(rpg);
        update_decors_anim(rpg);
    }
    if (rpg->gamestate == INVENTORY)
        update_anim_inventory(rpg);
}
