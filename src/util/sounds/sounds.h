#ifndef SOUNDS_H
#define SOUNDS_H

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_mixer.h>

extern Mix_Music *music_sound;
extern Mix_Chunk *bounce_sound;
extern Mix_Chunk *score_sound;

void initialize_sound(void);
void load_sounds(void);
void play_music(void);
void play_bounce_sound(void);
void play_score_sound(void);
void sound_cleanup(void);

#endif