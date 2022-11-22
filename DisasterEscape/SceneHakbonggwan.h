#pragma once

#include "Scene.h"

extern int quest_progress_hakbonggwan;

extern Scene SceneHakbonggwan_load();
extern int** SceneHakbonggwan_load_map(int* x, int* y);
extern Structure* SceneHakbonggwan_load_structure(int* sz);
extern void SceneHakbonggwan_on_start();

extern void SceneHakbonggwan_on_structure_active(int st, int dir);

extern void SceneHakbonggwan_reset();