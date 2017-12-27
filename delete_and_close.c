#include "delete_and_close.h"

/*frees and deletes all the pointers to renderers and textures*/
void delete_and_close()
{
  /*destroys and frees the main window*/
  SDL_DestroyWindow(main_window);
  main_window = NULL;

  /*destoys and frees main renderer*/
  SDL_DestroyRenderer(main_renderer);
  main_renderer = NULL;

  /*used to free the musiv=c files loaded*/
  Mix_FreeChunk(heli_crashed);
  heli_crashed = NULL;

  Mix_FreeMusic(heli_running);
  heli_running = NULL;

  /*freeing all the loaded textures*/
  free_my_texture(heli_texture);
  free_my_texture(background_texture);
  free_my_texture(sprite_sheet_1);
  free_my_texture(sprite_sheet_2);
  
  /*quitting all the graphic library dependencies*/
  SDL_Quit();
  IMG_Quit();
  TTF_Quit();
  Mix_Quit();
}
