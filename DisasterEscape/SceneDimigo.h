// SceneXXXX 들은 모두 장면을 나타내는 친구들이다!
// SceneXXXX_load가 메인 Scene 객체를 반환하며, Game에서의 모든 장면 처리는 SceneXXXX_load() 및 Scene 객체만으로 이루어진다
// 내부 세부적인 구현 빼면 SceneXXXX 는 사실 다 똑같은 물건이다!!!

#pragma once

#include "Scene.h"
#include "SaveFile.h"

extern int outside_time; // in SceneDimigo.c 330줄정도?

extern Scene SceneDimigo_load();
extern int** SceneDimigo_load_map(int* x, int* y);
extern Structure* SceneDimigo_load_structure(int* sz);

extern void SceneDimigo_on_return(int ret);
extern bool SceneDimigo_check_end();
extern void SceneDimigo_clear();
extern void SceneDimigo_on_start();
extern void SceneDimigo_change_cafeteria_skin();
extern void SceneDimigo_on_key_pressed(char ch);
extern void SceneDimigo_on_tick();
extern void SceneDimigo_on_active_cafeteria(int st, int dir);
extern void SceneDimigo_on_bongwan(int st, int dir);
extern void SceneDimigo_on_hakbonggwan(int st, int dir);
extern void SceneDimigo_on_gangdang(int st, int dir);
extern void SceneDimigo_on_door(int st, int dir);
extern void SceneDimigo_on_ujunghaksa(int st, int dir);
extern void SceneDimigo_on_singwan(int st, int dir);
extern void SceneDimigo_on_structure_active(int st, int dir);

extern void SceneDimigo_reset();

extern void SceneDimigo_save(SaveFile* sf);
extern void SceneDimigo_load_file(SaveFile* sf);