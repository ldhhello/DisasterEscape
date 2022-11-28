#pragma once

#include "Scene.h"

extern int quest_progress_healthjang;

extern Scene SceneHealthjang_load();
extern int** SceneHealthjang_load_map(int* x, int* y);
extern Structure* SceneHealthjang_load_structure(int* sz);
extern void SceneHealthjang_on_start();

extern void SceneHealthjang_on_door(int st, int dir);
extern void SceneHealthjang_on_kf94(int st, int dir);
extern void SceneHealthjang_on_donghyun(int st, int dir);
extern void SceneHealthjang_on_structure_active(int st, int dir);

extern void SceneHealthjang_reset();