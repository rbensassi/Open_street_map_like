CC = gcc
CFLAGS = -g -Wall
CPPFLAGS = `sdl2-config --cflags --libs`
LDFLAGS = `xml2-config --cflags --libs`
CKFLAGS = `pkg-config --libs check`
CHECKSEARCH = check_extension_search
CHECKSTYLE = check_extension_stylefile
CHECKADD = check_hashmap_add_functions
CHECKGET = check_hashmap_get_functions
CHECKPARSE = check_parser
CHECKPRINT = check_dessin_setting

all:
	make $(CHECKSEARCH)
	make $(CHECKSTYLE)
	make $(CHECKADD)
	make $(CHECKGET)
	make $(CHECKPARSE)
	make $(CHECKPRINT)


$(CHECKSEARCH) : ../parse/libs/hashmap_add_functions.c ../parse/libs/hashmap_get_functions.c ../print/lib/dessin_setting_functions.c ../print/dessin.c ../Extension/Svg.c ../Extension/search.c ../libs/hashmap.c ../parse/Parse.c
	$(CC) $(CFLAGS) check_extension_search.c -o $(CHECKSEARCH) $(CKFLAGS) $^ $(CPPFLAGS) $(LDFLAGS) -lSDL2_gfx -lm


$(CHECKSTYLE) :../parse/libs/hashmap_add_functions.c ../parse/libs/hashmap_get_functions.c ../print/lib/dessin_setting_functions.c ../print/dessin.c ../Extension/Svg.c ../Extension/search.c ../Extension/stylefile.c ../libs/hashmap.c ../parse/Parse.c
	$(CC) $(CFLAGS) check_extension_stylefile.c -o $(CHECKSTYLE) $(CKFLAGS) $^ $(CPPFLAGS) $(LDFLAGS) -lSDL2_gfx -lm


$(CHECKADD):../parse/libs/hashmap_add_functions.c  ../parse/libs/hashmap_get_functions.c ../libs/hashmap.c ../parse/Parse.c
	$(CC) $(CFLAGS) check_hashmap_add_functions.c -o $(CHECKADD) $(CKFLAGS) $^ $(LDFLAGS)


$(CHECKGET):../parse/libs/hashmap_get_functions.c
	$(CC) $(CFLAGS) check_hashmap_get_functions.c -o $(CHECKGET) $(CKFLAGS) $^ $(LDFLAGS) 


$(CHECKPARSE):../parse/Parse.c ../parse/libs/hashmap_add_functions.c ../parse/libs/hashmap_get_functions.c ../libs/hashmap.c
	$(CC) $(CFLAGS) check_parser.c -o $(CHECKPARSE) $(CKFLAGS) $^ $(LDFLAGS)


$(CHECKPRINT):../parse/libs/hashmap_add_functions.c ../parse/libs/hashmap_get_functions.c ../print/lib/dessin_setting_functions.c  ../print/dessin.c ../Extension/Svg.c ../Extension/search.c ../libs/hashmap.c ../parse/Parse.c 
	$(CC) $(CFLAGS) check_dessin_setting.c -o $(CHECKPRINT) $(CKFLAGS) $^ $(LDFLAGS) $(CPPFLAGS) -lSDL2_gfx -lm


clean:
	rm $(CHECKSEARCH)
	rm $(CHECKSTYLE)
	rm $(CHECKADD)
	rm $(CHECKGET)
	rm $(CHECKPARSE)
	rm $(CHECKPRINT)
