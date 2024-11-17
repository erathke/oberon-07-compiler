#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "microui.h"
#include "murl.h"

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

int _mu_multitext(mu_Context *ctx, int maxCols, int textLen, char *text, int _, mu_Vec2 *cursorPos) {
	mu_Id     id = mu_get_id(ctx, &text, sizeof(text));
	mu_Rect rect = mu_layout_next(ctx);
	mu_update_control(ctx, id, rect, MU_OPT_HOLDFOCUS);

	/* handle input */
	int res = 0;
	if (ctx->mouse_pressed == MU_MOUSE_LEFT && ctx->focus == id) {
		res |= MU_RES_ACTIVE;
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
				cursorPos->x++;
				if (cursorPos->x >= maxCols){
					cursorPos->y++;
					cursorPos->x = 0;
				}
			}
		}
		// remove characters
		if (ctx->key_pressed & MU_KEY_BACKSPACE) {
			cursorPos->x--;
			if (cursorPos->x < 0){
				if (cursorPos->y > 0) {
					cursorPos->y--;
					cursorPos->x = maxCols - 1;
				} else {
					cursorPos->x = 0;
					cursorPos->y = 0;
				}
			}
			int tpos = cursorPos->x + (cursorPos->y * maxCols); 
			text[tpos] = 0;
			res |= MU_RES_CHANGE;
		}
		// submit changes
		if (ctx->key_pressed & MU_KEY_RETURN) {
			mu_set_focus(ctx, 0);
			res |= MU_RES_SUBMIT;
		}
	}
	
	/* draw */
	mu_Font font = ctx->style->font;
	mu_Color panelColor = {18, 18, 18, 255};
	mu_Color textColor = {255, 0, 0, 255};
	mu_Vec2 posText = {rect.x + 5, rect.y + 10};
	const int lineHeight = ctx->text_height(font) + 5;
	mu_draw_rect(ctx, rect, panelColor);
	
	// Drawing text
	for (int i = 0;  i <= cursorPos->y; i++) {
		const char *colOffs = text + (i * maxCols); 
		mu_draw_text(ctx, font, colOffs, maxCols, posText, textColor);
		posText.y += lineHeight;
	}
	
	if (ctx->focus == id)  {	
		mu_Color cursorColor = {255, 255, 0, 255};
		int px = ctx->text_width(font, "#", 1) + 1;
		const int py = lineHeight;
		int x = rect.x + (cursorPos->x * px) + 3;
		int y = rect.y + (cursorPos->y * py) + 5;
		mu_Rect cursorRect = {x, y + 2, 2, py};
		mu_Rect maxPosRect = {rect.x + (maxCols * px) + 6, rect.y + 1, 1, rect.h - 2};
		
		mu_draw_box(ctx, rect, textColor);
		mu_draw_rect(ctx, cursorRect, cursorColor);
		cursorColor.a = 100;
		mu_draw_rect(ctx, maxPosRect, cursorColor);
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
