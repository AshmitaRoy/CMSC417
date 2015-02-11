TARGET   = echoserv
SOURCES  := $(wildcard *.c)
OBJECTS  := $(SOURCES:.c=*.o)
EDITED_FILES  := $(wildcard *~)
rm       = rm -f


echoserv: echoserv.o helper.o
	gcc -o echoserv echoserv.o helper.o -Wall

echoserv.o: echoserv.c helper.h
	gcc -o echoserv.o echoserv.c -c -ansi -pedantic -Wall

helper.o: helper.c helper.h
	gcc -o helper.o helper.c -c -ansi -pedantic -Wall


clean:
	@$(rm) $(TARGET) $(OBJECTS) $(EDITED_FILES)	
	@echo "Cleanup complete!"



