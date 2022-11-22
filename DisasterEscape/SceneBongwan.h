#pragma once

#include "Scene.h"

extern int quest_progress_bongwan;

extern Scene SceneBongwan_load();
extern int** SceneBongwan_load_map(int* x, int* y);
extern Structure* SceneBongwan_load_structure(int* sz);
extern void SceneBongwan_on_start();

extern void SceneBongwan_on_table(int st, int dir);
extern void Scenebongwan_on_clean_air(int st, int dir);
extern void SceneBongwan_on_door(int st, int dir);
extern void SceneBongwan_on_structure_active(int st, int dir);

extern void SceneBongwan_reset();