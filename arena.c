#include "arena.h"

int rand_lim(int limit);

/*x_1 and x_2 vary to give it an infinite effect*/
void construct_arena(SDL_Rect* clip_1,SDL_Rect* clip_2,int* x_1,int* x_2,int* ys_1,int* ys_2,int* xs_1,int* xs_2)
{
  int i;
  /*x_1 and x_2 should be initialized in main
   x_1 == 0
   x_2 == SCREEN_WIDTH*/
  *x_1 = *x_1 - MOVEMENT_PER_FRAME;
  *x_2 = *x_2 - MOVEMENT_PER_FRAME;
  /*if x_1 goes too much out of bounds*/
  if(*x_2 == 0)
    {
      *x_1 = SCREEN_WIDTH;
    }
  /*if x_2 goes too much out of bounds*/
  if(*x_1 == 0)
    {
      *x_2 = SCREEN_WIDTH;
    }
  render_my_texture(background_texture ,main_renderer ,*x_1 ,0 ,clip_1 ,0.0 ,NULL ,SDL_FLIP_NONE);
  render_my_texture(background_texture ,main_renderer ,*x_2 ,0 ,clip_2 ,0.0 ,NULL ,SDL_FLIP_NONE);

  /*xs_2 and xs_1 should be separated by screen width*/
  *xs_1 = *xs_1 - MOVEMENT_PER_FRAME;
  *xs_2 = *xs_2 - MOVEMENT_PER_FRAME;
  /*generating y-pos of sprites randomly*/
  if(*xs_2 == 0)
    {
      *xs_1 = SCREEN_WIDTH;
      *ys_1 = rand_lim(300) + 100;
    }
  if(*xs_1 == 0)
    {
      *xs_2 = SCREEN_WIDTH;
      *ys_2 = rand_lim(300) + 100;
    }

  /*changes made to background_collision_sprite array based on position of screen*/
  for(i=0;i<20;i++)
    {
      background_collision_sprite[i].x -= MOVEMENT_PER_FRAME;
    }
  /*when a part of screen goes too much out of bounds*/
  if(background_collision_sprite[0].x == 0 - SCREEN_WIDTH)
    {
      for(i=0;i<=10;i++)
	{
	  background_collision_sprite[i].x += 2*SCREEN_WIDTH;
	}
    }
  if(background_collision_sprite[11].x == 0 - SCREEN_WIDTH)
    {
      for(i=11;i<=19;i++)
	{
	  background_collision_sprite[i].x += 2*SCREEN_WIDTH;
	}
    }
  
  /*rendering sprite sheets at random ys generated*/
  render_my_texture(sprite_sheet_1 ,main_renderer ,*xs_1 ,*ys_1 ,sprite_clip ,0.0 ,NULL ,SDL_FLIP_NONE);
  render_my_texture(sprite_sheet_2 ,main_renderer ,*xs_2 ,*ys_2 ,sprite_clip ,0.0 ,NULL ,SDL_FLIP_NONE);
  
}

/*used to detect whether a collision happened*/
/*collision is detected by eliminating all non colliding cases*/
/*For a collision to take place (Bounded Box Collision) There are two boxes declared for each of the two colliding objects*/
/*A collision occurs only when the projections in x and y axes of both the boxes intersect*/
bool detect_collision(SDL_Rect* wall_1,SDL_Rect* wall_2)
{
  int i;
  bool success = 0;
  /*collision with wall 1*/
  if(wall_1->x > ((heli_parts[1].x) + (heli_parts[1].w)) )
    {
      /*no collision*/
      success = 0;
    }
 
  else
    {
      if( ((wall_1->x) + (wall_1->w)) < heli_parts[0].x)
	{
	  /*no collission*/
	  success = 0;
	}
      else
	{
	  if( ((wall_1->y) + (wall_1->h)) < heli_parts[0].y)
	    {
	      /*no collision*/
	      success = 0;
	    }	  	  
	  else
	    {
	      if( (wall_1->x) + (wall_1->w) < heli_parts[1].x)
		{ 
		  if( (wall_1->y) > (heli_parts[0].y + heli_parts[0].h) )
		    {
		      /*no collision*/
		      success = 0;
		    }
		  else
		    {
		      success = 1;
		      return(success);
		    }
		}
	      else
		{
		  if( (wall_1->y) > (heli_parts[1].y + heli_parts[1].h) )
		    {
		      /*no collision*/
		      success = 0;
		    }
		  else
		    {
		      success = 1;
		      return(success);
		    }
		} 
	    }
	}
    }
 
  /*collision detection with wall 2*/
  if(wall_2->x > ((heli_parts[1].x) + (heli_parts[1].w)) )
    {
      /*no collision*/
      success = 0;
    }
 
  else
    {
      if( ((wall_2->x) + (wall_2->w)) < heli_parts[0].x)
	{
	  /*no collission*/
	  success = 0;
	}
      else
	{
	  if( ((wall_2->y) + (wall_2->h)) < heli_parts[0].y)
	    {
	      /*no collision*/
	      success = 0;
	    }	  	  
	  else
	    {
	      if( (wall_2->x) + (wall_2->w) < heli_parts[1].x)
		{ 
		  if( (wall_2->y) > (heli_parts[0].y + heli_parts[0].h) )
		    {
		      /*no collision*/
		      success = 0;
		    }
		  else
		    {
		      success = 1;
		      return(success);
		    }
		}
	      else
		{
		  if( (wall_2->y) > (heli_parts[1].y + heli_parts[1].h) )
		    {
		      /*no collision*/
		      success = 0;
		    }
		  else
		    {
		      success = 1;
		      return(success);
		    }
		} 
	    }
	}
    }
  
  /*collision detection with background*/
  /*background is divided approximately into boxes of appropriate dimensions which can be used for detecting collision*/
  for(i=0;i<19;i++)
    {
      if(background_collision_sprite[i].x > ((heli_parts[1].x) + (heli_parts[1].w)) )
	{
	  /*no collision*/
	  success = 0;
	}
 
      else
	{
	  if( ((background_collision_sprite[i].x) + (background_collision_sprite[i].w)) < heli_parts[0].x)
	    {
	      /*no collission*/
	      success = 0;
	    }
	  else
	    {
	      if( ((background_collision_sprite[i].y) + (background_collision_sprite[i].h)) < heli_parts[0].y)
		{
		  /*no collision*/
		  success = 0;
		}	  	  
	      else
		{
		  if( (background_collision_sprite[i].x) + (background_collision_sprite[i].w) < heli_parts[1].x)
		    { 
		      if( (background_collision_sprite[i].y) > (heli_parts[0].y + heli_parts[0].h) )
			{
			  /*no collision*/
			  success = 0;
			}
		      else
			{
			  success = 1;
			  return(success);
			}
		    }
		  else
		    {
		      if( (background_collision_sprite[i].y) > (heli_parts[1].y + heli_parts[1].h) )
			{
			  /*no collision*/
			  success = 0;
			}
		      else
			{
			  success = 1;
			  return(success);
			}
		    } 
		}
	    }
	}
    }
  /*if the copter tries to go out of bounds of screen*/
  if( (main_heli->heli_box)->y < 0 )
    {
      success = 1;
    }
  return(success);
}

/*random number generation*/
int rand_lim(int limit) {
/* return a random number between 0 and limit inclusive.
 */

    int divisor = RAND_MAX/(limit+1);
    int retval;

    do { 
        retval = rand() / divisor;
    } while (retval > limit);

    return retval;
}
