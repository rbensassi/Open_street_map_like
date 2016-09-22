#include "hashmap_add_functions.h"

extern doc_data informations;
extern char * wayid;
extern way *sway;

/***************************************************
Initialisation des différentes compteurs et booléens 
***************************************************/


extern int count;
extern int last;
extern int type;
extern int SIZE_REF_LIST;
extern int NB_RELATIONS;


void ajoutnode(const xmlChar **attrs){
  data *d = malloc(2*sizeof(char *)*10);
  char *id = malloc(20);
  char *lat = malloc(20);
  char *lon = malloc(20);
  strcpy(id,(char *)attrs[1]);
  strcpy(lat,getLatitude(attrs)); 
  strcpy(lon,getLongitude(attrs));
  if(strcmp(lon,NODE_WITHOUT_LONGITUDE) == 0 || strcmp(lat,NODE_WITHOUT_LATITUDE) == 0){
    fprintf(stderr,"Node mal formée\n");
    exit(0);
  }
  d->latitude = lat;
  d->longitude = lon;
  hashmap_put(informations.hashmap,(char *)id,(any_t *)d);

}
void ajoutway( char *id){
  count++;
  if(sway != NULL){
    if(!type)strcpy(sway->type,(char *)"unknown");
    sway->refList[last] = NULL;
    sway->nbref = last;
    if(((strcmp(sway->type,"waterway") == 0)&&(strcmp(sway->valeur,"weir")!=0))|| ((strcmp(sway->type,"natural") == 0) && (strcmp(sway->type,"coastline") == 0)))
      hashmap_put(informations.hashbackground,(char *)wayid,(any_t *)sway);
    else
      hashmap_put(informations.hashforeground,(char *)wayid,(any_t *)sway);
  }
  sway = NULL;
  wayid = NULL;
  last = 0;
  type = 0 ;
  wayid = malloc(sizeof(char*));
  sway = malloc(sizeof(way));
  sway->type = malloc(100);
  sway->refList = malloc(SIZE_REF_LIST*sizeof(char*));
  sway->valeur = malloc(100);
  strcpy(wayid,id);


}
void ajoutrelation(){
  informations.nbrelation++;
  if(informations.nbrelation==NB_RELATIONS){
    NB_RELATIONS=NB_RELATIONS*2;
    informations.relation_list= (realloc(informations.relation_list,NB_RELATIONS*sizeof(relation)));
  }
  informations.relation_list[informations.nbrelation].nbouter=0;
  informations.relation_list[informations.nbrelation].nbinner=0;
  informations.relation_list[informations.nbrelation].max_outer=300;
  informations.relation_list[informations.nbrelation].max_inner=300;
  informations.relation_list[informations.nbrelation].outermembers=malloc(300*sizeof(char*));
  informations.relation_list[informations.nbrelation].innermembers=malloc(300*sizeof(char*));


}
void ajoutinner( char * ref){
  if( informations.relation_list[informations.nbrelation].nbinner==informations.relation_list[informations.nbrelation].max_inner){
    informations.relation_list[informations.nbrelation].max_inner*=2;
    informations.relation_list[informations.nbrelation].innermembers=(realloc(informations.relation_list[informations.nbrelation].innermembers,informations.relation_list[informations.nbrelation].max_inner*sizeof(char*)));
  }
  informations.relation_list[informations.nbrelation].innermembers[ informations.relation_list[informations.nbrelation].nbinner]=(char*)(malloc(50));
  strcpy(informations.relation_list[informations.nbrelation].innermembers[ informations.relation_list[informations.nbrelation].nbinner],ref);
  informations.relation_list[informations.nbrelation].nbinner++;
  
}
void ajoutouter( char *ref){
  if( informations.relation_list[informations.nbrelation].nbouter== informations.relation_list[informations.nbrelation].max_outer){
    informations.relation_list[informations.nbrelation].max_outer*=2;
    informations.relation_list[informations.nbrelation].outermembers= (realloc(informations.relation_list[informations.nbrelation].outermembers, informations.relation_list[informations.nbrelation].max_outer*sizeof(char*)));
  }
  informations.relation_list[informations.nbrelation].outermembers[ informations.relation_list[informations.nbrelation].nbouter]=(char*)(malloc(50));
  strcpy(informations.relation_list[informations.nbrelation].outermembers[informations.relation_list[informations.nbrelation].nbouter],ref);
  informations.relation_list[informations.nbrelation].nbouter++;  
}
