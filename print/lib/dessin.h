#ifndef __DESSIN_H__
#define __DESSIN_H__
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "SDL2_gfxPrimitives.h"
#include "../../libs/hashmap.h"
#include "../../Extension/lib/search.h"
#include "../../Extension/lib/stylefile.h"
#include "../../Extension/lib/Svg.h"
#include "../../parse/libs/Parse.h"
#define BASE_WINDOW 700
#define PI 3.1415927
char *xmlcolorfile;


typedef struct point {
    double x;
    double y;
} point ;
typedef struct {
  SDL_Window* fenetre;
  SDL_Renderer* renderer;//Déclaration du renderer
  char *buff;
  int current_width;
  int current_height; 
  double scale; 
}display;

#include "dessin_setting_functions.h"

void Init_display();
int render();
void  testway(way );
int _dessine (way );
int getThicknessWay(char*);
int dessineWay(char **,Uint8 ,Uint8  ,Uint8,Uint8,int );
int dessinePolygone(char **,int ,Uint8  ,Uint8  ,Uint8  ,Uint8  );
int dessineCoastLine(char** ,int );
#endif
