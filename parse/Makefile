CC = gcc -g -Wall -c
LDFLAGS = `xml2-config --cflags --libs`

all:hashmap_add_functions.o hashmap_get_functions.o Parse.o

Parse.o: libs/*.h Parse.c   
	$(CC) $(LDFLAGS)  $^
hashmap_get_functions.o:libs/*.h libs/hashmap_get_functions.c
	$(CC) $(LDFLAGS)  $^
hashmap_add_functions.o:libs/*.h libs/hashmap_add_functions.c
	$(CC) $(LDFLAGS)  $^

clean:
	rm *.o	
	rm libs/*.gch
