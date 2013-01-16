TARGET = test
CXX = g++
CXXFLAGS = -g -O2 -Wall -Werror -std=c++11
LDFLAGS =
LIBS =

SOURCES = $(wildcard *.c *.cpp)

OBJS = $(patsubst %.c, %.o, $(patsubst %.cpp, %.o, $(SOURCES)))

all: ${TARGET}

${TARGET}: ${OBJS}
	${CXX} ${LDFLAGS} -o $@ $^ ${LIBS}

%.o: %.cpp
	${CXX} ${CXXFLAGS} -c $<

.PHONY: all clean

clean:
	-rm -f *~ *.o *.swp tags ${TARGET}
