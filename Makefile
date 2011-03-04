EXECUTABLENAME=projet

SRCS=main.cpp Application.cpp Scene.cpp MyScene.cpp Point.cpp Vector.cpp Object.cpp Angle.cpp
HDRS=Application.h Scene.h MyScene.h Point.h Vector.h Object.h Angle.h

CFLAGS=-c -g -Wall
LDFLAGS=-g

# Adaptation des librairies en fonction de l'OS (mac ou linux)
ifeq ($(shell uname), Darwin)
LDLIBS=-framework OpenGL -framework GLUT
else
LDLIBS=-lGL -lGLU -lglut
endif

all: $(EXECUTABLENAME)

$(EXECUTABLENAME): $(SRCS:.cpp=.o)
	g++ $(LDFLAGS) $(LDLIBS) $^ -o $@

%.o: %.cpp
	g++ $(CFLAGS) -MD -o $@ $<
	@cp $*.d $*.P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
          -e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P; \
      rm -f $*.d

clean:
	rm -f $(SRCS:.cpp=.o) $(SRCS:.cpp=.P) $(EXECUTABLENAME)

-include $(SRCS:.cpp=.P)