#include <stdio.h>
#include <assert.h>
#include "raylib.h"

// Raylib

typedef struct {
	double x, y, width, height;
} ORectangle;

typedef struct {
	double x, y;
} OVector2;


void _InitWindow(int w, int h, int size, const char *title) {
	InitWindow(w, h, title);
}

void _ClearBackground(Color* color) {
	ClearBackground(*color);
}

void _DrawCircle(int x, int y, double r, Color* color) {
	DrawCircle(x, y, r, *color);
}

void _DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color* color) {
	DrawLine(startPosX, startPosY, endPosX, endPosY, *color);
}

void _DrawRectangle(int x, int y, int w, int h, Color* color) {
	DrawRectangle(x, y, w, h, *color);
}

void _DrawRectangleLines(int posX, int posY, int width, int height, Color* color) {
	DrawRectangleLines(posX, posY, width, height, *color);
}

void _DrawLineEx(OVector2 *startPos, OVector2 *endPos, double thick, Color* color) {
	Vector2 p1 = (Vector2) {startPos->x, startPos->y};
	Vector2 p2 = (Vector2) {endPos->x, endPos->y};
	DrawLineEx(p1, p2, thick, *color);
}

void _DrawText(int size, const char *text, int x, int y, int font, Color* color) {
	DrawText(text, x, y, font, *color);
}

void _LoadFontEx(const char *fileName, Font *font, int fontSize, int *codepoints, int codepointCount) {
	*font = LoadFontEx(fileName, fontSize, codepoints, codepointCount);
}

void _LoadFont(int size, const char *fileName, int type, Font *font) {
	*font = LoadFont(fileName);
}

void _LoadTexture(int size, const char *fileName, Texture* texture) {
	*texture = LoadTexture(fileName);
}

void _DrawTexture(Texture2D *texture, int x, int y, Color* color) {
	DrawTexture(*texture, x, y, *color);
}

void _DrawTextureRec(Texture2D *texture, ORectangle *source, OVector2* position, Color* color) {
	Rectangle rect = (Rectangle) {source->x, source->y, source->width, source->height};
	Vector2 p = (Vector2) {position->x, position->y};
	DrawTextureRec(*texture, rect, p, *color);
}

void _LoadImage(int size, const char *fileName, int type, Image* image) {
	*image = LoadImage(fileName);
}

void _UnloadImage(int type, Image* image) {
	UnloadImage(*image);
}

void _SetWindowIcon(Image *image) {
	SetWindowIcon(*image); 
}

void _ColorFromHSV(double hue, double saturation, double value, int _, Color *color) {
	*color = ColorFromHSV(hue, saturation, value);
}

// raudio
void _LoadSound(int size, const char *fileName, int type, Sound *sound) {
	*sound = LoadSound(fileName);
}

void _PlaySound(Sound *sound) {
	PlaySound(*sound);
}

void _StopSound(Sound *sound) {
	StopSound(*sound);
}

bool _IsSoundPlaying(Sound *sound) {
	return IsSoundPlaying(*sound);
}
