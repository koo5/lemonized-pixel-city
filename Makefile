SRCS    = $(wildcard *.cpp)
OBJS    = $(patsubst %.cpp,%.o,$(SRCS))
CFLAGS	= -g -Wno-write-strings
LDFLAGS	= -lGL -lGLU -lglut

all: clean objs
	${CXX} ${CFLAGS} ${LDFLAGS} -o PixelCity ${OBJS}
clean:
	rm -f ${OBJS}
objs: ${OBJS}
%.o: %.cpp
	${CXX} ${CFLAGS} -c -o $@ $^
