#include "hashmap_get_functions.h"


extern doc_data informations ;
extern char * wayid;
extern way *sway;


/******************************************
Obtenir la latitude d'un node en founissant
ses attributs
******************************************/


char* getLatitude(const xmlChar **attributs){
  int i = 2;
  while(attributs[i] != NULL){
    if(strcmp("lat",(char*)attributs[i]) == 0){
      return (char *) attributs[i+1];
    }
    i += 2;
  }return NODE_WITHOUT_LATITUDE;
}


/****************************************
Obtenir la longitude d'un node de la même
maniére
****************************************/


char* getLongitude(const xmlChar **attributs){
  int i = 2;
  while(attributs[i] != NULL){
    if(strcmp("lon",(char*)attributs[i]) == 0){
      return (char *) attributs[i+1];
    }
    i += 2;
  }return NODE_WITHOUT_LONGITUDE;
}


/**************************************
Obtenir une bordure de la map
en fournissant celle voulue et la liste
des attributs de Bounds
**************************************/


char* getBounds(char * option, const xmlChar **attributs){
  int i = 0;
  while(attributs[i] != NULL){
    if(strcmp(option,(char*)attributs[i]) == 0){
      return (char *) attributs[i+1];
    }
    i += 2;
  }return BOUND_NOT_FOUND;
}



/*********************************
On teste quel est le type d'un way
*********************************/

int test_type(char * tagkey){
  return ((strcmp((char *)tagkey,"building") == 0) ||(strcmp((char *)tagkey,"highway") == 0)||(strcmp((char *)tagkey,"waterway")==0)||(strcmp((char *)tagkey,"landuse")==0)||(strcmp((char *)tagkey,"surface")==0)||(strcmp((char *)tagkey,"leisure") == 0) || (strcmp((char *)tagkey,"natural") == 0)||(strcmp((char *)tagkey,"bridge")==0)||(strcmp((char *)tagkey,"boundary")==0));
}

int isSetWayName(char *attr){
  if(strcmp(attr,"name") == 0)
    return 1;
  return 0;
}
