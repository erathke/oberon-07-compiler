#include <stdio.h>
#include <assert.h>
#include "raylib.h"

// Raylib
void _DrawCircle(int x, int y, double r, Color* color) {
	DrawCircle(x, y, r, *color);
}

void _DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color* color) {
	DrawLine(startPosX, startPosY, endPosX, endPosY, *color);
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

void _LoadFontEx(const char *fileName, Font *font, int fontSize, int *codepoints, int codepointCount) {
	*font = LoadFontEx(fileName, fontSize, codepoints, codepointCount);
}

void _UnloadFont(const char *fileName, Font *font) {
	*font = LoadFont(fileName);
}

void _LoadTexture(const char *fileName, Texture* texture) {
	*texture = LoadTexture(fileName);
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

void _LoadImage(const char *fileName, Image* image) {
	*image = LoadImage(fileName);
}

void _UnloadImage(Image* image) {
	UnloadImage(*image);
}

void _SetWindowIcon(Image *image) {
	SetWindowIcon(*image); 
} 

// raudio
void _LoadSound(const char *fileName, Sound *sound) {
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
