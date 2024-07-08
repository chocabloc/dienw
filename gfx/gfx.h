#pragma once

// TODO: have an actual World object which you draw

#include "asset/manager.h"

void gfx_init();
bool gfx_should_close();
void gfx_close();

void gfx_clear();
void gfx_draw_object(instance_t* ins);
void gfx_render();
