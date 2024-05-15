#include "ball.h"

struct ball *ball = NULL;

void initialize_ball(void)
{
    ball = (struct ball *)malloc(sizeof(struct ball));

    ball->position.x = WINDOW_WIDTH / 2;
    ball->position.y = WINDOW_HEIGHT / 2;

    switch (rand() % 4)
    {
    case 0:
        ball->velocity.x = 1;
        ball->velocity.y = 1;
        break;
    case 1:
        ball->velocity.x = -1;
        ball->velocity.y = -1;
        break;
    case 2:
        ball->velocity.x = -1;
        ball->velocity.y = 1;
        break;
    case 3:
        ball->velocity.x = 1;
        ball->velocity.y = -1;
        break;
    }
}

void render_ball(void)
{
    SDL_SetRenderDrawColor(renderer, color_white.r, color_white.g, color_white.b, 255);
    SDL_RenderFillCircle(renderer, ball->position.x, ball->position.y, BALL_RADIUS);
}

void move_ball(void)
{
    ball->position.x += ball->velocity.x * game_speed;
    ball->position.y += ball->velocity.y * game_speed;

    if (ball->position.y <= BALL_RADIUS / 2 || ball->position.y >= WINDOW_HEIGHT - BALL_RADIUS / 2)
        ball->velocity.y = -ball->velocity.y;

    if (ball->position.x < -100) // Right player scores.
    {
        score_player_right++;
        has_game_text_changed = true;

        increase_game_speed(0.3);
        play_score_sound();

        ball_cleanup();
        initialize_ball();
    }

    if (ball->position.x > WINDOW_WIDTH + 100) // Left player scores.
    {
        score_player_left++;
        has_game_text_changed = true;

        increase_game_speed(0.3);
        play_score_sound();

        ball_cleanup();
        initialize_ball();
    }

    if ((ball->position.x - BALL_RADIUS <= 50 + PADDLE_WIDTH / 2) && (ball->position.x - BALL_RADIUS >= 53) && (ball->position.y >= left_player->position_y - PADDLE_HEIGHT / 2) && (ball->position.y <= left_player->position_y + PADDLE_HEIGHT / 2)) // Collision with left player.
    {
        ball->velocity.x = -ball->velocity.x;
        increase_game_speed(0.1);
        play_bounce_sound();
    }

    if ((ball->position.x + BALL_RADIUS >= WINDOW_WIDTH - 50 - PADDLE_WIDTH / 2) && (ball->position.x + BALL_RADIUS <= WINDOW_WIDTH - 53) && (ball->position.y >= right_player->position_y - PADDLE_HEIGHT / 2) && (ball->position.y <= right_player->position_y + PADDLE_HEIGHT / 2)) // Collision with right player.
    {
        ball->velocity.x = -ball->velocity.x;
        increase_game_speed(0.1);
        play_bounce_sound();
    }
}

void ball_cleanup(void)
{
    free(ball);
    ball = NULL;
}