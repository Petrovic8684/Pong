#ifndef FONTS_H
#define FONTS_H

#include <SDL2/SDL_ttf.h>
#include "../../game/game.h"

struct text
{
    SDL_Surface *text_surface;
    SDL_Texture *text_texture;
    SDL_Rect text_rect;
};

extern TTF_Font *font;

extern struct text score_player_left_text;
extern struct text score_player_right_text;

extern struct text paused_text;

extern struct text pong_text;
extern struct text made_by_text;
extern struct text press_enter_to_start_text;

extern bool has_game_text_changed;
extern bool should_render_pong_text;

void initialize_text(void);
void update_text(const char *prefix, bool has_variable, const int variable, SDL_Color color, int x, int y, bool add_padding, struct text *text);
void render_game_text(void);
void render_pong_text(void);
void render_menu_text(void);
void text_cleanup(struct text *text);
void font_cleanup(void);

#endif