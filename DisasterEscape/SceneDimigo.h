#pragma once

#include "Scene.h"

extern Scene SceneDimigo_load();
extern int** SceneDimigo_load_map(int* x, int* y);
extern Structure* SceneDimigo_load_structure(int* sz);
extern void SceneDimigo_on_start();
extern void SceneDimigo_on_structure_active(int st, int dir);