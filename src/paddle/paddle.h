#ifndef PADDLE_H
#define PADDLE_H

#include "../game/game.h"

#define PADDLE_HEIGHT 80
#define PADDLE_WIDTH 10

struct paddle
{
    int position_y;
};

extern struct paddle *left_player;
extern struct paddle *right_player;

void initialize_paddles(void);
void render_paddles(void);
void move_paddle(struct paddle *paddle, Sint8 offset_y);
void paddles_cleanup(void);

#endif