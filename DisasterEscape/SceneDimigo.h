#pragma once

#include "Scene.h"

extern Scene SceneDimigo_load();
extern int** SceneDimigo_load_map(int* x, int* y);
extern Structure* SceneDimigo_load_structure(int* sz);

extern void SceneDimigo_on_return(int ret);
extern void SceneDimigo_on_start();
extern void SceneDimigo_on_active_cafeteria(int st, int dir);
extern void SceneDimigo_on_bongwan(int st, int dir);
extern void SceneDimigo_on_hakbonggwan(int st, int dir);
extern void SceneDimigo_on_door(int st, int dir);
extern void SceneDimigo_on_ujunghaksa(int st, int dir);
extern void SceneDimigo_on_singwan(int st, int dir);
extern void SceneDimigo_on_structure_active(int st, int dir);

extern void SceneDimigo_reset();