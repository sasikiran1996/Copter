#ifndef HELI_H_INCLUDED
#define HELI_H_INCLUDED

/*This is used to handle all the evets related to helicopter*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "my_texture.h"
#include "constants.h"
#include <stdlib.h>

/*heli structure contains position of heli as rect and its y_vel*/
typedef struct _heli_
{
  SDL_Rect* heli_box;
  int y_vel;

}heli;

/*Take an uninitialized heli and initialize it*/
heli* init_heli(heli* new_heli);

/*take key presses and adjust the velocity of heli*/
heli* handle_heli_event(SDL_Event* e,heli* new_heli);

/*moves the helicopter*/
heli* move_heli(heli* new_heli);

/*renders the helicopter*/
void render_heli(my_texture* new_texture,SDL_Renderer* renderer,heli* new_heli);

#endif /*HELI_H_INCLUDED*/
