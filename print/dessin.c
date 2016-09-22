#include "lib/dessin.h"
extern doc_data informations;
display windparams;
hashmap_map *searchByName;
SDL_Event event;
extern char text[30];

	
/*
  agrandit la fenetre 
*/
	
int agrandir(){
  if(windparams.current_height<700){
    double facteur;
    if(700./windparams.current_height<1200./windparams.current_width)facteur=700./windparams.current_height;
    else facteur=1200./windparams.current_width ;
    windparams.scale=windparams.scale*facteur;
    windparams.current_width=(int)(windparams.current_width*facteur);
    windparams.current_height=(int)(windparams.current_height*facteur);
  }
  return 0;
}
/*
  initialise les parametres nécéssaires pour le dessin 

      
*/
void Init_display(){
  windparams.current_width=BASE_WINDOW;
  windparams.current_height=BASE_WINDOW;
	  
  double cos_min = cos((informations.min_lat/360) * 2 * PI);
  double cos_max = cos((informations.max_lat/360) * 2 * PI);
	      
  double x_min_lat = ((informations.max_lon - informations.min_lon)/360.) * cos_min;
  double x_max_lat = ((informations.max_lon - informations.min_lon)/360.) * cos_max;
  double x_max = (x_min_lat > x_max_lat) 
    ? x_min_lat : x_max_lat;
  double y_max = ((informations.max_lat - informations.min_lat)/360.);
  if (x_max > y_max) {
    windparams.scale= BASE_WINDOW/x_max;
    windparams.current_height = (int) (y_max *windparams.scale);
  }
  else {
    windparams.scale= BASE_WINDOW/y_max;
    windparams.current_width  = (int) (x_max * windparams.scale);
	    
  }
  agrandir();
}
	   

int dessineWay(char **refList,Uint8 r ,Uint8 g ,Uint8  b,Uint8 trans,int thickness ){
  int j = 0;
  point p1,p2;
  while(refList[j+1] != NULL){
    p1 = recupere_coordonnee(refList[j]);
    p2 = recupere_coordonnee(refList[j+1]);
    int x1 = (int) p1.x;
    int y1 = (int) p1.y;
    int x2 = (int) p2.x;
    int y2 = (int) p2.y;
    thickLineRGBA (windparams.renderer, x1, y1, x2, y2,thickness,r,g,b,trans);
    j++;
  }
  return 0;
}

int dessinePolygone(char **refList,int nbpoints,Uint8 r ,Uint8 g ,Uint8  b,Uint8 trans ){
  int j = 0;
  Sint16   *x, *y;
  point p;
  if(nbpoints!=0){
    x = (Sint16 *) (malloc(nbpoints*sizeof(Sint16)));
    y = (Sint16 * ) (malloc(nbpoints*sizeof(Sint16)));
    while(refList[j] != NULL){
      p = recupere_coordonnee(refList[j]);
      *(x + j) = (Sint16) p.x; 
      *(y + j) = (Sint16) p.y;                    
      j++;
    }
    int res= filledPolygonRGBA(windparams.renderer, x, y, j, r,g,b,trans);
    polygonRGBA(windparams.renderer, x, y, j, r,g,b,255); 
    free(x);
    free(y);
    return res;
  }
  return 0;  
}
     

int _dessineCoastLine(char** refList,int nbNode){
  point p1;
  point p2;
  point p[4]; 
  p1=recupere_coordonnee(refList[0]);
  p2=recupere_coordonnee(refList[nbNode-1]);
  point p3=recupere_coordonnee(refList[1]);                     
  int j = 0;
  Sint16   *x, *y;
  point p4;
  x = (Sint16 *) (malloc((5+nbNode)*sizeof(Sint16)));
  y = (Sint16 * ) (malloc((5+nbNode)*sizeof(Sint16)));
  while(refList[j] != NULL){
    p4 = recupere_coordonnee(refList[j]);
    *(x + j) = (Sint16) p4.x; 
    *(y + j) = (Sint16) p4.y;                    
    j++;
  }
  if(p1.y<p3.y){
    p[0].y=p1.y;
    p[0].x=0;
    p[1].y=windparams.current_height;;
    p[1].x=0;  
    p[2].x=windparams.current_width;
    p[2].y=windparams.current_height;;
    p[3].x=windparams.current_width;
    p[3].y=p2.y;
    int  i=0 ;
    for(i=0;i<4;i++){
      *(x + j) = (Sint16) p[i].x; 
      *(y + j) = (Sint16) p[i].y;
      j++; 
    }
                           
  }else if(p1.y>p3.y){
    p[0].y=p1.y;
    p[0].x=windparams.current_width;
    p[1].y=0;
    p[1].x=windparams.current_width;;  
    p[2].x=0;
    p[2].y=0;
    p[3].x=0;
    p[3].y=p2.y;
    int  i=0 ;
    for(i=0;i<4;i++){
      *(x + j) = (Sint16) p[3-i].x; 
      *(y + j) = (Sint16) p[3-i].y;
      j++;
                            
    }
                              
  }
  int res=filledPolygonRGBA(windparams.renderer, x, y, j,55,0,255,200);
  polygonRGBA(windparams.renderer, x, y, j, 55,0,255,200);
  return res;

}



