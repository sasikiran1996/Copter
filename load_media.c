#include "load_media.h"

bool load_media()
{
  bool success = 1;
  Uint32 color_key_pixel;
  Uint8 red;
  Uint8 green;
  Uint8 blue;
  SDL_Surface* temp_surface_heli = NULL;
  SDL_Surface* temp_surface_background = NULL;
  SDL_Surface* temp_surface_sprite = NULL;
  /*Loading music*/
  heli_running = Mix_LoadMUS("sounds/heli_running.wav");
  if(heli_running == NULL)
    {
      success = 0;
      printf("Unable to load heli_running.wav error:%s\n",Mix_GetError());
    }
  /*loading sound effect*/
  heli_crashed = Mix_LoadWAV("sounds/boom.wav");
  if(heli_crashed == NULL)
    {
      success = 0;
      printf("Unable to load boom.wav error:%s\n",Mix_GetError());
    }

  /*Loading heli image*/
  temp_surface_heli = IMG_Load("images/heli.png");
  if (temp_surface_heli == NULL)
    {
      success = 0;
      printf("error loading images/heli.png :%s\n",IMG_GetError());
    }
  else
    {
      /*finding color key for background of heli.png*/
      color_key_pixel = SDL_MapRGB(temp_surface_heli->format ,73 ,203 ,58);
      SDL_GetRGB(color_key_pixel ,temp_surface_heli->format ,&red ,&green ,&blue);
      /*free the temp_surface of heli*/
      SDL_FreeSurface(temp_surface_heli);
      temp_surface_heli = NULL;
      /*creating heli texture*/
      if( load_image(heli_texture ,main_renderer ,"images/heli.png" ,red ,green ,blue) == 0)
	{
	  success = 0;
	  printf("Error in loading image as heli_texture\n");
	}
      else
	{
	  temp_surface_background = IMG_Load("images/ground.png");
	  if(temp_surface_background == NULL)
	    {
	      success = 0;
	      printf("error loading images/ground.png :%s\n",IMG_GetError());
	    }
	  else
	    {
	      /*finding color key for background of ground.png*/
	      color_key_pixel = SDL_MapRGB(temp_surface_background->format ,0 ,0 ,128);
	      SDL_GetRGB(color_key_pixel ,temp_surface_background->format ,&red ,&green ,&blue);
	      
	      /*free the temp surface of background*/
	      SDL_FreeSurface(temp_surface_background);
	      temp_surface_background = NULL;
	      /*creating background texture*/
	      if( load_image(background_texture ,main_renderer ,"images/ground.png" ,red ,green ,blue) == 0)
		{
		  success = 0;
		  printf("Unable to load image as background_texture\n");
		}
	      else
		{
		  /*load hitwalls image*/
		  temp_surface_sprite = SDL_LoadBMP("images/hitwalls.bmp");
		  if(temp_surface_sprite == NULL)
		    {
		      success = 0;
		      printf("Unable to load images/hitwalls.bmp :%s\n",SDL_GetError());
		    }
		  else
		    {
		      /*create two textures from same image*/
		      sprite_sheet_1->texture = SDL_CreateTextureFromSurface(main_renderer,temp_surface_sprite);
		      sprite_sheet_2->texture = SDL_CreateTextureFromSurface(main_renderer,temp_surface_sprite);
		      if( (sprite_sheet_1->texture == NULL)||(sprite_sheet_2->texture == NULL) )
			{
			  printf("Unable to render error:%s\n",SDL_GetError());
			}
		      else
			{
			  sprite_sheet_1->texture_width = temp_surface_sprite->w;
			  sprite_sheet_1->texture_height = temp_surface_sprite->h;
			  sprite_sheet_2->texture_width = temp_surface_sprite->w;
			  sprite_sheet_2->texture_height = temp_surface_sprite->h;
			}
		      /*free the temporary surface*/
		      SDL_FreeSurface(temp_surface_sprite);
		      temp_surface_sprite = NULL;
		    }
		}
	    }
	}
    }
  return(success);
}
