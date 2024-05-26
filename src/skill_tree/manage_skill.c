/*
** EPITECH PROJECT, 2024
** skill
** File description:
** skill
*/

#include <stdlib.h>
#include "rpg.h"
#include "skill_tree.h"

int unlock_skill(skill_t *skill, char *name)
{
    skill_t *tmp = skill;

    while (tmp != NULL) {
        if (tmp->name == name && tmp->lock == 0) {
            tmp->unlocked = 1;
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}