int dessineCoastLine(char** refList,int nbNode){
  if(strcmp(refList[0],refList[nbNode-1])==0){
    _dessineCoastLine(refList,nbNode);
    dessinePolygone(refList,nbNode,230, 230, 230,255);
  }else{
    _dessineCoastLine(refList,nbNode);
  }                      
                       
  return 0;

}

void typeway(way w){
  style *c = malloc(100);
  int r=getThicknessWay(w.valeur);
  if(r==1){
    if((c = getColor("service")) == NULL)
      dessineWay(w.refList,255,255,255,150,2*r);
    else
      dessineWay(w.refList,c->r,c->g,c->b,150,2*r);
  }else if(r==2){
    if((c = getColor("residential")) == NULL)
      dessineWay(w.refList,255,255,255,255,2*r);
    else if(c->thickness == -1)
      dessineWay(w.refList,c->r,c->g,c->b,150,2*r);
    else if(c->r == -1)
      dessineWay(w.refList,255,255,255,255,2*c->thickness);
    else
      dessineWay(w.refList,c->r,c->g,c->b,150,2*c->thickness);
  }else if(r==3){
    if((c = getColor("unclassified")) == NULL)
      dessineWay(w.refList,255,255,255,255,2*r);
    else if(c->thickness == -1)
      dessineWay(w.refList,c->r,c->g,c->b,150,2*r);
    else if(c->r == -1)
      dessineWay(w.refList,255,255,255,255,2*c->thickness);
    else
      dessineWay(w.refList,c->r,c->g,c->b,150,2*c->thickness);
  }else if(r==4){
    if((c = getColor("tertiary")) == NULL)
      dessineWay(w.refList,220,133,163,255,2*r);
    else if(c->thickness == -1)
      dessineWay(w.refList,c->r,c->g,c->b,255,2*r);
    else if(c->r == -1)
      dessineWay(w.refList,220,133,163,255,2*c->thickness);
    else
      dessineWay(w.refList,c->r,c->g,c->b,255,2*c->thickness);
  }else if(r==5){
    if((c = getColor("secondary")) == NULL)
      dessineWay(w.refList,220,133,163,255,2*r);
    else if(c->thickness == -1)
      dessineWay(w.refList,c->r,c->g,c->b,255,2*r);
    else if(c->r == -1)
      dessineWay(w.refList,220,133,163,255,2*c->thickness);
    else
      dessineWay(w.refList,c->r,c->g,c->b,255,2*c->thickness);
  }else if(r==6){
    if((c = getColor("primary")) == NULL)
      dessineWay(w.refList,220,133,163,255,2*r);
    else if(c->thickness == -1)
      dessineWay(w.refList,c->r,c->g,c->b,255,2*r);
    else if(c->r == -1)
      dessineWay(w.refList,220,133,163,255,2*c->thickness);
    else
      dessineWay(w.refList,c->r,c->g,c->b,255,2*c->thickness);
  }else if(r==7){
    if((c = getColor("trunk")) == NULL)
      dessineWay(w.refList,220,133,163,255,2*r);
    else if(c->thickness == -1)
      dessineWay(w.refList,c->r,c->g,c->b,255,2*r);
    else if(c->r == -1)
      dessineWay(w.refList,255,255,255,255,2*c->thickness);
    else
      dessineWay(w.refList,c->r,c->g,c->b,255,2*c->thickness);
  }else if(r==8){
    if((c = getColor("motorway")) == NULL)
      dessineWay(w.refList,220,133,163,255,2*r);
    else if(c->thickness == -1)
      dessineWay(w.refList,c->r,c->g,c->b,255,2*r);
    else if(c->r == -1)
      dessineWay(w.refList,255,255,255,255,2*c->thickness);
    else
      dessineWay(w.refList,c->r,c->g,c->b,255,2*c->thickness);
  }
}


