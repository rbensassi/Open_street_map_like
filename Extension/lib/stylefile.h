#ifndef  __COLORFILE__H
#define __COLORFILE__H
#include <errno.h>
#include <unistd.h>
#include "../../parse/libs/Parse.h"
int parsecolorfile();
int isGoodValue(int i);
int nbElement(const xmlChar **);
int isDefineId(char *);
void setColor(const xmlChar **);
void setthick(const xmlChar **);
void setall(const xmlChar **);
#endif
typedef struct{
  int r;
  int g;
  int b;
  int thickness;
} style;
