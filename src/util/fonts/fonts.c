#include "fonts.h"

TTF_Font *font = NULL;

struct text score_player_left_text;
struct text score_player_right_text;

struct text paused_text;

struct text pong_text;
struct text made_by_text;
struct text press_enter_to_start_text;

bool has_game_text_changed = true;
bool should_render_pong_text = true;

void initialize_text(void)
{
    if (TTF_Init() == -1)
    {
        fprintf(stderr, "SDL_ttf failed to initialize: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    font = TTF_OpenFont("assets/fonts/runescape.ttf", 36);
}

void update_text(const char *prefix, bool has_variable, const int variable, SDL_Color color, int x, int y, bool add_padding, struct text *text)
{
    if (has_variable == true)
    {
        char string[20];
        string[0] = '\0';
        if (add_padding == true)
            sprintf(string, "%s %04d", prefix, variable);
        else
            sprintf(string, "%s %d", prefix, variable);

        text->text_surface = TTF_RenderText_Solid(font, string, color);
    }
    else
    {
        text->text_surface = TTF_RenderText_Solid(font, prefix, color);
    }

    text->text_texture = SDL_CreateTextureFromSurface(renderer, text->text_surface);

    text->text_rect.x = x;
    text->text_rect.y = y;
    text->text_rect.w = text->text_surface->w;
    text->text_rect.h = text->text_surface->h;
}

void render_game_text(void)
{
    if (has_game_text_changed == true)
    {
        int position_x;

        if (is_paused == true)
        {
            TTF_SizeText(font, "PAUSED", &position_x, NULL);
            update_text("PAUSED", false, -1, color_gray, (WINDOW_WIDTH - position_x) / 2, 100, false, &paused_text);
        }
        else
            update_text(" ", false, -1, color_gray, (WINDOW_WIDTH - position_x) / 2, 100, false, &paused_text);

        TTF_SizeText(font, "10", &position_x, NULL);

        update_text("", true, score_player_left, color_gray, (WINDOW_WIDTH - position_x) / 2 - 75, 50, false, &score_player_left_text);
        update_text("", true, score_player_right, color_gray, (WINDOW_WIDTH - position_x) / 2 + 75, 50, false, &score_player_right_text);

        has_game_text_changed = false;
    }

    SDL_RenderCopy(renderer, score_player_left_text.text_texture, NULL, &score_player_left_text.text_rect);
    SDL_RenderCopy(renderer, score_player_right_text.text_texture, NULL, &score_player_right_text.text_rect);
    SDL_RenderCopy(renderer, paused_text.text_texture, NULL, &paused_text.text_rect);
}

void render_pong_text(void)
{
    if (should_render_pong_text == true)
    {
        TTF_SetFontSize(font, 70);

        int position_x;
        TTF_SizeText(font, "P  O  N  G", &position_x, NULL);

        update_text("P  O  N  G", false, -1, get_random_color(), (WINDOW_WIDTH - position_x) / 2, WINDOW_HEIGHT / 4 + 30, false, &pong_text);

        should_render_pong_text = false;
    }
}

void render_menu_text(void)
{
    TTF_SetFontSize(font, 36);

    int position_x;
    TTF_SizeText(font, "Made by Jovan Petrovic", &position_x, NULL);
    update_text("Made by Jovan Petrovic", false, -1, color_white, (WINDOW_WIDTH - position_x) / 2, WINDOW_HEIGHT / 3 + 75, false, &made_by_text);

    TTF_SizeText(font, "Press ENTER to start", &position_x, NULL);
    update_text("Press ENTER to start", false, -1, color_white, (WINDOW_WIDTH - position_x) / 2, WINDOW_HEIGHT / 3 + 125, false, &press_enter_to_start_text);

    SDL_RenderCopy(renderer, pong_text.text_texture, NULL, &pong_text.text_rect);
    SDL_RenderCopy(renderer, made_by_text.text_texture, NULL, &made_by_text.text_rect);
    SDL_RenderCopy(renderer, press_enter_to_start_text.text_texture, NULL, &press_enter_to_start_text.text_rect);
};

void text_cleanup(struct text *text)
{
    SDL_FreeSurface(text->text_surface);
    SDL_DestroyTexture(text->text_texture);

    text->text_surface = NULL;
    text->text_texture = NULL;
}

void font_cleanup(void)
{
    TTF_CloseFont(font);
    font = NULL;

    TTF_Quit();
}