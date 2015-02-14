# Dylan Zingler
# Project 01 CMSC 417 NETWORKING
# Credit given to Yanick Rochon

# project name (generate executable with this name)
TARGET   = p1

CC       = gcc -c
# compiling flags here
#CFLAGS   = -std=c99 -Wall -I. -ansi -pedantic-errors  -D_BSD_SOURCE
CFLAGS = -ansi -pedantic-errors -Wall -Werror -pedantic -D_BSD_SOURCE -std=c99 -g 



LINKER   = gcc -o
# linking flags here
#LFLAGS   = -std=c99 -Wall -D_BSD_SOURCE
LFLAGS = -ansi -pedantic-errors -Wall -Werror -pedantic -D_BSD_SOURCE -std=c99


SOURCES  := $(wildcard *.c)
#INCLUDES := $(wildcard *.h)
OBJECTS  := $(SOURCES:.c=*.o)
EDITED_FILES  := $(wildcard *~)
TESTS := $(wildcard test*.sh)
rm       = rm -f

$(TARGET): obj
	$(LINKER) $(TARGET) $(LFLAGS) $(OBJECTS)
	echo "Linking complete!"

# OLD obj
#obj: $(SOURCES) $(INCLUDES)
#	$(CC) $(CFLAGS) $(SOURCES)
#	echo "Compilation complete!"

obj: $(SOURCES) 
	$(CC) $(CFLAGS) $(SOURCES) 
	echo "Compilation complete!"

test:
	./tests/test1.sh
	
zip:
	zip p1.zip ./tests.sh $(SOURCES) ./MAKEFILE

clean:
	@$(rm) $(TARGET) $(OBJECTS) $(EDITED_FILES)	
	@echo "Cleanup complete!"
