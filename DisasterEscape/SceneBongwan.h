#pragma once

#include "Scene.h"

extern Scene SceneBongwan_load();
extern int** SceneBongwan_load_map(int* x, int* y);
extern Structure* SceneBongwan_load_structure(int* sz);
extern void SceneBongwan_on_start();

extern void SceneBongwan_on_structure_active(int st, int dir);