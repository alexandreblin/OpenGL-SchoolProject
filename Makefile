EXECUTABLENAME=projet

SRCS=main.cpp Application.cpp Scene.cpp Point.cpp Vector.cpp Object.cpp Angle.cpp Light.cpp Spot.cpp Face.cpp
HDRS=Application.h Scene.h Point.h Vector.h Object.h Angle.h Light.h Spot.h Face.h

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