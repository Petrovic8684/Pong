#include "game.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool is_window_open = true;
bool is_paused = false;
bool is_in_menu = true;
bool is_game_lost = false;

int left_player_movement = 0;
int right_player_movement = 0;

int game_speed = STARTING_GAME_SPEED;

int score_player_left = 0;
int score_player_right = 0;

void initialize_sdl(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "SDL failed to initialize: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void create_window_and_renderer(const char *title)
{
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    if (window == NULL)
    {
        fprintf(stderr, "SDL window failed to initialize: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if (renderer == NULL)
    {
        fprintf(stderr, "SDL renderer failed to initialize: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

void handle_input(SDL_Event event)
{
    switch (event.key.keysym.sym)
    {
    case SDLK_RETURN:
        if (is_in_menu == false)
            return;
        is_in_menu = false;
        break;
    case SDLK_ESCAPE:
        if (is_in_menu == true)
            return;
        if (is_paused == true)
            is_paused = false;

        is_in_menu = true;
        break;
    case SDLK_p:
        if (is_in_menu == true)
            return;
        is_paused = !is_paused;
        has_game_text_changed = true;
        break;
    }
}

void handle_player_input(SDL_Event event, bool reset)
{
    switch (event.key.keysym.sym)
    {
    case SDLK_UP:
        right_player_movement = reset ? 0 : -5;
        break;
    case SDLK_DOWN:
        right_player_movement = reset ? 0 : 5;
        break;
    case SDLK_w:
        left_player_movement = reset ? 0 : -5;
        break;
    case SDLK_s:
        left_player_movement = reset ? 0 : 5;
        break;
    }
}

void poll_events(void)
{
    SDL_Event event;
    while (SDL_PollEvent(&event) > 0)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            is_window_open = false;
            break;
        case SDL_KEYUP:
            handle_input(event);
            handle_player_input(event, true);
            break;
        case SDL_KEYDOWN:
            handle_player_input(event, false);
            break;
        }
    }
}

void render_dashes(void)
{
    SDL_SetRenderDrawColor(renderer, color_gray.r, color_gray.g, color_gray.b, 255);

    SDL_Rect dash;

    dash.x = (WINDOW_WIDTH - 5) / 2;

    dash.w = 5;
    dash.h = 20;

    for (Uint8 i = 0; i < 50; i++)
    {
        dash.y = i * 40 + 5;
        SDL_RenderFillRect(renderer, &dash);
    }
}

void render(void)
{
    SDL_SetRenderDrawColor(renderer, color_black.r, color_black.g, color_black.b, 255);
    SDL_RenderClear(renderer);

    render_game_text();
    render_dashes();
    render_paddles();
    render_ball();

    SDL_RenderPresent(renderer);
}

void initialize_game(void)
{
    score_player_left = 0;
    score_player_right = 0;
    has_game_text_changed = true;

    game_speed = STARTING_GAME_SPEED;

    srand(time(NULL));

    initialize_paddles();
    initialize_ball();
}

void increase_game_speed(Uint8 ammount)
{
    if (game_speed + ammount >= 7)
    {
        game_speed = 7;
        return;
    }

    game_speed += ammount;
}

void increase_score(bool left_player)
{
    if (left_player == true)
        score_player_left++;
    else
        score_player_right++;

    has_game_text_changed = true;
}

void restart_game(void)
{
    is_game_lost = false;

    paddles_cleanup();
    ball_cleanup();

    initialize_game();
}

void start_game_and_keep_running(void)
{
    Uint32 start_time = SDL_GetTicks();
    Uint32 end_time, elapsed_time;

menu:
    restart_game();
    while (is_window_open == true && is_in_menu == true)
    {
        SDL_SetRenderDrawColor(renderer, color_black.r, color_black.g, color_black.b, 255);
        SDL_RenderClear(renderer);

        end_time = SDL_GetTicks();
        elapsed_time = end_time - start_time;

        if (elapsed_time > 1500)
        {
            start_time = end_time;
            should_render_pong_text = true;
        }

        render_pong_text();
        render_menu_text();

        poll_events();
        SDL_RenderPresent(renderer);
    }

game:
    while (is_window_open == true && is_game_lost == false)
    {
        render();
        poll_events();

        if (is_in_menu == true)
            goto menu;

        if (is_paused == false)
        {
            move_ball();

            if (left_player_movement != 0)
                move_paddle(left_player, left_player_movement);

            if (right_player_movement != 0)
                move_paddle(right_player, right_player_movement);
        }
    }

    if (is_game_lost == true)
    {
        restart_game();
        goto game;
    }
}

void game_cleanup(void)
{
    text_cleanup(&score_player_left_text);
    text_cleanup(&score_player_right_text);
    text_cleanup(&paused_text);
    text_cleanup(&pong_text);
    text_cleanup(&made_by_text);
    text_cleanup(&press_enter_to_start_text);

    font_cleanup();
    sound_cleanup();

    paddles_cleanup();
    ball_cleanup();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}