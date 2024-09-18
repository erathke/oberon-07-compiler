#include <stdlib.h>

#include "raylib.h"
#include "microui.h"
#include "murl.h"

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

Font* _CreateFont() {
	return malloc(sizeof(Font));
}

void _LoadFont(const char *fileName, Font *font) {
	*font = LoadFont(fileName);
}

void _LoadFontEx(const char *fileName, Font *font, int fontSize, int *codepoints, int codepointCount) {
	*font = LoadFontEx(fileName, fontSize, codepoints, codepointCount);
}

void _DestroyFont(Font *font) {
	free(font);
}

// Microui

mu_Context* _mu_create_ctx() {
	return malloc(sizeof(mu_Context));
}

void _mu_destroy(mu_Context* ctx) {
	free(ctx);
}

int _mu_begin_window_ex(mu_Context* ctx, const char *title, mu_Rect *rect, int opt) {
	return mu_begin_window_ex(ctx, title, *rect, opt);
}

