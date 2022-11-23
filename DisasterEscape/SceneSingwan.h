#pragma once

#include "Scene.h"

extern int quest_progress_singwan;

extern Scene SceneSingwan_load();
extern int** SceneSingwan_load_map(int* x, int* y);
extern Structure* SceneSingwan_load_structure(int* sz);
extern void SceneSingwan_on_start();

extern void SceneSingwan_on_door(int st, int dir);
extern void SceneSingwan_on_biggangdang(int st, int dir);
extern void SceneSingwan_on_structure_active(int st, int dir);

extern void SceneSingwan_reset();