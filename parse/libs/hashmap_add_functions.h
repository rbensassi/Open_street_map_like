#include "Parse.h"
#ifndef __PARSE_H__
#define __PARSE_H__
#define NODE_WITHOUT_LATITUDE "noLAT"
#define NODE_WITHOUT_LONGITUDE "noLON"
#define BOUND_NOT_FOUND "noBOUND"
#include "../../libs/hashmap.h"
#include "hashmap_get_functions.h"
#endif

void ajoutnode(const xmlChar **attrs);
void ajoutway( char *id);
void ajoutrelation();
void ajoutinner( char * ref);
void ajoutouter( char *ref);
