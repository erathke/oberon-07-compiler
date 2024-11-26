#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "microui.h"
#include "murl.h"

#ifndef MAX
	#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif

#ifndef MIN
	#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif

#define TAGS 16

static mu_Color tag_colors[TAGS] = {
	{255, 255, 255, 50}, // white = comment
	{255,   0,   0, 50}, // red = definition
	{255, 255,   0, 50}, // yellow = integer
	{0,   255, 255, 50}, // cyan = real
	{  0, 255,   0, 50}, // green = compile
	{ 50,  50, 220, 50}, // blue = string
	{180, 180, 180, 50}, // gray = macro
	{225, 193, 110, 50}, // brass = alias def
	{225, 193, 110, 50}, // brass = alias write
	{225, 193, 110, 50}, // brass = alias read
	{225, 193, 110, 50}, // brass = alias pointer write
	{225, 193, 110, 50}, // brass = alias pointer read
	{255, 255, 255, 15},
	{191, 255,   0, 150}, // lime = brk
	{255, 102,   0, 50}, // orange = at
	{255,   0, 255, 50} // ret
};

static const char hexChars[TAGS] = ".:#$*\"%@><!^.|&\\";

static void updateCursorPos(mu_Rect *rect, mu_Vec2 *mousePos, 
		mu_Vec2 *cursor, int lineHeight, int colWidth, int maxCols, int visibleLines) {

	int mx = mousePos->x - (mousePos->x % colWidth);
	int my = mousePos->y - (mousePos->y % lineHeight);
	int nx = mx - rect->x;
	int ny = my - rect->y;
	cursor->x = MIN(nx / colWidth, maxCols - 1);
	cursor->y = MIN(ny / lineHeight, visibleLines - 1);
}

static bool shiftDataLeft(mu_Vec2 *cursor, char *data, int maxCols) {
	bool moved = false;
	if (cursor->x > 0) {
		int tpos = cursor->x + (cursor->y * maxCols);
		int size = maxCols - cursor->x;
		memmove(data + tpos - 1, data + tpos, size);
		data[tpos + size - 1] = 0;
		moved = true;
	}
	return moved;
}

static bool shiftDataRight(mu_Vec2 *cursor, char *data, int maxCols) {
	bool moved = false;
	if (cursor->x < maxCols - 1) {
		int tpos = cursor->x + (cursor->y * maxCols);
		int size = (maxCols - cursor->x) - 1;
		memmove(data + tpos + 1, data + tpos, size);
		data[tpos] = 0;
		moved = true;
	}
	return moved;
}

static bool shiftDataUp(mu_Vec2 *cursor, int dataSize, char *data, int maxLines, int maxCols) {
	bool moved = false;
	if (cursor->y > 0) {
		int tpos = cursor->x + (cursor->y * maxCols);
		int size = dataSize - tpos - cursor->x;
		memmove(data + tpos - maxCols, data + tpos, size);
		// cleaning line
		tpos = (maxLines - 1) * maxCols;
		//printf("lines: %d, cols: %d, pos: %d\n", maxLines, maxCols, tpos);
		memset(data + tpos, 0, maxCols);
		moved = true;
	}
	return moved;
}

static bool shiftDataDown(mu_Vec2 *cursor, int dataSize, char *data, int *yOffs, int visibleLines, int maxCols) {
	bool moved = false;
	if (cursor->y < *yOffs + visibleLines - 1) {
		int tpos = cursor->x + (cursor->y * maxCols);
		int size = dataSize - tpos - cursor->x;
		memmove(data + tpos + maxCols, data + tpos, size);
		// cleaning line
		memset(data + tpos, 0, maxCols);
		moved = true;
	}
	return moved;
}

static void moveCursorLeft(mu_Vec2 *cursor, int *yOffs, int maxCols, int maxLines, int visibleLines) {
	cursor->x--;
	if (cursor->x < 0){
		if (cursor->y > 0) {
			//printf("y: %d, offs: %d\n", cursor->y, *yOffs);
			if (cursor->y ==  *yOffs) {
				--*yOffs;
			}
			cursor->y--;
			cursor->x = maxCols - 1;
		} 
		else {
			cursor->x = 0;
			cursor->y = 0;
		}
	}
}

static void moveCursorRight(mu_Vec2 *cursor, int *yOffs, int maxCols, int maxLines, int visibleLines) {
	cursor->x++;
	if (cursor->x >= maxCols){
		if (cursor->y < maxLines - 1) {
			cursor->y++;
			cursor->x = 0;
			if (cursor->y == (visibleLines + *yOffs)) {
				++*yOffs;
			}
		} 
		else {
			cursor->x = maxCols - 1;
			cursor->y = maxLines - 1;
		}
	}
}

static void moveCursorUp(mu_Vec2 *cursor, int n, int *yOffs, int visibleLines) {
	if (cursor->y > 0) {
		cursor->y -= n;
		if (cursor->y < *yOffs) {
			*yOffs = MAX(*yOffs - n, 0);
		}
	}
}

