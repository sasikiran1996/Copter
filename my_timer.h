#ifndef MY_TIMER_H_INCLUDED
#define MY_TIMER_H_INCLUDED

/*Library for timer*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _my_timer_
{
  /*time when clock started*/
  Uint32 start_ticks;
  /*time elapsed when clock has been paused*/
  Uint32 paused_ticks;

  /*timer status*/
  bool paused;
  bool started;
  
}my_timer;

/*initialize the timer*/
my_timer* init_my_timer(my_timer* new_timer);

/*various clock actions*/
my_timer* start_my_timer(my_timer* new_timer);

my_timer* stop_my_timer(my_timer* new_timer);

my_timer* pause_my_timer(my_timer* new_timer);

my_timer* unpause_my_timer(my_timer* new_timer);

/*Get the timer's time*/
Uint32 get_ticks(my_timer* new_timer);

#endif /*MY_TIMER_H_INCLUDED*/
