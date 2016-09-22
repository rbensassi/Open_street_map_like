#include "lib/stylefile.h"

extern doc_data informations;
extern char *xmlcolorfile;


style *s;
int correctDoc = 0;


int isDefineId(char *id){
  if(strcmp(id,"service") == 0 || strcmp(id,"residential") == 0 || strcmp(id,"secondary") == 0 || strcmp(id,"tertiary") == 0 || strcmp(id,"unclassified") == 0 || strcmp(id,"primary") == 0 || strcmp(id,"trunk") == 0 || strcmp(id,"motorway") == 0 || strcmp(id,"building") == 0)
    return 1;
  return 0;
}


int nbElement(const xmlChar **tab){
  int i = 0;
  while(tab[i] != NULL){
    i++;
  }
  return i;
}


int isGoodValue(int i){
  if(i > 255 || i < 0)
    return 0;
  return 1;
}


void setColor(const xmlChar **attrs){
  if(strcmp((const char *)attrs[2],"r") != 0 || strcmp((const char *)attrs[4],"g") != 0 || strcmp((const char *)attrs[6],"b") != 0){
    fprintf(stderr,"Le format d'un tag doit etre typer ainsi (valeur est un entier) :\n k=\"valeur\" r=\"valeur\" g=\"valeur\" b=\"valeur\"\nk=\"valeur\" t=\"valeur\"\nk=\"valeur\" t=\"valeur\" r=\"valeur\" g=\"valeur\" b=\"valeur\"\n");
    exit(-1);
  }
    
  const char * str1 = (const char *)attrs[3];
  char * endptr1;
  const char * str2 = (const char *)attrs[5];
  char* endptr2;
  const char * str3 = (const char *)attrs[7];
  char * endptr3;
      
  int n1 = strtol(str1, &endptr1, 10);
  int n2 = strtol(str2, &endptr2, 10);
  int n3 = strtol(str3, &endptr3, 10);
      
  if(endptr1 == str1 || endptr2 == str2 || endptr3 == str3){
    printf("Parsing color xml file went wrong\n");
    exit(-1);
  }
  else if(isGoodValue(n1) == 0 || isGoodValue(n2) == 0 || isGoodValue(n3) == 0){
    fprintf(stderr,"Une ou plusieurs des valeurs entrees pour les couleurs n'est pas correct (entre 0 entre 255 compris)\n");
    exit(-1);
  }else{
    char *id = malloc(20);
    strcpy(id,(char *)attrs[1]);
    if(isDefineId(id) == 0){
      fprintf(stderr,"Erreur dans un type de way : %s\n",id);
      xmlcolorfile = NULL;
      exit(-1);
    }
    s->r = n1;
    s->g = n2;
    s->b = n3;
    s->thickness = -1;
    hashmap_put(informations.hashcolor,id,(any_t *)s);	
  }
}


void setthick(const xmlChar **attrs){
  if(strcmp((const char *)attrs[2],"t") != 0){
    fprintf(stderr,"Le format d'un tag doit etre typer ainsi (valeur est un entier) :\n k=\"valeur\" r=\"valeur\" g=\"valeur\" b=\"valeur\"\nk=\"valeur\" t=\"valeur\"\nk=\"valeur\" t=\"valeur\" r=\"valeur\" g=\"valeur\" b=\"valeur\"\n");
    exit(-1);
  }
      
  const char * str = (const char *)attrs[3];
  char * endptr;
      
  int n = strtol(str, &endptr, 10);

  if(endptr == str){
    printf("Parsing color xml file went wrong\n");
    exit(-1);
  }
  if( n < 0 || n > 8 ){
    fprintf(stderr,"Une ou plusieurs des valeurs entrees pour les couleurs n'est pas correct (entre 0 entre 255 compris)\n");
    exit(-1);
  }
  char *id = malloc(20);
  strcpy(id,(char *)attrs[1]);
  if(isDefineId(id) == 0){
    fprintf(stderr,"Erreur dans un type de way : %s\n",id);
    xmlcolorfile = NULL;
    exit(-1);
  }
  s->r = -1;
  s->g = -1;
  s->b = -1;
  s->thickness = n;
  hashmap_put(informations.hashcolor,id,(any_t *)s);
}


