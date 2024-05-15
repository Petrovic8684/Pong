#ifndef MATH_H
#define MATH_H

#include <stdint.h>
#include <SDL2/SDL.h>

struct vector2
{
    float x;
    float y;
};

int SDL_RenderFillCircle(SDL_Renderer *renderer, int x, int y, int radius);

#endif