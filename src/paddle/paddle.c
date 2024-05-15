#include "paddle.h"

struct paddle *left_player = NULL;
struct paddle *right_player = NULL;

void initialize_paddles(void)
{
    left_player = (struct paddle *)malloc(sizeof(struct paddle));
    right_player = (struct paddle *)malloc(sizeof(struct paddle));

    left_player->position_y = WINDOW_HEIGHT / 2;
    right_player->position_y = WINDOW_HEIGHT / 2;
}

void render_paddles(void)
{
    SDL_SetRenderDrawColor(renderer, color_white.r, color_white.g, color_white.b, 255);

    SDL_Rect left_player_rect;

    left_player_rect.x = 50;
    left_player_rect.y = left_player->position_y - PADDLE_HEIGHT / 2;

    left_player_rect.w = PADDLE_WIDTH;
    left_player_rect.h = PADDLE_HEIGHT;

    SDL_RenderFillRect(renderer, &left_player_rect);

    SDL_Rect right_player_rect;

    right_player_rect.x = WINDOW_WIDTH - 50 - PADDLE_WIDTH;
    right_player_rect.y = right_player->position_y - PADDLE_HEIGHT / 2;

    right_player_rect.w = PADDLE_WIDTH;
    right_player_rect.h = PADDLE_HEIGHT;

    SDL_RenderFillRect(renderer, &right_player_rect);
}

void move_paddle(struct paddle *paddle, Sint8 offset_y)
{
    if (paddle->position_y + offset_y <= PADDLE_HEIGHT / 2 || paddle->position_y + offset_y >= WINDOW_HEIGHT - PADDLE_HEIGHT / 2)
        return;

    paddle->position_y += offset_y;
}

void paddles_cleanup(void)
{
    free(left_player);
    left_player = NULL;

    free(right_player);
    right_player = NULL;
}