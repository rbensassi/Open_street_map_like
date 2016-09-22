#include "lib/Svg.h"
extern doc_data informations;
extern display windparams;
void write_svg(int fd,int nbarg,char* arg1,...){
  int i=0;
  char res[1024];
  strcpy(res,arg1);
  va_list ap;
  va_start(ap,arg1);
  char*tmp;
  for( i=0;i<nbarg;i++){
    tmp=(char*)(va_arg(ap,char*));
    strcat(res,(char*)(tmp));
  }
  va_end(ap);
  write(fd,res,strlen(res));
}

void line_svg(int fd ,point p1, point p2,char *color,int epaisseur){
  char points[4][5];
  sprintf(points[0],"%d",(int)p1.x);
  sprintf(points[1],"%d",(int)p1.y);
  sprintf(points[2],"%d",(int)p2.x);
  sprintf(points[3],"%d",(int)p2.y);
  char width[4];
  sprintf(width,"%d",epaisseur);
  write_svg(fd,12,"<line x1=\"",points[0],"\"  y1=\"",points[1],"\" x2=\"",points[2],"\" y2=\"",points[3],"\"  style=\"stroke:",color,";stroke-width:",width,"\"/>\n");
}
void polygone_svg(int fd,char **refList,int nbpoints,char*color,char* trans){
  int j = 0;
  char*points ;
  point p;
  char x[5];
  char y[5];
  if(nbpoints!=0){
    points=(char *) (malloc(nbpoints*10*sizeof(char)));
    strcpy(points,"\"");
      while(refList[j] != NULL){
	     p = recupere_coordonnee(refList[j]);
	     sprintf(x,"%d",(int)p.x);
	     strcat(points,x);
	     strcat(points,",");
	     sprintf(y,"%d",(int)p.y);
             strcat(points,y);
             strcat(points," ");
	     j++;
	   }
         write(fd,"<polygon points=",16);
         write(fd,points,strlen(points));
         write(fd,"\" style=\"fill:",14);
         write(fd,color,strlen(color));
         write(fd,";stroke:purple;fill-opacity:",28);
        write(fd,trans,strlen(trans));
	 write(fd,";stroke-width:1\"/>\n",19);
	   }
  }


void way_svg(int fd ,char **refList,char*color,int epaisseur){
  int j = 0;
  point p1,p2;
  while(refList[j+1] != NULL){
    p1 = recupere_coordonnee(refList[j]);
    p2 = recupere_coordonnee(refList[j+1]);
    line_svg(fd,p1,p2,color,epaisseur);
    j++;
  }
}


void dessine_svg (int fd ,way w){
  if(strcmp(w.type,"highway")==0){
    int r=getThicknessWay(w.valeur);
    if(r<=4)
      way_svg(fd,w.refList,"white",2*r);
    else way_svg(fd,w.refList,"white",3*r);
  }else if(strcmp(w.type,"building")==0){
    polygone_svg(fd,w.refList,w.nbref,"gray","1.0");
	  	
  }else if((((strcmp(w.type,"waterway"))==0)&&(strcmp(w.valeur,"riverbank")==0))||((strcmp(w.type,"natural")==0)&&(strcmp(w.valeur,"water")==0))){
    polygone_svg(fd,w.refList,w.nbref,"blue","1.0");
  }else if(((strcmp(w.type,"landuse")==0)&&((strcmp(w.valeur,"grass")==0)||(strcmp(w.valeur,"forest")==0)))||((strcmp(w.type,"leisure")==0)&&(strcmp(w.valeur,"park")==0))||((strcmp(w.type,"natural")==0)&&(strcmp(w.valeur,"wood")==0))){
    polygone_svg(fd,w.refList,w.nbref,"green","1.0");
  }else if((strcmp(w.type,"natural")==0)&&(strcmp(w.valeur,"coastline")==0)){
    //CoastLine(fd,w.refList,w.nbref);
            
  }else if(strcmp(w.type,"waterway")==0){
    way_svg(fd,w.refList,"blue",3);
  }
}


int  parcours_svg (int fd,hashmap_map *hash){
  int i=0 ;
  for(i = 0; i < 100000; i++){
    if(hash->data[i].in_use != 0) {
      hashmap_element data = hash->data[i];
      dessine_svg(fd,(*((way*)(data.data))));
    }
  }
  return 0;
}
void dessinemultipolygone_svg(int fd,char**waylist,int nbelements,char*color,char*trans){
  int i=0;
  way *w;		 
  for(i=0;i<nbelements;i++){
    if(hashmap_get(informations.hashforeground,waylist[i],(any_t*)&w)!=MAP_MISSING){
      polygone_svg(fd,w->refList,w->nbref,color,trans);
    } 
  }
}        


int dessinerelation_svg(int fd,relation r){
  if((strcmp(r.name,"multipolygon")==0)){
    if(strcmp(r.valeur,"park")==0)
      dessinemultipolygone_svg(fd,r.outermembers,r.nbouter,"green","1.0");
    if(strcmp(r.valeur,"park")==0)
      dessinemultipolygone_svg(fd,r.innermembers,r.nbinner,"green","1.0");
    else  dessinemultipolygone_svg(fd,r.innermembers,r.nbinner,"brown","1.0");
  }
  return 0;

}
int relations_svg(int fd){
  int i=0 ;
  for(i=0;i<informations.nbrelation;i++){ 
    dessinerelation_svg(fd,informations.relation_list[i]);
  }
  return 0;
}

  void export(char* path){
    remove(path);
    int fd=open(path, O_CREAT|O_RDWR,0777);
    write(fd ,"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n",39);
    char buff1[4];
    char buff2[4];
    sprintf(buff1,"%d",windparams.current_width);
    sprintf(buff2,"%d",windparams.current_height);
    write_svg(fd,5,"<svg height=\"",buff2,"\""," width=\"",buff1,"\">\n");
    write_svg(fd,4,"<rect width=\"",buff1,"\" height=\"",buff2,"\" style=\"fill:rgb(205,205,193);stroke-width:1;stroke:rgb(0,0,0)\"/>\n");
     parcours_svg(fd,informations.hashbackground);
     relations_svg(fd);
    parcours_svg(fd,informations.hashforeground);
    write(fd,"</svg>\n",6);
    close(fd);

  }