int _dessine (way w){
  style *c = malloc(100);
  if(strcmp(w.type,"highway")==0){
    typeway(w);
  } else if(strcmp(w.type,"building")==0){
    if((c = getColor("building")) == NULL)
      dessinePolygone(w.refList,w.nbref,150,150,150,100);
    else if(c->thickness == -1)
      dessinePolygone(w.refList,w.nbref,c->r,c->g,c->b,150);
    else if(c->r == -1)
      dessinePolygone(w.refList,w.nbref,255,255,255,255);
    else
      dessinePolygone(w.refList,w.nbref,c->r,c->g,c->b,150);
  }else if((((strcmp(w.type,"waterway"))==0)&&(strcmp(w.valeur,"riverbank")==0))||((strcmp(w.type,"natural")==0)&&(strcmp(w.valeur,"water")==0))){
    dessinePolygone(w.refList,w.nbref,141,182,205,255);
  }else if(((strcmp(w.type,"landuse")==0)&&((strcmp(w.valeur,"grass")==0)||(strcmp(w.valeur,"forest")==0)))||((strcmp(w.type,"leisure")==0)&&(strcmp(w.valeur,"park")==0))||((strcmp(w.type,"natural")==0)&&(strcmp(w.valeur,"wood")==0))){
    dessinePolygone(w.refList,w.nbref,0,255,100,255);
  }else if((strcmp(w.type,"natural")==0)&&(strcmp(w.valeur,"coastline")==0)){
    dessineCoastLine(w.refList,w.nbref);
  }else if((strcmp(w.type,"waterway")==0)&&(strcmp(w.valeur,"weir")==0)){
    dessineWay(w.refList,139,123,139,255,5);
  }else if(strcmp(w.type,"waterway")==0){
    dessineWay(w.refList,141,182,205,100,5);
  }
  return 0;
}



int  parcours (hashmap_map *hash){
  int i=0 ;
  for(i = 0; i < 100000; i++){
    if(hash->data[i].in_use != 0) {
      hashmap_element data = hash->data[i];
      _dessine((*((way*)(data.data))));
      if(strcmp(((way*)(data.data))->name,"") != 0){
	//printf("le nom est %s\n",((way*)(data.data))->name);
	hashmap_put(searchByName,((way*)(data.data))->name,(any_t) data.key);
      }
    }
  }
  return 0;
}





int dessinemultipolygone(char**waylist,int nbelements,Uint8 r ,Uint8 g ,Uint8  b,Uint8 trans ){
  int i=0;
  way *w;		 
  for(i=0;i<nbelements;i++){
    if(hashmap_get(informations.hashforeground,waylist[i],(any_t*)&w)!=MAP_MISSING){
      dessinePolygone(w->refList,w->nbref,r,g,b,trans);
    } 
  }
  return 0;
}        
         

int dessinerelation(relation r){
  if((strcmp(r.name,"multipolygon")==0)){
    if(strcmp(r.valeur,"park")==0)
      dessinemultipolygone(r.outermembers,r.nbouter,0,255,0,155);
    if(strcmp(r.valeur,"park")==0)
      dessinemultipolygone(r.innermembers,r.nbinner,255,0,0,255);
    else  dessinemultipolygone(r.innermembers,r.nbinner,255,185,15,155);
  }
  return 0;

}
int _relations_draw(){
  int i=0 ;
  for(i=0;i<informations.nbrelation;i++){ 
    dessinerelation(informations.relation_list[i]);
  }
  return 0;
}

int render(){
  
  if(SDL_Init(SDL_INIT_VIDEO) < 0) // Initialisation de la SDL
    {
      printf("Erreur d'initialisation de la SDL : %s",SDL_GetError());
      return EXIT_FAILURE;
    }	
  // Création de la fenêtre :
  Init_display();
  windparams.fenetre = 
    SDL_CreateWindow("Une fenetre SDL" , 
		     SDL_WINDOWPOS_CENTERED, 
		     SDL_WINDOWPOS_CENTERED ,
		     windparams.current_width, //(int) (BASE_WINDOW * t),  // width
		     windparams.current_height, //BASE_WINDOW,              // height
		     SDL_WINDOW_RESIZABLE);
 
  windparams.renderer = SDL_CreateRenderer(windparams.fenetre, -1, 0); // Création du windparams.renderer
  SDL_RenderPresent(windparams.renderer);
  if(windparams.fenetre == NULL) // Gestion des erreurs
    {
      printf("Erreur lors de la creation d'une fenetre : %s",SDL_GetError());
      return EXIT_FAILURE;
    }
	  
  if(windparams.renderer == NULL)//gestion des erreurs
    {
      printf("Erreur lors de la creation d'un windparams.windparams.renderer : %s",SDL_GetError());
      return EXIT_FAILURE;
    }

  searchByName = hashmap_new();
  SDL_SetRenderDrawColor(windparams.renderer, 230, 230, 250,0);
  SDL_RenderClear(windparams.renderer);
  parcours(informations.hashbackground);
  _relations_draw();
  parcours(informations.hashforeground);
  SDL_RenderPresent(windparams.renderer);
  export("map.svg");
  SDL_StartTextInput();
  while (1) {
    while(SDL_PollEvent(&event)){
      if(event.type == SDL_QUIT){
	exit(0);//break;
      }else{
	getInput();
      }
      SDL_RenderPresent(windparams.renderer);
    }
    if(strlen(text) > 0){
      search();
    }
    //SDL_UpdateWindowSurface(fenetre);
  }
  return 0;
}



