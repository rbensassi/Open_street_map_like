
/****************************************
Inclusion des headers respectivements :
-header de la hashmap
-header pour la définition des structures
-header des fonctions de dessins
****************************************/

#include "../libs/hashmap.h"
#include "libs/Parse.h"


/********************************
Initialisation d'un structure way
********************************/
doc_data informations ;
char * wayid = NULL;
way *sway = NULL;

/***************************************************
Initialisation des différentes compteurs et booléens 
***************************************************/

int count = 0;
int last = 0;
int type = 0;
int SIZE_REF_LIST = 100;
int NB_RELATIONS=100;

/**********************************************
SAX : A partir d'une balise
on obtient la liste de ces attributs et son nom
**********************************************/

void parse_sax(void *user_data, const xmlChar *name, const xmlChar **attrs){
  if(strcmp((char*)name,"bounds") == 0){
    const char *minlat = getBounds("minlat",attrs);
    const char * maxlat = getBounds("maxlat",attrs);
    const char * maxlon = getBounds("maxlon",attrs);
    const char * minlon = getBounds("minlon",attrs);
    if(strcmp(BOUND_NOT_FOUND,minlat) == 0 || strcmp(BOUND_NOT_FOUND,maxlat) == 0
       || strcmp(BOUND_NOT_FOUND,maxlon) == 0 || strcmp(BOUND_NOT_FOUND,minlon) == 0){
      printf("Bordure mal formée\n");
      exit(0);
    }
    informations.min_lat=atof(minlat);
    informations.min_lon=atof(minlon);
    informations.max_lat=atof(maxlat);
    informations.max_lon=atof(maxlon);
  }
  
  if(strcmp((char*)name,"way") == 0){
    ajoutway((char*)attrs[1]);
  }
  if(strcmp((char*)name,"relation") == 0){
    ajoutrelation();
  }
  if(strcmp((char*)name,"node") == 0){
    ajoutnode(attrs);
  }
  if((strcmp((char*)name,"way") != 0 )&& (strcmp((char*)name,"relation") != 0)){
    if(strcmp((char*)name,"nd") == 0){
      if(last == SIZE_REF_LIST){
	SIZE_REF_LIST *= 10;
	sway->refList = (realloc(sway->refList,SIZE_REF_LIST*sizeof(char*))); 
      }
      sway->refList[last] = malloc(20);
      strcpy(sway->refList[last],(char *)attrs[1]);
      last++;
    }else if((strcmp((char*)name,"member") == 0)&&(strcmp((char*)attrs[1],"way")==0)){
      if (strcmp((char*)attrs[5],"inner")==0){
	ajoutinner((char*)attrs[3]);
      }else{
	ajoutouter((char*)attrs[3]);
      }

    }    if(strcmp((char*)name,"tag") == 0){
      int res;
      if((res = test_type((char*)attrs[1])) != 0){
	if(informations.nbrelation==-1){
	  if(sway != NULL){
	    strcpy(sway->type,(char *)attrs[1]);
	    strcpy(sway->valeur,(char *)attrs[3]);
	    type = 1;
	    sway->thickness = 0;
	  }
	}else {
          strcpy(informations.relation_list[informations.nbrelation].type,(char *)attrs[1]);
          strcpy(informations.relation_list[informations.nbrelation].valeur,(char *)attrs[3]);
	  type = 1;
	} 
      }
      if(isSetWayName((char *) attrs[1])){
	//printf("parse : %s \n",(char*)attrs[3]);
	if(sway != NULL){
	  strcpy(sway->name,(char *)attrs[3]);  
	}
      }	
      else if((strcmp((char*)attrs[1],"type")==0)&&(informations.nbrelation!=-1)){
	strcpy(informations.relation_list[informations.nbrelation].name,(char*)attrs[3]);   
      }
    }
  }
}


int parse(char*file){
  
  informations.hashmap = hashmap_new();
  informations.hashforeground = hashmap_new();
  informations.hashbackground = hashmap_new();
  informations.nbrelation=-1;
  informations.relation_list= (relation*)(malloc(NB_RELATIONS*sizeof(relation)));    

  
  // Intialisation à zéro de tous les membres (NULL pour un pointeur par conversion)
  xmlSAXHandler sh = { 0 };

  // Affectation des fonctions de rappel
  sh.startElement = parse_sax;

  xmlParserCtxtPtr ctxt;
  // Création du contexte
  if ((ctxt = xmlCreateFileParserCtxt(file)) == NULL) {
    fprintf(stderr, "Erreur lors de la création du contexte\n");
    exit(-1);
    //return EXIT_FAILURE;
  }
  // Fonctions de rappel à utiliser
  ctxt->sax = &sh;
  // Analyse
  xmlParseDocument(ctxt);
  // Le document est-il bien formé ?
  if (ctxt->wellFormed) {
    printf("Document XML bien formé\n");
  } else {
    fprintf(stderr, "Document XML mal formé\n");
    exit(-1);
    //return EXIT_FAILURE;
  }
  if(sway != NULL){
    if(!type)
      strcpy(sway->type,(char *)"unknown");
    if(strcmp(sway->type,"waterway") == 0 || ((strcmp(sway->type,"natural") == 0) && (strcmp(sway->type,"coastline") == 0)))
      hashmap_put(informations.hashbackground,(char *)wayid,(any_t *)sway);
    else
      hashmap_put(informations.hashforeground,(char *)wayid,(any_t *)sway);
  }
 
   
  printf("Nombre d'entrer dans la fonction : %d\n", count);
  printf("Taille de la hashmap : %d\n",hashmap_length(informations.hashmap));
  return EXIT_SUCCESS;
}

