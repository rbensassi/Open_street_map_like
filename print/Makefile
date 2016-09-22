CC = gcc -g -Wall -c
CPPFLAGS = `sdl2-config --cflags --libs`
LDFLAGS = `xml2-config --cflags --libs`

all:dessin_setting_functions.o dessin.o

dessin.o:dessin.c lib/dessin_setting_functions.h lib/dessin.h 
	$(CC)  $(CPPFLAGS) $(LDFLAGS)  $^

dessin_setting_functions.o:lib/dessin_setting_functions.c lib/dessin.h
	$(CC) $(LDFLAGS) $(CPPFLAGS)  $^
clean:
	rm *.o
	rm lib/*.gch
