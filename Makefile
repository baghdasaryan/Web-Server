CC = g++
DEBUG = -g
CFLAGS = -Wall -Wno-unused-function #-Wextra -Werror $(DEBUG)
LDFLAGS = -Wall $(DEBUG)
SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)
INCLUDES =
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = server

all: $(EXECUTABLE)

#server: $(OBJECTS)
$(EXECUTABLE): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(SOURCES)

#.cpp.o:
#	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f server *.o *~
