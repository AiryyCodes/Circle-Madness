#pragma once

bool window_init(const char* title, int width, int height);

void window_tick();

void window_cleanup();

int get_window_width();
int get_window_height();

int get_framebuffer_width();
int get_framebuffer_height();
