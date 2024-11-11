#include <stdio.h>
#include <assert.h>
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

void _LoadTexture(const char *fileName, Texture* texture) {
	Texture2D t = LoadTexture(fileName);
	*texture = t;
}

void _DrawTexture(Texture2D *texture, int x, int y, Color* color) {
	DrawTexture(*texture, x, y, *color);
}


typedef struct {
	int x, y, width, height;
} ORectangle;

typedef struct {
	int x, y;
} OVector2;

void _DrawTextureRec(Texture2D *texture, ORectangle *source, OVector2* position, Color* color) {
	Rectangle rect = (Rectangle) {source->x, source->y, source->width, source->height};
	Vector2 p = (Vector2) {position->x, position->y};
	DrawTextureRec(*texture, rect, p, *color);
}
