/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** init_pawn
*/
#pragma once

// Init pawn
float get_new_job_cooldown(pawn_job_t job);
entity_t *init_entity_pawn(char **infos);

// Init items pawn
item_pawn_t *init_item_pawn(item_pawn_type_t item_type);
