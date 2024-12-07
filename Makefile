#
# makefile
#  task_tracker_cli
#
#  Created by Haoxiang Zhang on 12/2/24.
#

CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17 -I./include -I./src
LFLAGS = -o

SOURCES = ./src/cli.cpp ./src/json.cpp ./src/main.cpp ./src/utils.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = cli

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(LFLAGS) $@ $^
	
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) *.json

run: $(EXECUTABLE)
	./$(EXECUTABLE)
	
