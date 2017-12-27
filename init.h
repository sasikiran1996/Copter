#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

/*used to initialize all the variables being used and 
for initializing all the SDL*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>
#include "variables.h"
#include "constants.h"
#include "my_texture.h"
#include "my_timer.h"

bool init();

#endif /*INIT_H_INCLUDED*/
