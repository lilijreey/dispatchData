
MYSQL_CFLAGS=$(shell mysql_config --cflags)
MYSQL_LIBS=$(shell mysql_config --libs)

CXXFLAGS=-Wall -O0 -std=c++11 $(MYSQL_CFLAGS)
LDFLAGS= $(MYSQL_LIBS)

SOURCE:=$(shell find . -type f -name *.cpp)
OBJECTS:=$(patsubst %.cpp,%.o,$(SOURCE))
Exec=main

all: $(Exec)

$(Exec): $(OBJECTS)
	g++ -o main $^ $(LDFLAGS)
	./$(Exec)

clean:
	rm -rf $(OBJECTS) $(Exec)




