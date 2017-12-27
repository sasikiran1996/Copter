#ifndef MY_TEXTURE_H_INCLUDED
#define MY_TEXTURE_H_INCLUDED

/*A structure called my_texture to handle all the operations related to textures*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef struct my_texture_
{
  SDL_Texture* texture;
  int texture_width;
  int texture_height;

}my_texture;

/*creates a new texture and returns it*/
my_texture* initialize_my_texture();

/*Deallocates memory allocated to texture*/
void free_my_texture(my_texture* new_texture);

/*Loads a image as my_texture*/
bool load_image(my_texture* new_texture,SDL_Renderer* renderer,char* path,int R_value,int G_value,int B_value);

/*renders texture at given x,y 
defaults-
clip = NULL when rendering whole texture
angle = 0.0
center = NULL rotates about center of image
flip = SDL_FLIP_NONE*/
void render_my_texture(my_texture* new_texture,SDL_Renderer* renderer,int x,int y,SDL_Rect* clip,double angle,SDL_Point* center,SDL_RendererFlip flip);  

/*Without colour keying*/
bool load_image_normally(my_texture* new_texture,SDL_Renderer* renderer,char* path);

/*set modulation colour i.e. increase or decrease r-g-b components*/
void set_color(my_texture* new_texture,Uint8 red,Uint8 green,Uint8 blue);

/*Set alpha modulation -transparency*/
void set_alpha(my_texture* new_texture,Uint8 alpha);

/*Set blending mode*/
void set_blend(my_texture* new_texture,SDL_BlendMode blending);

/*creates a texture from font, given text and color*/
bool load_from_rendered_text(my_texture* new_texture,SDL_Renderer* renderer,char* text,SDL_Color text_color,TTF_Font* font);

#endif /*MY_TEXTURE_H_INCLUDED*/
