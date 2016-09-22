#include "lib/search.h"
extern display windparams ;
extern doc_data informations;
extern hashmap_map *searchByName;

int firstInput = 1;
way * waysearched = NULL;
SDL_Event event;
char text[30];
char*buff;


void getInput(){
  if(event.type == SDL_TEXTINPUT){
    if(waysearched != NULL){
      _dessine(*waysearched);
      waysearched = NULL;
    }
    if(firstInput){
      boxRGBA(windparams.renderer, (windparams.current_width/2)-(windparams.current_width/3), 0, (windparams.current_width/2)+(windparams.current_width/3), 30, 255, 255, 255, 255);
      firstInput = 0;
    }
    if(strlen(text) < 30)
      strcat(text,event.text.text);
    stringRGBA (windparams.renderer, windparams.current_width/4, 10, text, 0, 0, 0, 255);
    printf("%s\n",text);
  }else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && strlen(text) > 0){
    if(waysearched != NULL){
      _dessine(*waysearched);
      waysearched = NULL;
    }
    buff = malloc((strlen(text)));
    text[strlen(text)] = '\0';
    buff[strlen(text)-1] = '\0'; 
    strncpy(buff,text,strlen(text)-1);
    strcpy(text,buff);
    boxRGBA(windparams.renderer, (windparams.current_width/2)-(windparams.current_width/3), 0, (windparams.current_width/2)+(windparams.current_width/3), 30, 255, 255, 255, 255);
    stringRGBA (windparams.renderer, windparams.current_width/4, 10, text, 0, 0, 0, 255);
    printf("%s\n",text);
  }
}

int search_dessine (way w){
  if(strcmp(w.type,"highway")==0){
    int r=getThicknessWay(w.valeur);
    if(r<=4)
      dessineWay(w.refList,186,85,211,150,2*r);
    else dessineWay(w.refList,186,85,211,255,2*r);
  } else if(strcmp(w.type,"building")==0){
    dessinePolygone(w.refList,w.nbref,186,85,211,255);
	  	
  }else if((((strcmp(w.type,"waterway"))==0)&&(strcmp(w.valeur,"riverbank")==0))||((strcmp(w.type,"natural")==0)&&(strcmp(w.valeur,"water")==0))){
    dessinePolygone(w.refList,w.nbref,141,182,205,255);
  }else if(((strcmp(w.type,"landuse")==0)&&((strcmp(w.valeur,"grass")==0)||(strcmp(w.valeur,"forest")==0)))||((strcmp(w.type,"leisure")==0)&&(strcmp(w.valeur,"park")==0))||((strcmp(w.type,"natural")==0)&&(strcmp(w.valeur,"wood")==0))){
    dessinePolygone(w.refList,w.nbref,0,255,100,255);
  }else if((strcmp(w.type,"natural")==0)&&(strcmp(w.valeur,"coastline")==0)){
    dessineCoastLine(w.refList,w.nbref);
            
  }else if(strcmp(w.type,"waterway")==0){
    dessineWay(w.refList,141,182,205,100,5);
  }
  return 0;
}
int search(){
  int i=0;
  for(i = 0; i < 100000; i++){
    if(searchByName->data[i].in_use != 0) {
      hashmap_element data = searchByName->data[i];
      if(strcmp(data.key,text) == 0){
	waysearched = malloc(1000);
	hashmap_get(informations.hashforeground, ((char *)(data.data)),(any_t) &waysearched);
	search_dessine(*waysearched);

	break;
      }
    }
  }
  return 1;
}

