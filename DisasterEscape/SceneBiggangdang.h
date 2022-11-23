#pragma once

#include "Scene.h"

extern int quest_progress_biggangdang;

extern Scene SceneBiggangdang_load();
extern int** SceneBiggangdang_load_map(int* x, int* y);
extern Structure* SceneBiggangdang_load_structure(int* sz);
extern void SceneBiggangdang_on_start();

extern void SceneBiggangdang_on_door(int st, int dir);
extern void SceneBiggangdang_on_structure_active(int st, int dir);

extern void SceneBiggangdang_reset();