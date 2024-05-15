#ifndef BALL_H
#define BALL_H

#include "../game/game.h"
#include "../util/math/math.h"

#define BALL_RADIUS 6

struct ball
{
    struct vector2 position;
    struct vector2 velocity;
};

extern struct ball *ball;

void initialize_ball(void);
void render_ball(void);
void move_ball(void);
void ball_cleanup(void); // LOL

#endif