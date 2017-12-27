#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "variables.h"
#include "constants.h"
#include "my_texture.h"
#include "my_timer.h"
#include "init.h"
#include "load_media.h"
#include "arena.h"
#include "heli.h"
#include "delete_and_close.h"

/*high score is used for stroing the scores along with a name*/
typedef struct _high_score_
{
  char str[20];
  int score;

}high_score;

/*function which handles the highscore management*/
void write_highscore(int value);

int main(int argc,char* argv[])
{
  /*all the variables to be used*/
  int score;
  SDL_Event e;
  SDL_Event up_event;
  SDL_Event temp_e;
  int quit = 0;
  int presser = 0;
  SDL_Rect* clip_1;
  SDL_Rect* clip_2;
  SDL_Rect wall_1,wall_2;
  int x_1 = 0,x_2 = SCREEN_WIDTH,xs_1 = SPRITE_DISTANCE,xs_2 = SPRITE_DISTANCE + SCREEN_WIDTH,ys_1 = SCREEN_HEIGHT/2,ys_2 = SCREEN_HEIGHT/2;
  /*time seeding*/
  srand(time(NULL));
  /*the two clips which oscillate giving the effect of an infinite background*/
  clip_1 = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  clip_2 = (SDL_Rect*)malloc(sizeof(SDL_Rect));
  clip_1->x = 0;
  clip_1->y = 0;
  clip_1->w = SCREEN_WIDTH;
  clip_1->h = SCREEN_HEIGHT;

  clip_2->x = SCREEN_WIDTH;
  clip_2->y = 0;
  clip_2->w = SCREEN_WIDTH;
  clip_2->h = SCREEN_HEIGHT;
  /*needed to initialize these above variables*//*done*/

  /*sprite rects*/
  wall_1.w = 30;
  wall_1.h = 90;
  wall_2.w = 30;
  wall_2.h = 90;

  if(init() == 0)
    {
      printf("Unable to initialize\n");
    }
  else
    {
      if(load_media() == 0)
	{
	  printf("Unable to load media\n");
	}
      else
	{
	  /*start playing the music of heli running*/
	  /*-1 says to keep the music in a continuous loop*/
	  Mix_PlayMusic(heli_running,-1);
	  start_my_timer(score_timer);
	  SDL_RenderClear(main_renderer);

	  /*infinite game loop and exits only on clicking x*/
	  while(quit != 1)
	    {
	      presser = 0;
	      /*Till Event queue becomes empty*/
	      while(SDL_PollEvent(&e) != 0)
		{
		  switch (e.type)
		    {
		    case SDL_QUIT:
		      quit = 1;
		      break;
		    case SDL_MOUSEBUTTONDOWN:
		      while( presser != 1)
			{
			  /*handle the heli event for Mouse Down*/
			  handle_heli_event(&e ,main_heli);
			  /*move the heli accordingly*/
			  move_heli(main_heli);
			  SDL_RenderClear(main_renderer);
			  /*constructs the arena*/
			  construct_arena(clip_1,clip_2,&x_1,&x_2,&ys_1,&ys_2,&xs_1,&xs_2);
			  /*collision rects*/
			  wall_1.x = xs_1;
			  wall_1.y = ys_1;
			  
			  wall_2.x = xs_2;
			  wall_2.y = ys_2;

			  heli_parts[0].y = (main_heli->heli_box)->y;
			  heli_parts[1].y = (main_heli->heli_box)->y;
			    
			  render_heli(heli_texture ,main_renderer ,main_heli);
			  /*display all the changes on screen*/
			  SDL_RenderPresent(main_renderer);
			  /*collision check*/
			  if( detect_collision(&wall_1,&wall_2) )
			    {
			      /*calculate score*/
			      score = get_ticks(score_timer)/100;
			      stop_my_timer(score_timer);
			      /*halts the running music*/
			      Mix_HaltMusic();
			      /*plays the blast sound without repeating*/
			      Mix_PlayChannel(-1,heli_crashed,0);
			      SDL_Delay(1000);
			      quit = 1;
			      break;
			    }
			  /*keep handling the event mouse down until encountering a mouse up*/
			  while(SDL_PollEvent(&temp_e) != 0)
			    {
			      switch(temp_e.type)
				{
				case SDL_MOUSEBUTTONUP:
				  /*indicates that mouse button is released*/
				  presser = 1;
				  up_event.type = SDL_MOUSEBUTTONUP;
				  move_heli(main_heli);
				  SDL_RenderClear(main_renderer);
				  construct_arena(clip_1,clip_2,&x_1,&x_2,&ys_1,&ys_2,&xs_1,&xs_2);
				  /*collision rects*/
				  wall_1.x = xs_1;
				  wall_1.y = ys_1;
				  
				  wall_2.x = xs_2;
				  wall_2.y = ys_2;
			
				  heli_parts[0].y = (main_heli->heli_box)->y;
				  heli_parts[1].y = (main_heli->heli_box)->y;
			   
				  render_heli(heli_texture ,main_renderer ,main_heli);
				  /*delay kept to scynchronize time taken in two different loops*/
				  SDL_Delay(10);
				  SDL_RenderPresent(main_renderer);
				  /*collision check*/
				  if( detect_collision(&wall_1,&wall_2) )
				    {
				      score = get_ticks(score_timer)/100;
				      stop_my_timer(score_timer);
				      /*halts the running music*/
				      Mix_HaltMusic();
				      /*plays the blast sound repeating it 0 times*/
				      Mix_PlayChannel(-1,heli_crashed,0);

				      SDL_Delay(1000);
				      quit = 1;
				      break;
				    }

				  
				  handle_heli_event(&temp_e ,main_heli);
				  break;
				case SDL_QUIT:
				  quit = 1;
				  break;
				default:
				  break;
				}
			      if(quit == 1)
				{
				  break;
				}
			    }
			}
		      break;
		    }
		  if(quit == 1)
		    {
		      break;
		    }
		}
	      if(quit == 1)
		{
		  break;
		}
	      /*handles heli events as mouse is released i.e free fall*/
	      handle_heli_event(&up_event,main_heli);
	      move_heli(main_heli);
	      SDL_RenderClear(main_renderer);
	      construct_arena(clip_1,clip_2,&x_1,&x_2,&ys_1,&ys_2,&xs_1,&xs_2);
	      /*collision rects*/
	      wall_1.x = xs_1;
	      wall_1.y = ys_1;
				  
	      wall_2.x = xs_2;
	      wall_2.y = ys_2;
				  
	      heli_parts[0].y = (main_heli->heli_box)->y;
	      heli_parts[1].y = (main_heli->heli_box)->y;
			   
	      render_heli(heli_texture ,main_renderer ,main_heli);
	      SDL_RenderPresent(main_renderer);
	      /*check collison*/
	      if( detect_collision(&wall_1,&wall_2) )
		{
		  score = get_ticks(score_timer)/100;
		  stop_my_timer(score_timer);
		  /*halts the running music*/
		  Mix_HaltMusic();
		  /*plays the blast sound repeating it 0 times*/
		  Mix_PlayChannel(-1,heli_crashed,0);

		  SDL_Delay(1000);
		  quit = 1;
		  break;
		}
	    }
	  /*delete and all SDL variables and exit SDL*/
	  delete_and_close();
	}
    }
  printf("Your Score is %d\n",score);
  /*writes high score to a bin file if it is among the top three*/
  write_highscore(score);
  return(0);
}

