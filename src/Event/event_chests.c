/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** event_chests
*/

#include "rpg.h"

static void init_popup_item_position(rpg_t *rpg)
{
    popup_item_t *popup = rpg->interface->popup_item;
    sfVector2f pos = get_player(rpg)->common->pos;
    sfFloatRect rect;

    sfSprite_setPosition(popup->back_sprite, pos);
    sfSprite_setPosition(popup->item_sprite, (sfVector2f){pos.x - 350, pos.y});
    sfSprite_setPosition(popup->light_sprite,
        (sfVector2f){pos.x - 350, pos.y});
    rect = sfText_getGlobalBounds(popup->item_name);
    sfText_setOrigin(popup->item_name, (sfVector2f){rect.width / 2,
        rect.height / 2});
    sfText_setPosition(popup->item_name, (sfVector2f){pos.x, pos.y - 140});
    sfText_setPosition(popup->item_description, (sfVector2f){pos.x - 150,
        pos.y - 62});
    sfText_setPosition(popup->skip_text, (sfVector2f){pos.x + 270,
        pos.y + 150});
    rect = sfText_getGlobalBounds(popup->rarity);
    sfText_setOrigin(popup->rarity, (sfVector2f){rect.width / 2,
        rect.height / 2});
    sfText_setPosition(popup->rarity, (sfVector2f){pos.x - 350, pos.y + 150});
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

    sfText_setString(popup->item_description, description_text);
    sfText_setString(popup->rarity, get_rarity_string(item->rarity));
    init_popup_item_position(rpg);
    popup->display = 1;
    free(description_text);
}

static void reinit_popup_item(rpg_t *rpg, chest_t *chest)
{
    popup_item_t *popup = rpg->interface->popup_item;
    item_t *item = get_item_from_name(rpg, chest->item_name, chest->item_type);
    sfFloatRect rect;
    sfColor rarity_color = get_color_from_item_rarity(item->rarity);

    popup->item_texture = sfTexture_createFromFile(item->texture_path, NULL);
    popup->item_sprite = sfSprite_create();
    sfSprite_setTexture(popup->item_sprite, popup->item_texture, sfTrue);
    rect = sfSprite_getGlobalBounds(popup->item_sprite);
    sfSprite_setOrigin(popup->item_sprite,
        (sfVector2f){rect.width / 2, rect.height / 2});
    sfSprite_setScale(popup->item_sprite, (sfVector2f){6, 6});
    sfSprite_setColor(popup->item_sprite, sfColor_fromRGBA(255, 255, 255, 0));
    sfText_setString(popup->item_name, item->name);
    sfText_setColor(popup->item_name, rarity_color);
    sfText_setColor(popup->rarity, rarity_color);
    reinit_popup_item2(rpg, popup, item);
}

static void chest_is_interacted(rpg_t *rpg, entity_t *player, int i)
{
    if (rpg->chests[i]->item_type != OTHER &&
        !rpg->chests[i]->is_interacted && !rpg->chests[i]->is_recieved) {
        play_music(rpg->sounds->items, 25);
        quest_done_item(rpg, rpg->chests[i]->item_name);
        add_item_from_type(rpg, rpg->chests[i]->item_name,
            rpg->chests[i]->item_type);
        reinit_popup_item(rpg, rpg->chests[i]);
        rpg->chests[i]->is_recieved = true;
    }
    rpg->chests[i]->is_interacted = !rpg->chests[i]->is_interacted;
    if (!rpg->chests[i]->is_interacted &&
        rpg->interface->popup_item->display == 1) {
        rpg->interface->popup_item->display = 2;
        play_music(rpg->sounds->close, 100);
        }
    if (rpg->chests[i]->is_interacted)
        player->common->state = INTERACT;
    else if (!rpg->chests[i]->is_interacted &&
        rpg->interface->popup_item->display == 0)
        player->common->state = IDLE;
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
            if (rpg->chests[i]->is_interacted)
                play_music(rpg->sounds->close, 100);
            if (rpg->chests[i]->is_interacted == false)
                play_music(rpg->sounds->open, 100);
            return chest_is_interacted(rpg, player, i);
        }
    }
}
