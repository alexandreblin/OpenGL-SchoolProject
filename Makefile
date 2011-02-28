EXECUTABLENAME=ProjetApp

CFLAGS=-c -ggdb -Wall

UNAME := $(shell uname)
# Adaptation des flags en fonction de l'OS (mac ou linux)
ifeq ($(UNAME), Darwin)
#CFLAGS+= 
LDFLAGS=-framework OpenGL -framework GLUT
else
#CFLAGS+= 
LDFLAGS=-lGL -lGLU -lglut
endif

SRCS=main.cpp Application.cpp
HDRS=Application.h

all: $(EXECUTABLENAME)

$(EXECUTABLENAME): $(SRCS:.cpp=.o)
	g++ $(LDFLAGS) $^ -o $@

%.o: %.c
	g++ $(CFLAGS) $<

clean:
	rm -f $(SRCS:.cpp=.o) $(EXECUTABLENAME) depend

depend: $(SRCS) $(HDRS)
	g++ -M $(CFLAGS) $(SRCS) > .dependencies

-include .dependencies