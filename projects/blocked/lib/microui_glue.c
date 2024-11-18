#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "microui.h"
#include "murl.h"

#ifndef MAX
	#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif

#ifndef MIN
	#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif

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

int _mu_layout_next(mu_Context* ctx, mu_Rect *rect) {
	*rect = mu_layout_next(ctx);
}

int _mu_layout_set_next(mu_Context* ctx, mu_Rect *rect, int relative) {
	mu_layout_set_next(ctx, *rect, relative);
}

static void updateCursorPos(mu_Rect *rect, mu_Vec2 *mousePos, 
		mu_Vec2 *cursorPos, int lineHeight, int colWidth, int maxCols, int maxLines) {

	int mx = mousePos->x - (mousePos->x % colWidth);
	int my = mousePos->y - (mousePos->y % lineHeight);
	int nx = mx - rect->x;
	int ny = my - rect->y;
	cursorPos->x = MIN(nx / colWidth, maxCols - 1);
	cursorPos->y = MIN(ny / lineHeight, maxLines - 1);
}

static void moveCursorLeft(mu_Vec2 *cursorPos, int maxCols) {
	cursorPos->x--;
	if (cursorPos->x < 0){
		if (cursorPos->y > 0) {
			cursorPos->y--;
			cursorPos->x = maxCols - 1;
		} 
		else {
			cursorPos->x = 0;
			cursorPos->y = 0;
		}
	}
}

static void moveCursorRight(mu_Vec2 *cursorPos, int maxCols, int maxLines) {
	cursorPos->x++;
	if (cursorPos->x >= maxCols){
		if (cursorPos->y < maxLines - 1) {
			cursorPos->y++;
			cursorPos->x = 0;
		} 
		else {
			cursorPos->x = maxCols - 1;
			cursorPos->y = maxLines - 1;
		}
	}
}

int _mu_multitext(mu_Context *ctx, int maxCols, int textLen, char *text, int _, mu_Vec2 *cursorPos) {
	mu_Id     id = mu_get_id(ctx, &text, sizeof(text));
	mu_Rect rect = mu_layout_next(ctx);
	mu_update_control(ctx, id, rect, MU_OPT_HOLDFOCUS);
	
	mu_Font font = ctx->style->font;
	const int lineHeight = ctx->text_height(font) + 5;
	const int colWidth = ctx->text_width(font, "#", 1) + 1;
	const int maxVisibleLines = rect.h / lineHeight;
	const int maxLines = maxVisibleLines; // TODO: calculate
	
	/* handle input */
	int res = 0;
	if (ctx->mouse_pressed == MU_MOUSE_LEFT && ctx->focus == id) {
		res |= MU_RES_ACTIVE;
		updateCursorPos(&rect, &ctx->mouse_pos, cursorPos, lineHeight, colWidth, maxCols, maxVisibleLines);
	}
	if (ctx->focus == id) {
		// insert characters
		int len = strlen(ctx->input_text);
		if (len > 0) {
			int i = 0;
			while (i < len) {
				int tpos = cursorPos->x + (cursorPos->y * maxCols); 
				text[tpos] = ctx->input_text[i];
				res |= MU_RES_CHANGE;
				i++;
				moveCursorRight(cursorPos, maxCols, maxLines);
			}
		}
		// remove characters
		if (ctx->key_pressed & MU_KEY_BACKSPACE) {
			moveCursorLeft(cursorPos, maxCols);
			int tpos = cursorPos->x + (cursorPos->y * maxCols); 
			text[tpos] = 0;
			res |= MU_RES_CHANGE;
		}
		
		if (IsKeyPressed(KEY_DELETE)) {
			int tpos = cursorPos->x + (cursorPos->y * maxCols); 
			text[tpos] = 0;
			res |= MU_RES_CHANGE;
		}
		
		// cursor movement
		if (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT)) {
			moveCursorLeft(cursorPos, maxCols);
		}
		
		if (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT)) {
			moveCursorRight(cursorPos, maxCols, maxLines);
		}
		
		if (IsKeyPressed(KEY_UP) || IsKeyPressedRepeat(KEY_UP)) {
			if (cursorPos->y > 0) {
				cursorPos->y--;
			}
		}
		
		if (IsKeyPressed(KEY_DOWN) || IsKeyPressedRepeat(KEY_DOWN)) {
			if (cursorPos->y < maxLines - 1) {
				cursorPos->y++;
			}
		}
		
		// submit changes
		if (ctx->key_pressed & MU_KEY_RETURN) {
			mu_set_focus(ctx, 0);
			res |= MU_RES_SUBMIT;
		}
	}
	
	/* draw */
	mu_Color panelColor = {18, 18, 18, 255};
	mu_Color textColor = {255, 0, 0, 255};
	mu_Color textColor2 = {255, 0, 0, 40};
	mu_Vec2 posText = {rect.x + 5, rect.y + 10};
	
	mu_draw_rect(ctx, rect, panelColor);
	
	// Drawing cursor
	if (ctx->focus == id)  {
		mu_Color cursorColor = {255, 255, 0, 220};
		int x = rect.x + (cursorPos->x * colWidth) + 3;
		int y = rect.y + (cursorPos->y * lineHeight) + 5;
		mu_Rect cursorRect = {x + 1, y + 2, colWidth, lineHeight};
		mu_draw_rect(ctx, cursorRect, cursorColor);
		
		mu_Rect maxPosRect = {rect.x + (maxCols * colWidth) + 6, rect.y + 1, 1, rect.h - 2};
		cursorColor.a = 100;
		mu_draw_rect(ctx, maxPosRect, cursorColor);
	} 
	
	// Drawing text
	const char *zeroChar = "0";
	for (int y = 0; y < maxVisibleLines; y++) {
		for (int x = 0; x < maxCols; x++) {
			const char *colOffs = text + (y * maxCols) + x;
			if (colOffs[0] != '\0') {
				mu_draw_text(ctx, font, colOffs, 1, posText, textColor);
			} else {
				mu_draw_text(ctx, font, zeroChar, 1, posText, textColor2);
			}
			posText.x += colWidth;
		}
		posText.y += lineHeight;
		posText.x = rect.x + 5;
	}

	return res;
}

int _mu_textwidth(mu_Context *ctx, int textLen, const char *text) {
	mu_Font font = ctx->style->font;
	return ctx->text_width(font, text, textLen);
}

int _mu_textheight(mu_Context *ctx) {
	mu_Font font = ctx->style->font;
	return ctx->text_height(font);
}
