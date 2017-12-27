#include "heli.h"

/*Take an uninitialized heli and initialize it*/
heli* init_heli(heli* new_heli)
{
  new_heli = (heli*)malloc(sizeof(heli));
	new_heli->heli_box = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  (new_heli->heli_box)->w = HELI_WIDTH;
  (new_heli->heli_box)->h = HELI_HEIGHT;
  (new_heli->heli_box)->x = HELI_X_POS;
  (new_heli->heli_box)->y = HELI_Y_POS;
  new_heli->y_vel = 0;
  return(new_heli);
}

/*take key presses and adjust the velocity of heli*/
/*comes into this loop only when mouse button is up or down*/
/*heli's velocity constantly increases until it reaches a maximum value in the same way as acceleration*/
/*the acceleration is a frame dependant acceleration i.e. it has an acceleration per frame instead of per time*/
heli* handle_heli_event(SDL_Event* e,heli* new_heli)
{
  switch(e->type)
    {
    case SDL_MOUSEBUTTONDOWN:
      /*increases the velocity of heli just like acceleration*/
      if(new_heli->y_vel < MAX_UPWARD_VELOCITY)
	{
	  new_heli->y_vel += HELI_VELOCITY_UP;
	}
      break;
    case SDL_MOUSEBUTTONUP:
      /*once mouse key relesed heli falls downwards and deceleration starts*/
      if(new_heli->y_vel > MAX_DOWNWARD_VELOCITY)
	{
	  new_heli->y_vel += HELI_VELOCITY_DOWN;
	}
      break;
    }
  return(new_heli);
}

/*moves the helicopter*/
heli* move_heli(heli* new_heli)
{
  (new_heli->heli_box)->y -= new_heli->y_vel;
  return(new_heli);
}

/*renders the helicopter*/
void render_heli(my_texture* new_texture,SDL_Renderer* renderer,heli* new_heli)
{
  render_my_texture(new_texture, renderer, (new_heli->heli_box)->x,  (new_heli->heli_box)->y,NULL ,0.0 ,NULL ,SDL_FLIP_NONE);
}




