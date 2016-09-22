CC = gcc
CCC = gcc -c
CFLAGS = -g -Wall
CPPFLAGS = `sdl2-config --cflags --libs`
LDFLAGS = `xml2-config --cflags --libs`
NAME=Main

all:
	make -C Extension
	make -C print
	make -C parse
	make -C libs
	make $(NAME)

$(NAME) :Extension/stylefile.o Extension/Svg.o Extension/search.o print/dessin_setting_functions.o print/dessin.o parse/hashmap_add_functions.o parse/hashmap_get_functions.o libs/hashmap.o parse/Parse.o Main.o
	$(CC)  $(CFLAGS)  -o  $(NAME)  $^ $(CPPFLAGS) $(LDFLAGS) -lSDL2_gfx -lm

Main.o:Main.c
	$(CCC) $(CPPFLAGS) $(LDFLAGS) Main.c
clean:
	rm *.o	
	rm $(NAME)
	make -C Extension clean
	make -C print clean
	make -C parse clean
	make -C libs clean
