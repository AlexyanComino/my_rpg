/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_sounds
*/

#include "rpg.h"

void init_sounds2(sounds_t *sounds)
{
    sounds->myclock = init_my_clock();
    sounds->items = sfMusic_createFromFile("assets/Sounds/finquête.wav");
    sounds->quest = sfMusic_createFromFile("assets/Sounds/quest.flac");
    sounds->attack = sfMusic_createFromFile("assets/Sounds/attack.flac");
}

sounds_t *init_sounds(void)
{
    sounds_t *sounds = malloc(sizeof(sounds_t));

    sounds->sword = sfMusic_createFromFile("assets/Sounds/sword.wav");
    sounds->attack_fire = sfMusic_createFromFile
        ("assets/Sounds/attack_fire.wav");
    sounds->arrow = sfMusic_createFromFile("assets/Sounds/arc.wav");
    sounds->explosion = sfMusic_createFromFile("assets/Sounds/explosion.wav");
    sounds->attack_sword = sfMusic_createFromFile
        ("assets/Sounds/sword_touch.wav");
    sounds->burn = sfMusic_createFromFile("assets/Sounds/burn.wav");
    sounds->hammer = sfMusic_createFromFile("assets/Sounds/marteau.wav");
    sounds->click = sfMusic_createFromFile("assets/Sounds/click.wav");
    sounds->death = sfMusic_createFromFile("assets/Sounds/mort.wav");
    sounds->open = sfMusic_createFromFile("assets/Sounds/open.wav");
    sounds->close = sfMusic_createFromFile("assets/Sounds/close.wav");
    sounds->intro = sfMusic_createFromFile("assets/Sounds/intro.flac");
    sounds->loop = sfMusic_createFromFile("assets/Sounds/loop.flac");
    init_sounds2(sounds);
    return sounds;
}
