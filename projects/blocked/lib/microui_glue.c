#include <stdlib.h>

#include "microui.h"
#include "murl.h"

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

int _mu_textwidth(mu_Context *ctx, int textLen, const char *text) {
	mu_Font font = ctx->style->font;
	return ctx->text_width(font, text, textLen);
}

int _mu_textheight(mu_Context *ctx) {
	mu_Font font = ctx->style->font;
	return ctx->text_height(font);
}

void mu_hrule(mu_Context *ctx, int thickness) {
	mu_Id     id = mu_get_id(ctx, &thickness, sizeof(thickness));
	mu_Rect rect = mu_layout_next(ctx);
	mu_update_control(ctx, id, rect, 0);
	mu_Color color = ctx->style->colors[MU_COLOR_TEXT];
	mu_Rect hrect = {rect.x, rect.y + (rect.h / 2), rect.w, thickness};
	mu_draw_rect(ctx, hrect, color);
}
