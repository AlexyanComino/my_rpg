/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** event_chests
*/

#include "rpg.h"

static void init_popup_item_position(rpg_t *rpg)
{
    popup_item_t *p = rpg->interface->popup_item;
    sfVector2f pos = get_player(rpg)->common->pos;
    sfFloatRect rect;

    sfSprite_setPosition(p->back_sprite, pos);
    sfSprite_setPosition(p->item_anim->sprite,
        (sfVector2f){pos.x - 390, pos.y});
    sfSprite_setPosition(p->light_sprite, (sfVector2f){pos.x - 390, pos.y});
    rect = sfText_getGlobalBounds(p->title->text);
    sfText_setOrigin(p->title->text, (sfVector2f){rect.width / 2,
        rect.height / 2});
    sfText_setPosition(p->title->text, (sfVector2f){pos.x, pos.y - 250});
    sfText_setPosition(p->item_description, (sfVector2f){pos.x - 150,
        pos.y - 140});
    sfText_setPosition(p->skip_text, (sfVector2f){pos.x + 350, pos.y + 200});
    rect = sfText_getGlobalBounds(p->rarity);
    sfText_setOrigin(p->rarity, (sfVector2f){rect.width / 2, rect.height / 2});
    sfText_setPosition(p->rarity, (sfVector2f){pos.x - 390, pos.y + 170});
}

static sfColor get_color_from_item_rarity(rarity_t rarity)
{
    switch (rarity) {
    case COMMON:
        return sfColor_fromRGBA(101, 171, 255, 0);
    case UNCOMMON:
        return sfColor_fromRGBA(103, 255, 58, 0);
    case RARE:
        return sfColor_fromRGBA(255, 219, 58, 0);
    case EPIC:
        return sfColor_fromRGBA(140, 58, 193, 0);
    case LEGENDARY:
        return sfColor_fromRGBA(214, 52, 52, 0);
    default:
        return sfColor_fromRGBA(255, 255, 255, 0);
    }
}

static char *get_rarity_string(rarity_t rarity)
{
    switch (rarity) {
    case COMMON:
        return "Common";
    case UNCOMMON:
        return "Uncommon";
    case RARE:
        return "Rare";
    case EPIC:
        return "Epic";
    case LEGENDARY:
        return "Legendary";
    default:
        return "Unknown";
    }
}

static void reinit_popup_item2(rpg_t *rpg, popup_item_t *popup, item_t *item)
{
    char *description_text = description_handling(item->description);

    set_string_to_text(popup->item_description, description_text);
    set_string_to_text(popup->rarity, get_rarity_string(item->rarity));
    init_popup_item_position(rpg);
    popup->display = 1;
    free(description_text);
}

anim_sprite_t *init_anim_sprite(char *texture_path, float scale_bonus,
    float transition_speed, float init_scale)
{
    anim_sprite_t *anim_sprite = malloc(sizeof(anim_sprite_t));
    sfFloatRect rect;

    anim_sprite->sprite = sfSprite_create();
    anim_sprite->texture = sfTexture_createFromFile(texture_path, NULL);
    sfSprite_setTexture(anim_sprite->sprite, anim_sprite->texture, sfTrue);
    anim_sprite->scale_dir = 1;
    rect = sfSprite_getGlobalBounds(anim_sprite->sprite);
    sfSprite_setOrigin(anim_sprite->sprite,
        (sfVector2f){rect.width / 2, rect.height / 2});
    sfSprite_setScale(anim_sprite->sprite,
        (sfVector2f){init_scale, init_scale});
    anim_sprite->scale_max = init_scale + scale_bonus;
    anim_sprite->scale_min = init_scale - scale_bonus;
    anim_sprite->speed = transition_speed;
    return anim_sprite;
}

static void reinit_popup_item(rpg_t *rpg, chest_t *chest)
{
    popup_item_t *popup = rpg->interface->popup_item;
    item_t *item = get_item_from_name(rpg, chest->item_name, chest->item_type);
    sfColor rarity_color = get_color_from_item_rarity(item->rarity);

    popup->item_anim = init_anim_sprite(item->texture_path, 0.5, 0.015, 9);
    sfSprite_setColor(popup->item_anim->sprite,
        sfColor_fromRGBA(255, 255, 255, 0));
    set_string_to_text(popup->title->text, item->name);
    sfText_setColor(popup->title->text, rarity_color);
    sfText_setColor(popup->rarity, rarity_color);
    reinit_popup_item2(rpg, popup, item);
}

static void chest_is_interacted(rpg_t *rpg, entity_t *player, int i)
{
    if (rpg->chests[i]->item_type != OTHER &&
        !rpg->chests[i]->is_interacted && !rpg->chests[i]->is_recieved) {
        if (!strcmp(rpg->chests[i]->item_name, "Guide des Horizons")) {
            rpg->comp->carte = true;
            setup_command_help_in_game(rpg);
        }
        play_music(rpg->sounds->items, 25 * rpg->volume);
        add_item_from_type(rpg, rpg->chests[i]->item_name,
            rpg->chests[i]->item_type);
        reinit_popup_item(rpg, rpg->chests[i]);
        rpg->chests[i]->is_recieved = true;
    }
    rpg->chests[i]->is_interacted = !rpg->chests[i]->is_interacted;
    if (!rpg->chests[i]->is_interacted &&
        rpg->interface->popup_item->display == 1) {
        rpg->interface->popup_item->display = 2;
        play_music(rpg->sounds->close, 100 * rpg->volume);
        quest_done_item(rpg, rpg->chests[i]->item_name);
    }
    if (rpg->chests[i]->is_interacted)
        player->common->state = INTERACT;
    else if (!rpg->chests[i]->is_interacted &&
        rpg->interface->popup_item->display == 0)
        player->common->state = IDLE;
}

static void play_music_chest(rpg_t *rpg, chest_t *chest)
{
    if (chest->is_interacted)
        play_music(rpg->sounds->close, 100 * rpg->volume);
    if (chest->is_interacted == false)
        play_music(rpg->sounds->open, 100 * rpg->volume);
}

void event_chests(rpg_t *rpg, sfKeyCode key)
{
    entity_t *player = get_player(rpg);

    if (rpg->gamestate != GAME || key != sfKeyE)
        return;
    for (unsigned int i = 0; i < rpg->chests_size; i++) {
        if (!intrect_is_in_view(rpg, rpg->chests[i]->rect))
            continue;
        if (sfIntRect_intersects(&rpg->chests[i]->rect,
            &player->common->zones->hitbox_attack, NULL)) {
            play_music_chest(rpg, rpg->chests[i]);
            return chest_is_interacted(rpg, player, i);
        }
    }
}
