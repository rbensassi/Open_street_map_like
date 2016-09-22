#include "Parse.h"
#ifndef __PARSE_H__
#define __PARSE_H__
#define NODE_WITHOUT_LATITUDE "noLAT"
#define NODE_WITHOUT_LONGITUDE "noLON"
#define BOUND_NOT_FOUND "noBOUND"
#include "../../libs/hashmap.h"
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/parserInternals.h>

#endif

char* getLatitude(const xmlChar **attributs);
char* getLongitude(const xmlChar **attributs);
char* getBounds(char * option, const xmlChar **attributs);
int test_type(char * tagkey);
int isSetWayName(char *attr);
