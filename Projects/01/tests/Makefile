# Variables
rm       = rm -f
TARGET   = echoclient

# Compiler
CC       = gcc -c
CFLAGS = -ansi -pedantic-errors -Wall -pedantic -D_BSD_SOURCE -std=c99

# Linker
LINKER   = gcc -o
LFLAGS = -ansi -pedantic-errors -Wall -pedantic -D_BSD_SOURCE -std=c99

# Files
SOURCES  := $(wildcard *.c)
OBJECTS  := $(SOURCES:.c=*.o)
EDITED_FILES  := $(wildcard *~)
TESTS := $(wildcard test*.sh)

# Generate Target (LINKING STAGE)
$(TARGET): obj
	$(LINKER) $(TARGET) $(LFLAGS) $(OBJECTS)
	echo "Linking complete!"


# COMPILING STAGE (Generatingv.o Files)
obj: $(SOURCES) 
	$(CC) $(CFLAGS) $(SOURCES) 
	echo "Compilation complete!"

# COMPRESSION
zip:
	zip $(TARGET).zip ./tests.sh $(SOURCES) ./Makefile config.csv

# CLEAN-UP
clean:
	@$(rm) $(TARGET) $(OBJECTS) $(EDITED_FILES)	
	@echo "Cleanup complete!"