static void moveCursorDown(mu_Vec2 *cursor, int n, int *yOffs, int maxLines, int visibleLines) {
	if (cursor->y < maxLines - 1) {
		cursor->y += n;
		if (cursor->y >= (*yOffs + visibleLines)) {
			*yOffs = MIN(*yOffs + n, maxLines - visibleLines);
		}
	}
}

int _mu_multitext(mu_Context *ctx, int maxCols, int textLen, char *text, int _, mu_Vec2 *cursor, int *yOffs) {
	
	mu_Id     id = mu_get_id(ctx, &text, sizeof(text));
	mu_Rect rect = mu_layout_next(ctx);
	mu_update_control(ctx, id, rect, MU_OPT_HOLDFOCUS);
	
	mu_Font font = ctx->style->font;
	const int lineHeight = ctx->text_height(font) + 5;
	const int colWidth = ctx->text_width(font, "#", 1) + 1;
	const int visibleLines = rect.h / lineHeight;
	const int maxLines = (textLen / maxCols) - 1; // avoiding half line
	
	/* handle input */
	int res = 0;
	if (ctx->mouse_pressed == MU_MOUSE_RIGHT && ctx->focus == id) {
		res |= MU_RES_ACTIVE;
		updateCursorPos(&rect, &ctx->mouse_pos, cursor, lineHeight, colWidth, maxCols, visibleLines);
		cursor->y += *yOffs;
	}
	if (ctx->focus == id) {
		// insert characters
		int len = strlen(ctx->input_text);
		if (len > 0) {
			int i = 0;
			while (i < len) {
				int tpos = cursor->x + (cursor->y * maxCols); 
				text[tpos] = ctx->input_text[i];
				moveCursorRight(cursor, yOffs, maxCols, maxLines, visibleLines);
				i++;
			}
			res |= MU_RES_CHANGE;
		}
		// moving data
		if (IsKeyDown(KEY_LEFT_SHIFT)) {
			// shift data left from cursor x to end of line
			if (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT)) {
				if (shiftDataLeft(cursor, text, maxCols)) {
					moveCursorLeft(cursor, yOffs, maxCols, maxLines, visibleLines);
					res |= MU_RES_CHANGE;
				}
			}
			// shift data right from cursor x to end of line
			if (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT)) {
				if (shiftDataRight(cursor, text, maxCols)) {
					moveCursorRight(cursor, yOffs, maxCols, maxLines, visibleLines);
					res |= MU_RES_CHANGE;
				}
			}
			// shift data up from current line
			if (IsKeyPressed(KEY_UP) || IsKeyPressedRepeat(KEY_UP)) {
				if (shiftDataUp(cursor, textLen, text, maxLines, maxCols)) {
					moveCursorUp(cursor, 1, yOffs, visibleLines);
					res |= MU_RES_CHANGE;
				}
			}
			// shift data down from current line
			if (IsKeyPressed(KEY_DOWN) || IsKeyPressedRepeat(KEY_DOWN)) {
				if (shiftDataDown(cursor, textLen, text, yOffs, visibleLines, maxCols)) {
					moveCursorDown(cursor, 1, yOffs, maxLines, visibleLines);
					res |= MU_RES_CHANGE;
				}
			}
			// insert line after
			if (ctx->key_pressed & MU_KEY_RETURN) {
				cursor->x = 0;
				moveCursorDown(cursor, 1, yOffs, maxLines, visibleLines);
				if (shiftDataDown(cursor, textLen, text, yOffs, visibleLines, maxCols)) {
					res |= MU_RES_CHANGE;
				}
			}
			// clean from cursor to end of line
			if (IsKeyPressed(KEY_DELETE)) {
				int tpos = cursor->x + (cursor->y * maxCols); 
				int size = maxCols - cursor->x;
				memset(text + tpos, 0, size);
				res |= MU_RES_CHANGE;
			}
		}
		else if (IsKeyDown(KEY_LEFT_CONTROL)) {
			// tags
			// move tag char up
			if (IsKeyPressed(KEY_UP) || IsKeyPressedRepeat(KEY_UP)) {
				int tpos = cursor->x + (cursor->y * maxCols); 
				text[tpos] = (text[tpos] + 1) % TAGS;
				res |= MU_RES_CHANGE;
			}
			// move tag char down
			if (IsKeyPressed(KEY_DOWN) || IsKeyPressedRepeat(KEY_DOWN)) {
				int tpos = cursor->x + (cursor->y * maxCols); 
				text[tpos] = (text[tpos] - 1) % TAGS;
				if (text[tpos] < 0) {
					text[tpos] = TAGS - 1;
				}
				res |= MU_RES_CHANGE;
			}
		}
		else {
			// remove character at left from current position
			if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) {
				moveCursorLeft(cursor, yOffs, maxCols, maxLines, visibleLines);
				int tpos = cursor->x + (cursor->y * maxCols); 
				text[tpos] = 0;
				res |= MU_RES_CHANGE;
			}
			// move character at current position
			if (IsKeyPressed(KEY_DELETE)) {
				int tpos = cursor->x + (cursor->y * maxCols); 
				text[tpos] = 0;
				res |= MU_RES_CHANGE;
			}
			// cursor movement
			// move cursor left / wrap to upper line
			if (IsKeyPressed(KEY_LEFT) || IsKeyPressedRepeat(KEY_LEFT)) {
				moveCursorLeft(cursor, yOffs, maxCols, maxLines, visibleLines);
			}
			// move cursor right / wrap to lower line
			if (IsKeyPressed(KEY_RIGHT) || IsKeyPressedRepeat(KEY_RIGHT)) {
				moveCursorRight(cursor, yOffs, maxCols, maxLines, visibleLines);
			}
			// move cursor up / stop at line 0
			if (IsKeyPressed(KEY_UP) || IsKeyPressedRepeat(KEY_UP)) {
				moveCursorUp(cursor, 1, yOffs, visibleLines);
			}
			// move cursor down / stop at max line
			if (IsKeyPressed(KEY_DOWN) || IsKeyPressedRepeat(KEY_DOWN)) {
				moveCursorDown(cursor, 1, yOffs, maxLines, visibleLines);
			}
			// move cursor up n positions
			if (IsKeyPressed(KEY_PAGE_UP)) {
				int n = cursor->y;
				if (cursor->y >= visibleLines) {
					n = visibleLines - 1;
				}
				moveCursorUp(cursor, n, yOffs, visibleLines);
			}
			// move cursor down n positions
			if (IsKeyPressed(KEY_PAGE_DOWN)) {
				int n = visibleLines - 1;
				if ((cursor->y + visibleLines) >= maxLines) {
					n = (maxLines - 1) - cursor->y;
				}
				moveCursorDown(cursor, n, yOffs, maxLines, visibleLines);
			}
			// move cursor to the beginning of the line
			if (IsKeyPressed(KEY_HOME)) {
				cursor->x = 0;
			}
			// move cursor to the end of the line
			if (IsKeyPressed(KEY_END)) {
				cursor->x = maxCols - 1;
			}
			// submit changes
			if (ctx->key_pressed & MU_KEY_RETURN) {
				mu_set_focus(ctx, 0);
				res |= MU_RES_SUBMIT;
			}
		}
	}
	
	/* draw */
	
	mu_Color panelColor = {18, 18, 18, 255};
	if (ctx->focus == id)  {
		mu_draw_rect(ctx, rect, panelColor);
	}
	else {
		panelColor.a = 210;
		mu_draw_rect(ctx, rect, panelColor);
	}
	
	mu_Color cursorColor = {255, 0, 255, 255};
	int cx = rect.x + (cursor->x * colWidth) + 3;
	int totalYOffs = cursor->y - *yOffs; 
	int cy = rect.y + (totalYOffs * lineHeight) + 5;
	mu_Rect cursorRect = {cx + 1, cy + 2, colWidth + 1, lineHeight};
	// Drawing cursor
	if (ctx->focus == id)  {
		
		if (IsKeyDown(KEY_LEFT_SHIFT)) {
			int width = (maxCols - cursor->x) * colWidth;
			mu_Rect cursorRect = {cx + 1, cy + 2, width + 1, lineHeight};
			mu_draw_box(ctx, cursorRect, cursorColor);
		}
		else if (IsKeyDown(KEY_LEFT_CONTROL)) {
			mu_Color cursorColor = {0, 255, 255, 255};
			mu_draw_box(ctx, cursorRect, cursorColor);
		}
		else {
			mu_draw_box(ctx, cursorRect, cursorColor);
		}
	}
	else {
		mu_draw_rect(ctx, cursorRect, cursorColor);
	}
	
	// Drawing text
	mu_Color textColor = tag_colors[0];
	mu_Vec2 posText = {rect.x + 5, rect.y + 10};
	
	mu_Color currentColor = textColor;
	
	for (int y = 0; y < visibleLines; y++) {
		for (int x = 0; x < maxCols; x++) {
			int totalYOffs = *yOffs + y;
			const char *colOffs = text + (totalYOffs * maxCols) + x;
			char ch = colOffs[0];
			if (ch > TAGS) {
				if (ch != ' ') {
					currentColor.a = 255;
				} 
				else { // space char
					ch = '_';
					currentColor.a = 50;
				}
				mu_draw_text(ctx, font, &ch, 1, posText, currentColor);
			} else {
				currentColor = tag_colors[ch];
				if (x == cursor->x && totalYOffs == cursor->y) {
					currentColor.a = 200;
				}
				if (ch != 0)
					mu_draw_text(ctx, font, hexChars + ch, 1, posText, currentColor);
			}
			posText.x += colWidth;
		}
		posText.y += lineHeight;
		posText.x = rect.x + 5;
	}
	
	return res;
}
