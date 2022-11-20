#pragma once

#include "Scene.h"

extern Scene SceneCafeteria_load();
extern int** SceneCafeteria_load_map(int* x, int* y);
extern Structure* SceneCafeteria_load_structure(int* sz);
extern void SceneCafeteria_on_start();

extern void SceneCafeteria_on_door(int st, int dir);
extern void SceneCafeteria_on_rice(int st, int dir);
extern void SceneCafeteria_on_structure_active(int st, int dir);

extern void SceneCafeteria_reset();