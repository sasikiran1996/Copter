#include "variables.h"

/*All the variables to be used Globally in all files of game*/
/*Will be declared only once when this .c is executed and thus can avoid multiple declarations*/

SDL_Window* main_window;
SDL_Renderer* main_renderer;
my_texture* heli_texture;
my_texture* background_texture;
my_texture* sprite_sheet_1;
my_texture* sprite_sheet_2;
SDL_Rect* sprite_clip;
heli* main_heli;
SDL_Rect* background_collision_sprite;
SDL_Rect* heli_parts;
my_timer* score_timer;
Mix_Music* heli_running;
Mix_Chunk* heli_crashed;

