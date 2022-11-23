#pragma once

#include "Scene.h"

extern int quest_progress_gangdang;

extern Scene SceneGangdang_load();
extern int** SceneGangdang_load_map(int* x, int* y);
extern Structure* SceneGangdang_load_structure(int* sz);
extern void SceneGangdang_on_start();

extern void SceneGangdang_on_door(int st, int dir);
extern void SceneGangdang_on_healthjang(int st, int dir);
extern void SceneGangdang_on_structure_active(int st, int dir);

extern void SceneGangdang_reset();