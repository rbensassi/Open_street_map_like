#include "dessin_setting_functions.h"

extern doc_data informations;
extern display windparams;

point conversion(char *lon, char *lat){
  char *test;
  point p;
  double la = strtod(lat, &test);
  double la_rad = (la/360) * 2 * PI;
  if((*test) != '\0'){
    fprintf(stderr,"la latitude n est pas un chiffre \n");
    return p;
  }
  double lo = strtod(lon,&test);
  if((*test)!='\0'){
    fprintf(stderr,"la longitude n est pas un chiffre \n");
    return p;
  }
  p.x = ((lo - informations.min_lon)/360.) * cos(la_rad) *windparams.scale;
  p.y = ((la -  informations.min_lat)/360.) * windparams.scale;
  p.y = windparams.current_height - p.y;
  return p;
}
point recupere_coordonnee(char *ref){
  char *lat;
  char *lon;
  data *dat= malloc(sizeof(data));
  hashmap_get(informations.hashmap,(char*)ref,(any_t*)&dat);
  lat = (char*)((dat)->latitude);
  lon = (char*)((dat)->longitude);
  point p= conversion(lon,lat);
  return p;
}
/*****************************
Donne l'epaisseur d'un highway
*****************************/

int getThicknessWay(char* attribut){
  if(strcmp((char*)attribut,"service") == 0)
    return 1;
  else if(strcmp(attribut,"residential") == 0)
    return 2;
  else if(strcmp(attribut,"unclassified") == 0)
    return 3;
  else if(strcmp(attribut,"tertiary") == 0)
    return 4;
  else if(strcmp(attribut,"secondary") == 0)
    return 5;
  else if(strcmp(attribut,"primary") == 0)
    return 6;
  else if(strcmp(attribut,"trunk") == 0)
    return 7;
  else if(strcmp(attribut,"motorway") == 0)
    return 8;
  return 1;
}

style * getColor(char *type){
  style *c = malloc(100);
  if(xmlcolorfile == NULL || hashmap_get(informations.hashcolor,type,(any_t)&c) == -3)
    return NULL;
  return c;
}
