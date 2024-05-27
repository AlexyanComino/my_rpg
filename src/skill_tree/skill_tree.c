/*
** EPITECH PROJECT, 2024
** skill
** File description:
** skill tree
*/

#include <stdio.h>
#include <stdlib.h>
#include "rpg.h"
#include "skill_tree.h"

static skill_t *init_skill
(char *name, char *description, int cost, int (*function)(rpg_t *rpg))
{
    skill_t *skill = malloc(sizeof(skill_t));

    skill->name = name;
    skill->description = description;
    skill->cost = cost;
    skill->function = function;
    skill->background = init_sprite_from_file("assets/skill/23.png");
    sfSprite_setScale(skill->background, (sfVector2f){2.5, 2.5});
    sfSprite_setColor(skill->background, sfColor_fromRGBA(255, 255, 255, 150));
    skill->highlight = init_sprite_from_file("assets/inventory/5.png");
    sfSprite_setScale(skill->highlight, (sfVector2f){12, 12});
    sfSprite_setOrigin(skill->highlight, (sfVector2f){1.3, 1.2});
    skill->locked = init_sprite_from_file
    ("assets/skill/Small Oval Padlock - GOLD - 0010.png");
    sfSprite_setScale(skill->locked, (sfVector2f){4, 4});
    sfSprite_setColor(skill->locked, sfColor_fromRGBA(255, 255, 255, 150));
    skill->lock = 1;
    skill->level = 0;
    skill->unlocked = 0;
    skill->next = NULL;
    return skill;
}

static int skill_test(rpg_t *rpg)
{
    rpg = rpg;
    printf("Skill test\n");
    return 1;
}

static int setup_logo(skill_t *skill, char *logo_path)
{
    skill->logo = init_sprite_from_file(logo_path);
    sfSprite_setScale(skill->logo, (sfVector2f){2, 2});
    sfSprite_setColor(skill->logo, sfColor_fromRGBA(255, 255, 255, 150));
    return 0;
}

static skill_t *init_skill_tree(skill_t *skill)
{
    setup_logo(skill->next->next->next->next->next,
    "assets/skill/skill_icon_07.png");
    skill = add_skill(skill,
    init_skill("Earth", "Shoot a earth", 10, &skill_test));
    setup_logo(skill->next->next->next->next->next->next,
    "assets/skill/skill_icon_06.png");
    skill = add_skill(skill,
    init_skill("Water", "Shoot a water", 10, &skill_test));
    setup_logo(skill->next->next->next->next->next->next->next,
    "assets/skill/skill_icon_05.png");
    skill = add_skill(skill,
    init_skill("Dark", "Shoot a dark", 10, &skill_test));
    setup_logo(skill->next->next->next->next->next->next->next->next,
    "assets/skill/skill_icon_08.png");
    skill = add_skill(skill,
    init_skill("Light", "Shoot a light", 10, &skill_test));
    setup_logo(skill->next->next->next->next->next->next->next->next->next,
    "assets/skill/skill_icon_09.png");
    return skill;
}

skill_t *init_all_skill(void)
{
    skill_t *skill = init_skill
    ("Damage Boost", "Shoot a fireball", 10, &skill_test);

    setup_logo(skill, "assets/skill/skill_icon_00.png");
    skill = add_skill(skill,
    init_skill("Defense Boost", "Heal yourself", 10, &skill_test));
    setup_logo(skill->next, "assets/skill/skill_icon_01.png");
    skill = add_skill(skill,
    init_skill("strengh", "Shoot a lightning", 10, &skill_test));
    setup_logo(skill->next->next, "assets/skill/skill_icon_02.png");
    skill = add_skill(skill,
    init_skill("Ice", "Shoot a ice", 10, &skill_test));
    setup_logo(skill->next->next->next, "assets/skill/skill_icon_03.png");
    skill = add_skill(skill,
    init_skill("Fire sword", "Shoot a poison", 10, &skill_test));
    setup_logo(skill->next->next->next->next,
    "assets/skill/skill_icon_04.png");
    skill = add_skill(skill,
    init_skill("poison", "Shoot a wind", 10, &skill_test));
    return init_skill_tree(skill);
}

skill_t *add_skill(skill_t *skill, skill_t *new_skill)
{
    skill_t *tmp = skill;

    if (skill == NULL)
        return new_skill;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new_skill;
    return skill;
}

static void check_requirement(skill_t *skill)
{
    int level = 0;
    static int max_comp = 3;
    static int last_nb = 0;
    int nb = 0;

    for (skill_t *t = skill; t; t = t->next) {
        if (level >= max_comp)
            break;
        nb += (t->unlocked == 1) ? 1 : 0;
        level += (t->unlocked == 1) ? 1 : 0;
        if (t->unlocked == 1)
            continue;
        sfSprite_setColor(t->background, sfColor_fromRGBA(255, 255, 255, 255));
        sfSprite_setColor(t->locked, sfColor_fromRGBA(255, 255, 255, 255));
        sfSprite_setColor(t->logo, sfColor_fromRGBA(255, 255, 255, 255));
        t->lock = 0;
        level++;
    }
    max_comp += (nb % 3 == 0 && last_nb != nb) ? 3 : 0;
    last_nb = nb;
}

static int click_skill(rpg_t *rpg, skill_t *tmp)
{
    if (rpg->event.type == sfEvtMouseButtonPressed &&
    rpg->event.mouseButton.button == sfMouseLeft)
        unlock_skill(rpg->skill_tree, tmp->name);
    return 0;
}

int highlight_skill_tree(rpg_t *rpg)
{
    skill_t *tmp = rpg->skill_tree;
    sfVector2f mouse = rpg->win->mouse_pos;
    sfFloatRect rect = {0, 0, 0, 0};

    for (; tmp; tmp = tmp->next) {
        rect = sfSprite_getGlobalBounds(tmp->background);
        if (sfFloatRect_contains(&rect, mouse.x, mouse.y)) {
            sfSprite_setPosition(tmp->highlight,
            sfSprite_getPosition(tmp->background));
            sfRenderWindow_drawSprite(rpg->win->window, tmp->highlight, NULL);
            click_skill(rpg, tmp);
        }
    }
    return 0;
}

int manage_skill_tree(rpg_t *rpg)
{
    if (rpg->event.type == sfEvtKeyPressed && rpg->event.key.code == sfKeyY) {
        rpg->gamestate = (rpg->gamestate == GAME) ? SKILL_TREE : GAME;
    }
    if (rpg->gamestate != SKILL_TREE)
        return 0;
    check_requirement(rpg->skill_tree);
    return 1;
}
