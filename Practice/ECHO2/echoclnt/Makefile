TARGET   = echoclnt
SOURCES  := $(wildcard *.c)
OBJECTS  := $(SOURCES:.c=*.o)
EDITED_FILES  := $(wildcard *~)
rm       = rm -f

echoclnt: echoclnt.o helper.o
	gcc -o echoclnt echoclnt.o helper.o -Wall

echoclnt.o: echoclnt.c helper.h
	gcc -o echoclnt.o echoclnt.c -c -ansi -pedantic -Wall

helper.o: helper.c helper.h
	gcc -o helper.o helper.c -c -ansi -pedantic -Wall
	
clean:
	@$(rm) $(TARGET) $(OBJECTS) $(EDITED_FILES)	
	@echo "Cleanup complete!"
	