/*Highscore handler*/
void write_highscore(int value)
{
  int i,j,k,once = 0;
  high_score prev_scores[3];
  high_score temp;
  FILE* fr;
  FILE* fw;
  temp.score = value;
  fr = fopen("highscore.bin","rb");
  /*When the highscore file is opened for the first time i.e it needs to be created*/
  if(fr == NULL)
    {
      printf("Such file doesnt exist: So created it");
      fw = fopen("highscore.bin","wb");
      if(fw != NULL)
	{
	  printf("You have a highscore.\nPlease Enter your name\n");
	  fgets(temp.str,20,stdin);
	  
	  /*Write the high score into file*/
	  fwrite(&temp,sizeof(high_score),1,fw);
	}
    }
  else
    {
      for(i=0;i<3;i++)
	{
	  /*File already exists so copy all the information till EOF is encountered*/
	  if( fread(&prev_scores[i],sizeof(high_score),1,fr) == 0)
	    {
	      break;
	    }
	}
      /*close the read mode*/
      fclose(fr);
      /*open it to write*/
      fw = fopen("highscore.bin","wb");

      /*compares the present score with the values in order*/
      /*If a lesser value than present score is encountered then instead of that value present score is written*/
      /*'once' is used to take care that present score is written only once*/
      for(j=0,k=0;j<i;j++)
	{
	  if( (prev_scores[k].score < temp.score)&&(once == 0) )
	    {
	      printf("You have a highscore.\nPlease Enter your name\n");
	      fgets(temp.str,20,stdin);
	      
	      /*once variable is used since temp score should be written only once*/
	      once = 1;
	      fwrite(&temp,sizeof(high_score),1,fw);
	    }
	  else
	    {
	      fwrite(&prev_scores[k],sizeof(high_score),1,fw);
	      k++;
	    }
	}
      /*If the values in File are lessthan 3 another value needs to be wriiten*/
      /*if present score is already written then write the remaining leftout values*/
      /*else the present score is written*/
      if( i!=3 )
	{
	  if(once == 0)
	    {
	      printf("You have a highscore.\nPlease Enter your name\n");
	      fgets(temp.str,20,stdin);
	      
	      fwrite(&temp,sizeof(high_score),1,fw);
	    }
	  else
	    {
	      fwrite(&prev_scores[k],sizeof(high_score),1,fw);
	    }
	}
    }
  /*flushing and closing the file*/
  fflush(fw);
  fclose(fw);

  /*printing the new high scores in terminal*/
  fr = fopen("highscore.bin","rb");
  i = 1;
  printf("High Scores\n");
  while( fread(&temp,sizeof(high_score),1,fr) != 0 )
    {
      printf("%d:%s   %d\n",i,temp.str,temp.score);
      i++;
    }
}
