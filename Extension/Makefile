CC = gcc -g -Wall -c
CPPFLAGS = `sdl2-config --cflags --libs`
LDFLAGS = `xml2-config --cflags --libs`

all:search.o stylefile.o Svg.o

search.o:search.c  lib/search.h
	$(CC) $(LDFLAGS) $(CPPFLAGS) $^

stylefile.o:stylefile.c lib/stylefile.h
	$(CC) $(LDFLAGS) $(CPPFLAGS) $^
Svg.o:Svg.c   lib/Svg.h 
	$(CC) $(LDFLAGS) $(CPPFLAGS) $^
clean:
	rm *.o	
	rm lib/*.gch
