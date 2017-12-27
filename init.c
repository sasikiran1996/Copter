
#include "init.h"

/*Initializes all components and variables*/
bool init()
{
  bool success = 1;
  /*Initializes SDL*/
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
      success = 0;
      printf("Unable to initialize SDL error:%s\n",SDL_GetError());
    }
  else
    {
      /*initialize all variables concerning SDL*/
      heli_running = NULL;
      heli_crashed = NULL;
      
      main_window = NULL;
      main_renderer = NULL;
      
      heli_texture = initialize_my_texture();
      background_texture = initialize_my_texture();
      
      sprite_sheet_1 = initialize_my_texture();
      sprite_sheet_2 = initialize_my_texture();
      
      main_heli = init_heli(main_heli);
      score_timer = init_my_timer(score_timer);     

      /*heli parts are used for collision of background with arena*/
      /*heli is divided into its head and tail parts for Bounded Box Collision*/
      heli_parts = (SDL_Rect*)malloc(2*sizeof(SDL_Rect));
      heli_parts[0].x = (main_heli->heli_box)->x;
      heli_parts[0].y = (main_heli->heli_box)->y;
      heli_parts[0].w = 65;
      heli_parts[0].h = 35;

      heli_parts[1].x = (main_heli->heli_box)->x + 65;
      heli_parts[1].y = (main_heli->heli_box)->y;
      heli_parts[1].w = 79;
      heli_parts[1].h = 53;

      /*the obstacle wall's sprite clip*/
      sprite_clip = (SDL_Rect*)malloc(sizeof(SDL_Rect));
      sprite_clip->x = 0;
      sprite_clip->y = 0;
      sprite_clip->w = 30;
      sprite_clip->h = 90;

      /*background divided approximately into rectangles for collision detection*/
      background_collision_sprite = (SDL_Rect*)malloc(20*sizeof(SDL_Rect));

      background_collision_sprite[0].x = 0;
      background_collision_sprite[0].y = 578;
      background_collision_sprite[0].w = 30;
      background_collision_sprite[0].h = 190;


      background_collision_sprite[1].x = 30;
      background_collision_sprite[1].y = 538;
      background_collision_sprite[1].w = 90;
      background_collision_sprite[1].h = 230;


      background_collision_sprite[2].x = 120;
      background_collision_sprite[2].y = 464;
      background_collision_sprite[2].w = 160;
      background_collision_sprite[2].h = 304;

      
      background_collision_sprite[3].x = 290;
      background_collision_sprite[3].y = 590;
      background_collision_sprite[3].w = 110;
      background_collision_sprite[3].h = 178;


      background_collision_sprite[4].x = 400;
      background_collision_sprite[4].y = 638;
      background_collision_sprite[4].w = 130;
      background_collision_sprite[4].h = 130;


      background_collision_sprite[5].x = 530;
      background_collision_sprite[5].y = 494;
      background_collision_sprite[5].w = 85;
      background_collision_sprite[5].h = 174;

      
      background_collision_sprite[6].x = 615;
      background_collision_sprite[6].y = 604;
      background_collision_sprite[6].w = 30;
      background_collision_sprite[6].h = 164;


      background_collision_sprite[7].x = 645;
      background_collision_sprite[7].y = 624;
      background_collision_sprite[7].w = 173;
      background_collision_sprite[7].h = 144;


      background_collision_sprite[8].x = 818;
      background_collision_sprite[8].y = 574;
      background_collision_sprite[8].w = 120;
      background_collision_sprite[8].h = 194;


      background_collision_sprite[9].x = 938;
      background_collision_sprite[9].y = 624;
      background_collision_sprite[9].w = 90;
      background_collision_sprite[9].h = 144;


      background_collision_sprite[10].x = 1028;
      background_collision_sprite[10].y = 584;
      background_collision_sprite[10].w = 115;
      background_collision_sprite[10].h = 144;


      /*next part of the screen*/
      background_collision_sprite[11].x = 1143;
      background_collision_sprite[11].y = 634;
      background_collision_sprite[11].w = 30;
      background_collision_sprite[11].h = 134;

      
      background_collision_sprite[12].x = 1173;
      background_collision_sprite[12].y = 534;
      background_collision_sprite[12].w = 90;
      background_collision_sprite[12].h = 234;

      
      background_collision_sprite[13].x = 1263;
      background_collision_sprite[13].y = 634;
      background_collision_sprite[13].w = 200;
      background_collision_sprite[13].h = 134;

      
      background_collision_sprite[14].x = 1463;
      background_collision_sprite[14].y = 594;
      background_collision_sprite[14].w = 190;
      background_collision_sprite[14].h = 174;

      
      background_collision_sprite[15].x = 1653;
      background_collision_sprite[15].y = 534;
      background_collision_sprite[15].w = 20;
      background_collision_sprite[15].h = 234;


      background_collision_sprite[16].x = 1673;
      background_collision_sprite[16].y = 484;
      background_collision_sprite[16].w = 80;
      background_collision_sprite[16].h = 284;

      
      background_collision_sprite[17].x = 1753;
      background_collision_sprite[17].y = 634;
      background_collision_sprite[17].w = 170;
      background_collision_sprite[17].h = 134;

      
      background_collision_sprite[18].x = 1923;
      background_collision_sprite[18].y = 474;
      background_collision_sprite[18].w = 240;
      background_collision_sprite[18].h = 294;

     
      background_collision_sprite[19].x = 2173;
      background_collision_sprite[19].y = 548;
      background_collision_sprite[19].w = 113;
      background_collision_sprite[19].h = 220;

      
      /*end of initialization of variables*/
      /*Creates a SDL window*/
      main_window = SDL_CreateWindow("Copter_Game",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
      if(main_window == NULL)
	{
	  success = 0;
	  printf("Unable to create window sdl error:%s\n",SDL_GetError());
	}
      else
	{
	  /*Initializes IMG*/
	  if( !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) )
	    {
	      success = 0;
	      printf("Unable to initialize SDL image error:%s\n",IMG_GetError());
	    }
	  /*Initialize SDL_Mixer*/
	  if( Mix_OpenAudio( 44100,MIX_DEFAULT_FORMAT,2,2048) < 0)
	    {
	      success = 0;
	      printf("SDL_Mixer could not initialize error:%s\n",Mix_GetError());
	    }
	  else
	    {
	      /*Initializes TTF*/
	      if(TTF_Init() == -1)
		{
		  success = 0;
		  printf("Unable to initialize ttf error:%s\n",TTF_GetError());
		}
	      else
		{
		  /*Creates a renderer*/
		  main_renderer = SDL_CreateRenderer( main_window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
		  if(main_renderer == NULL)
		    {
		      success = 0;
		      printf("Unable to create renderer error:%s\n",SDL_GetError());
		    }
		  else
		    {
		      /*Set renderer's drawing color to white*/
		      SDL_SetRenderDrawColor(main_renderer,0xFF,0xFF,0xFF,0xFF);
		    }
		}
	    }
	}
    }
  return(success);
}
