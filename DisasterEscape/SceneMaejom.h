#pragma once

#include "Scene.h"

extern Scene SceneMaejom_load();
extern int** SceneMaejom_load_map(int* x, int* y);
extern Structure* SceneMaejom_load_structure(int* sz);
extern void SceneMaejom_on_start();

extern void SceneMaejom_on_door(int st, int dir);
extern void SceneMaejom_on_snack(int st, int dir);
extern void SceneMaejom_on_towel(int st, int dir);
extern void SceneMaejom_on_water(int st, int dir);
extern void SceneMaejom_on_structure_active(int st, int dir);

extern void SceneMaejom_reset();

extern int quest_progress_maejom;