#pragma once

#include "scene.h"

bool game_init();

void game_update();

void game_render();

void game_cleanup();

Scene& get_current_scene();
