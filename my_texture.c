#include "my_texture.h"
#include <stdlib.h>

/*initializes the structure my_texture*/
my_texture* initialize_my_texture()
{
  my_texture* new_texture;
  new_texture = (my_texture*)malloc(sizeof(my_texture));
  new_texture->texture = NULL;
  new_texture->texture_width = 0;
  new_texture->texture_height = 0;
  
  return(new_texture);
}

/*frees my_texture structure*/
void free_my_texture(my_texture* new_texture)
{
  if(new_texture->texture != NULL)
    { 
      SDL_DestroyTexture(new_texture->texture);
      new_texture->texture = NULL;
      new_texture->texture_width = 0;
      new_texture->texture_height = 0;
    }
}

/*loads an image given a color key i.e the color chosen to be transparent*/
bool load_image(my_texture* new_texture,SDL_Renderer* renderer,char* path,int R_value,int G_value,int B_value)
{
  bool success = 1;
  SDL_Surface* temp_surface = NULL;

  temp_surface = IMG_Load(path);
  if(temp_surface == NULL)
    {
      success = 0;
      printf("Error loading image error:%s",IMG_GetError());
    }
  else
    {
      SDL_SetColorKey(temp_surface,SDL_TRUE,SDL_MapRGB(temp_surface->format,R_value,G_value,B_value));
      new_texture->texture = SDL_CreateTextureFromSurface(renderer,temp_surface);
      if(new_texture->texture == NULL)
	{
	  success = 0;
	  printf("Unable to render error:%s",SDL_GetError());
	}
      else
	{
	  new_texture->texture_width = temp_surface->w;
	  new_texture->texture_height = temp_surface->h;
	}
      /*Get rid of old surface*/
      SDL_FreeSurface(temp_surface);
    }
  return(success);
}

/*renders the texture handling several possible options like rotation,flipping*/
void render_my_texture(my_texture* new_texture,SDL_Renderer* renderer,int x,int y,SDL_Rect* clip,double angle,SDL_Point* center,SDL_RendererFlip flip)
{
  SDL_Rect position;
  position.x = x;
  position.y = y;
  position.w = new_texture->texture_width;
  position.h = new_texture->texture_height;
  /*position = {x,y,new_texture->texture_width,new_texture->texture_height};*/
  if(clip != NULL)
    {
      position.w = clip->w;
      position.h = clip->h;
    }
  SDL_RenderCopyEx(renderer,new_texture->texture,clip,&position,angle,center,flip);
}

/*Load image without color key*/
bool load_image_normally(my_texture* new_texture,SDL_Renderer* renderer,char* path)
{
  bool success = 1;
  SDL_Surface* temp_surface = NULL;

  temp_surface = IMG_Load(path);
  if(temp_surface == NULL)
    {
      success = 0;
      printf("Error loading image error:%s",IMG_GetError());
    }
  else
    {
      new_texture->texture = SDL_CreateTextureFromSurface(renderer,temp_surface);
      if(new_texture->texture == NULL)
	{
	  success = 0;
	  printf("Unable to render error:%s",SDL_GetError());
	}
      else
	{
	  new_texture->texture_width = temp_surface->w;
	  new_texture->texture_height = temp_surface->h;
	}
      /*Get rid of old surface*/
      SDL_FreeSurface(temp_surface);
    }
  return(success);
}

/*Sets the color key for a given texture*/
void set_color(my_texture* new_texture,Uint8 red,Uint8 green,Uint8 blue)
{
  SDL_SetTextureColorMod(new_texture->texture,red,green,blue);
}

/*Sets the alpha value i.e. transparency*/
void set_alpha(my_texture* new_texture,Uint8 alpha)
{
  SDL_SetTextureAlphaMod(new_texture->texture,alpha);
}

/*Sets the blending for a texture*/
void set_blend(my_texture* new_texture,SDL_BlendMode blending)
{
  SDL_SetTextureBlendMode(new_texture->texture,blending);
}

/*Loads the Given text into a texture*/
/*Used to load text onto the screen using the TTF library*/
bool load_from_rendered_text(my_texture* new_texture,SDL_Renderer* renderer,char* text,SDL_Color text_color,TTF_Font* font)
{
  bool success = 1;
  SDL_Surface* text_surface = NULL;
  if(new_texture->texture != NULL)
    {
      free_my_texture(new_texture);
    }
  text_surface = TTF_RenderText_Solid( font, text, text_color);
  if( text_surface == NULL)
    {
      success = 0;
      printf("Unable to render text surface ttf error:%s\n",TTF_GetError());
    }
  else
    {
      new_texture->texture = SDL_CreateTextureFromSurface( renderer, text_surface);
      if(new_texture->texture == NULL)
	{
	  success = 0;
	  printf("Unable to create texture error:%s\n",SDL_GetError());
	}
      else
	{
	  new_texture->texture_width = text_surface->w;
	  new_texture->texture_height = text_surface->h;
	}
      SDL_FreeSurface(text_surface);
    }
  return(success);
}
