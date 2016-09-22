#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/parserInternals.h>


/*****************************
Définition des macros d'erreur
*****************************/

#define NODE_WITHOUT_LATITUDE "noLAT"
#define NODE_WITHOUT_LONGITUDE "noLON"
#define BOUND_NOT_FOUND "noBOUND"


#ifndef __PARSE_H__
#define __PARSE_H__

#include "hashmap_add_functions.h"
#include "hashmap_get_functions.h"
#include "../../libs/hashmap.h"


typedef struct {
  char  name[100];
  int thickness;
  char *type;
  char*valeur;
  char **refList;
  int nbref;
} way;

typedef struct {
  char * longitude;
  char * latitude;
 
}data;

typedef struct {
  char   name[100];
  char  type[100];
  char valeur[100];
  char **outermembers;
  char **innermembers;
  int nbouter;
  int nbinner;
  int max_outer;
  int max_inner;
}relation;
typedef struct {
  hashmap_map *hashmap;
  hashmap_map *hashbackground;
  hashmap_map *hashforeground;
  hashmap_map *hashcolor;
  relation *relation_list;
  int nbrelation;
  double min_lat;
  double min_lon; 
  double max_lat; 
  double max_lon;
} doc_data;

 
int parse(char*);

void parse_sax(void *, const xmlChar *, const xmlChar **);
#endif
