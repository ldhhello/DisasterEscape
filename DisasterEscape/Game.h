#pragma once

#include "Include.h"
#include "Scene.h"

extern int player_x, player_y;
extern int player_idx;

extern void Game_print_map(bool fade_in);
extern void Game_print_earthquake(int ms);

extern void Game_change_scene(Scene sc, bool is_enter);

extern void Game_speechbubble(const char* str);
extern void Game_system_message(const char* str);

extern void Game_ending_credit(const char* str);

extern int Game_modal_select_box(char(*str)[100], int cnt);
extern int Game_modal_select_box_speech(char* speech, char(*str)[100], int cnt);

extern void Game_die();
extern void Game_clear();
extern void Game_reset_all();
extern void Game_set_return(int ret);

extern void Game_save(int slot);

extern void Game_modal();