#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "print/lib/dessin.h"
#include "parse/libs/Parse.h"

int main(int argc, char *argv[]){
  if(argc < 2){
    fprintf(stderr, "Un fichier doit etre donné\n");
    return EXIT_FAILURE;
  }
  if(argc == 3){
    //setcolorfile = 1;
    char *symlinkpath = argv[2];
    char actualpath [PATH_MAX+1];
    char *ptr;
    if((ptr = realpath(symlinkpath, actualpath)) != NULL){
      xmlcolorfile = malloc(100);
      xmlcolorfile = ptr;
      parsecolorfile();
    }else{
      fprintf(stderr,"Fichier de coloriage personnel non trouvé, coloriage par défault initialisé\n");
    }
  } 
  parse(argv[1]);
  render();
  return EXIT_SUCCESS;
}

