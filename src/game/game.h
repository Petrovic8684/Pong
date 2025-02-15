#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>

#include "../paddle/paddle.h"
#include "../ball/ball.h"
#include "../util/colors/colors.h"
#include "../util/sounds/sounds.h"
#include "../util/fonts/fonts.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 550

#define STARTING_GAME_SPEED 2.5;

extern SDL_Window *window;
extern SDL_Renderer *renderer;

extern bool is_window_open;
extern bool is_paused;
extern bool is_in_menu;
extern bool is_game_lost;

extern int game_speed;

extern int score_player_left;
extern int score_player_right;

void initialize_sdl(void);
void create_window_and_renderer(const char *title);
void handle_input(SDL_Event event);
void handle_player_input(SDL_Event event, bool reset);
void poll_events(void);
void render_dashes(void);
void render(void);
void initialize_game(void);
void increase_game_speed(Uint8 ammount);
void increase_score(bool left_player);
void restart_game(void);
void start_game_and_keep_running(void);
void game_cleanup(void);

#endif