void setall(const xmlChar **attrs){
  if(strcmp((const char *)attrs[2],"t") != 0){
    fprintf(stderr,"Le format d'un tag doit etre typer ainsi (valeur est un entier) :\n k=\"valeur\" r=\"valeur\" g=\"valeur\" b=\"valeur\"\nk=\"valeur\" t=\"valeur\"\nk=\"valeur\" t=\"valeur\" r=\"valeur\" g=\"valeur\" b=\"valeur\"\n");
    exit(-1);
  }else if(strcmp((const char *)attrs[4],"r") != 0 || strcmp((const char *)attrs[6],"g") != 0 || strcmp((const char *)attrs[8],"b") != 0){
    fprintf(stderr,"Le format d'un tag doit etre typer ainsi (valeur est un entier) :\n k=\"valeur\" r=\"valeur\" g=\"valeur\" b=\"valeur\"\nk=\"valeur\" t=\"valeur\"\nk=\"valeur\" t=\"valeur\" r=\"valeur\" g=\"valeur\" b=\"valeur\"\n");
    exit(-1);
  }
      
  const char * str1 = (const char *)attrs[3];
  char * endptr1;
  const char * str2 = (const char *)attrs[5];
  char * endptr2;
  const char * str3 = (const char *)attrs[7];
  char* endptr3;
  const char * str4 = (const char *)attrs[9];
  char * endptr4;
      
  
  int n1 = strtol(str1, &endptr1, 10);
  int n2 = strtol(str2, &endptr2, 10);
  int n3 = strtol(str3, &endptr3, 10);
  int n4 = strtol(str4, &endptr4, 10);
      

  if(endptr1 == str1 || endptr2 == str2 || endptr3 == str3 || endptr4 == str4){
    printf("Parsing color xml file went wrong\n");
    exit(-1);
  }
  if( n1 < 0 || n1 > 8 ){
    fprintf(stderr,"Une ou plusieurs des valeurs entrees pour les couleurs n'est pas correct (entre 0 entre 255 compris)\n");
    exit(-1);
  }
  if(isGoodValue(n2) == 0 || isGoodValue(n3) == 0 || isGoodValue(n4) == 0){
    fprintf(stderr,"Une ou plusieurs des valeurs entrees pour les couleurs n'est pas correct (entre 0 entre 255 compris)\n");
    exit(-1);
  }
  char *id = malloc(20);
  strcpy(id,(char *)attrs[1]);
  if(isDefineId(id) == 0){
    fprintf(stderr,"Erreur dans un type de way : %s\n",id);
    xmlcolorfile = NULL;
    exit(-1);
  }
  s->r = n2;
  s->g = n3;
  s->b = n4;
  s->thickness = n1;
  hashmap_put(informations.hashcolor,id,(any_t *)s);
}


void parsefile(void *user_data, const xmlChar *name, const xmlChar **attrs){
  if(strcmp((char*)name,"color") == 0){
    correctDoc = 1;
  }else if(strcmp((char*)name,"tag") == 0 && attrs != NULL && nbElement(attrs) >= 2 && correctDoc){
    s = NULL;
    s = malloc(10);

    if(nbElement(attrs) == 8){
      setColor(attrs);
    }else if(nbElement(attrs) == 4){
      setthick(attrs);
    }else if(nbElement(attrs) == 10){
      setall(attrs);	
    }else{
      fprintf(stderr,"Balise mal rempli\n");
    }
  }else{
    fprintf(stderr,"Balise XML non reconnu : <%s>\n",name);
    exit(-1);
  }
}

int parsecolorfile() {
  
  informations.hashcolor = hashmap_new();
  
  xmlSAXHandler sh = { 0 };

  sh.startElement = parsefile;

  xmlParserCtxtPtr couleur;
  if ((couleur = xmlCreateFileParserCtxt(xmlcolorfile)) == NULL) {
    fprintf(stderr, "Erreur lors de la création du contexte\n");
    return -1;
  }
  couleur->sax = &sh;
  xmlParseDocument(couleur);
  if (couleur->wellFormed) {
    printf("Document XML bien formé\n");
  } else {
    fprintf(stderr, "Document COLOR XML mal formé\n");
    return -1;
  }
  return 1;
}
