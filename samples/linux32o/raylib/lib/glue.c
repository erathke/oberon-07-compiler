#include <stdio.h>
#include "raylib.h"

#define RAYLIB_NUKLEAR_IMPLEMENTATION
#define RAYLIB_NUKLEAR_INCLUDE_DEFAULT_FONT
#include "raylib-nuklear.h"

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

// Raylib-nuklear
struct nk_context* _InitNuklearEx(const char *fileName, double fontSize) {
	Font font = LoadFont(fileName);
	return InitNuklearEx(font, fontSize);
}

// Nuklear
typedef struct o_Rect {
	int x, y, w, h;
} o_Rect;

int _nk_begin(struct nk_context *ctx, const char *title, o_Rect* b, int flags) {
	return nk_begin(ctx, title, nk_recti(b->x, b->y, b->w, b->h), flags);
}

void _nk_layout_row_dynamic(struct nk_context *ctx, double height, int cols) {
	nk_layout_row_dynamic(ctx, height, cols);
}

void _nk_layout_row_static(struct nk_context *ctx, double height, int item_width, int cols) {
	nk_layout_row_static(ctx, height, item_width, cols);
}

