#include "my_timer.h"

/*initialize the timer*/
my_timer* init_my_timer(my_timer* new_timer)
{
  new_timer = (my_timer*)malloc(sizeof(my_timer));
  new_timer->start_ticks = 0;
  new_timer->paused_ticks = 0;
  new_timer->paused = 0;
  new_timer->started = 0;
	return(new_timer);
}

/*various clock actions*/
/*can also be used to restart timer*/
my_timer* start_my_timer(my_timer* new_timer)
{
  new_timer->started = 1;
  new_timer->paused = 0;
  new_timer->start_ticks = SDL_GetTicks();
  new_timer->paused_ticks = 0;
	return(new_timer);
}

/*it reinitializes all variables*/
my_timer* stop_my_timer(my_timer* new_timer)
{
  new_timer->started = 0;
  new_timer->paused = 0;
  new_timer->start_ticks = 0;
  new_timer->paused_ticks = 0;
	return(new_timer);
}

/*pauses the timer*/
my_timer* pause_my_timer(my_timer* new_timer)
{
  if( (new_timer->started)&& !(new_timer->paused) )
    {
      new_timer->paused = 1;
      /*calculate paused ticks*/
      new_timer->paused_ticks = SDL_GetTicks() - new_timer->start_ticks;
      new_timer->start_ticks = 0;
    }
	return(new_timer);
}

/*unpauses the timer*/
my_timer* unpause_my_timer(my_timer* new_timer)
{
  if( (new_timer->started)&&(new_timer->paused) )
    {
      new_timer->paused = 0;
      /*shifting start ticks by amount of time passed already while clock was running*/
      new_timer->start_ticks = SDL_GetTicks() - new_timer->paused_ticks;
      new_timer->paused_ticks = 0;
    }
	return(new_timer);
}

/*Get the timer's time*/
Uint32 get_ticks(my_timer* new_timer)
{
  Uint32 time_elapsed = 0;
  if(new_timer->started)
    {
      if(new_timer->paused)
	{
	  time_elapsed = new_timer->paused_ticks;
	}
      else
	{
	  time_elapsed = SDL_GetTicks() - new_timer->start_ticks;
	}
    }
  return(time_elapsed);
}






