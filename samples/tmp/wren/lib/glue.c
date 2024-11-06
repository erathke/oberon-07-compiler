#include <stdio.h>
#include "raylib.h"

// Raylib
void _DrawCircle(int x, int y, double r, Color* color) {
	DrawCircle(x, y, r, *color);
}

void _DrawRectangle(int x, int y, int w, int h, Color* color) {
	DrawRectangle(x, y, w, h, *color);
}

void _ClearBackground(Color* color) {
	ClearBackground(*color);
}

void _DrawText(const char *text, int x, int y, int font, Color* color) {
	DrawText(text, x, y, font, *color);
}

static Font font;
Font* _LoadFont(const char *fileName) {
	font = LoadFont(fileName);
	return &font;
}

