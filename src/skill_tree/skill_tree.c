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

static int skill_test(rpg_t *rpg)
{
    rpg = rpg;
    printf("Skill test\n");
    return 1;
}

static skill_t *init_skill_tree(skill_t *skill)
{
    skill = add_skill(skill,
    init_skill("Earth", "Shoot a earth", 10, &skill_test));
    skill = add_skill(skill,
    init_skill("Water", "Shoot a water", 10, &skill_test));
    skill = add_skill(skill,
    init_skill("Dark", "Shoot a dark", 10, &skill_test));
    skill = add_skill(skill,
    init_skill("Light", "Shoot a light", 10, &skill_test));
    return skill;
}

skill_t *init_all_skill(void)
{
    skill_t *skill = init_skill
    ("Fireball", "Shoot a fireball", 10, &skill_test);

    skill = add_skill(skill,
    init_skill("Heal", "Heal yourself", 10, &skill_test));
    skill = add_skill(skill,
    init_skill("Lightning", "Shoot a lightning", 10, &skill_test));
    skill = add_skill(skill,
    init_skill("Ice", "Shoot a ice", 10, &skill_test));
    skill = add_skill(skill,
    init_skill("Poison", "Shoot a poison", 10, &skill_test));
    skill = add_skill(skill,
    init_skill("Wind", "Shoot a wind", 10, &skill_test));
    return init_skill_tree(skill);
}

skill_t *init_skill
(char *name, char *description, int cost, int (*function)(rpg_t *rpg))
{
    skill_t *skill = malloc(sizeof(skill_t));

    skill->name = name;
    skill->description = description;
    skill->cost = cost;
    skill->function = function;
    skill->background = init_sprite_from_file("assets/skill/23.png");
    sfSprite_setScale(skill->background, (sfVector2f){2.5, 2.5});
    skill->level = 0;
    skill->max_level = 5;
    skill->unlocked = 0;
    skill->next = NULL;
    return skill;
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

int unlock_skill(skill_t *skill, char *name)
{
    skill_t *tmp = skill;

    while (tmp != NULL) {
        if (tmp->name == name) {
            tmp->unlocked = 1;
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}

int manage_skill_tree(rpg_t *rpg)
{
    if (rpg->event.type == sfEvtKeyPressed && rpg->event.key.code == sfKeyY) {
        rpg->gamestate = (rpg->gamestate == GAME) ? SKILL_TREE : GAME;
    }
    return 1;
}
